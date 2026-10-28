# -*- coding: utf-8 -*-
# -----------------------------------------------------------------------------
# NAME = abs_inliner
# -----------------------------------------------------------------------------
# VERSION = 0.2
# -----------------------------------------------------------------------------
# Description:
#   Base on inliner.py of ul-cseq
#   revise:
#       - 2025/5/4 Add the retention logic (ISRs) in visit_FuncDef 
#   Base on inliner.py of Lazy-cseq
#   Add new features:
#       -init_scalar()/malloc() should not be called when variables have init expressions!
#       -split declaration of local variables + init value to two separate statements:
#           e.g. int x = value; --> int x; x = value;
#       - limit recursion depth (otherwise parsing recursive functions
#           will give a python stack overflow)
#       - rename labels (& corresponding gotos) in inlined blocks of code to avoid label duplication
#       - removing empty statement (which call additional context switch)
#
#   Limitations:
#       Cannot deal with pointer to function (that function need to be inline)
#       Cannot deal with inlining recursive call
#
# TODO:
#     - if a function is in region of __VERIFIER_atomic, it is not inlined
#     - simulate parameter parsing inside __VERIFIER_atomic_begin and end to reduce context switch
#     - handle f(g(x)):  g(x) is in n.args therefore at the moment would not be inlined?
# Changelog:
#
# -----------------------------------------------------------------------------


from pycparser import c_ast
from abs_module import ABS_Module
import common


class ABS_Inliner(ABS_Module):
    INDENT_SPACING = ' '

    currentFunction = ['']         # Current function
    currentFunctionParams = []     # while parsing a function call, keeps the list of parameters used for the actual call

    inlinedStack = []              # inlined function to add before a statement
    indexStack = []                # current index (= functionname_inliningcountforthisfunction) used for labels and gotos

    __parsingStruct = False        #
    funcInlinedCount = {}          # number of times a function call has been inlined, by function

    __parsingFunction = False


    def visit_FuncDef(self, n):
        # print('Generate FuncDef', n.decl.name)
        self.__parsingFunction = True
        # Function definitions of inlined functions must disappear
        # (except thread functions which is the parameter of pthread_create).
        if (self.__needsInlining_nonThreadFunc(n.decl.name) and
                n.decl.name not in self.Parser.threadName and  # Not a thread Function
                n.decl.name not in self.Parser.funcReferenced and  # Not a pointer to function
                not ('ISR' in n.decl.name or 'isr' in n.decl.name or 'interrupt' in n.decl.name)):
            self.__parsingFunction = False
            return ''

        self.currentFunction.append(n.decl.name)
        decl = self.visit(n.decl)
        self.indent_level = 0
        body = self.visit(n.body)

        # At the bottom of each thread, add a pthread_exit() statement
        returnStmt = ''

        # TODO: Need to be revised pthread exit
        # Check if the function is main or contains ISR/isr/interrupt
        if (self.currentFunction[-1] in self.Parser.threadName or  # thread Function
                self.currentFunction[-1] == 'main' or  # main function
                'ISR' in self.currentFunction[-1] or
                'isr' in self.currentFunction[-1] or
                'interrupt' in self.currentFunction[-1]):
            # returnStmt = self._make_indent() + '__exit_%s: ; %s(0);\n' % (self.currentFunction[-1],
            #     common.changeID['pthread_exit'])
            if self.currentFunction[-1] not in self.Parser.abs_fhasreturn:
                returnStmt = self._make_indent() + '%s(0);\n' % common.changeID['pthread_exit']

        # Continue the visit.
        if n.param_decls:
            # Old style K&R declaration
            knrdecls = ';\n'.join(self.visit(p) for p in n.param_decls)
            body = body[:body.rfind('}')] + self._make_indent() + returnStmt + '}'
            block = decl + '\n' + knrdecls + ';\n' + body + '\n'
        else:
            body = body[:body.rfind('}')] + self._make_indent() + returnStmt + '}'
            block = decl + '\n' + body + '\n'

        self.currentFunction.pop()
        self.__parsingFunction = False

        return block

    def visit_FuncCall(self, n):
        fref = self._parenthesize_unless_simple(n.name)  # Function name
        # print('Visiting FuncCall', fref)
        args = self.visit(n.args)

        # TODO: assuming that there is no pthread_exit so far
        # Pthread exit()s can only be within thread functions,
        # no need to check whether we're in a thread.

        if (fref == 'pthread_exit' or
                fref == common.changeID['pthread_exit']):  # pthread_exit() param is ignored for the moment
            # return 'goto __exit_%s ' % (self.currentFunction[-1])
            return '%s(0);\n' % common.changeID['pthread_exit']
            # return ''

        args = self.visit(n.args)
        s = fref + '(' + args + ')'

        if n.args is None:
            self.currentFunctionParams.append([])

        if self.__needsInlining_nonThreadFunc(fref):
            if fref not in self.funcInlinedCount:
                self.funcInlinedCount[fref] = 0
            self.funcInlinedCount[fref] += 1

            self.indexStack.append('_%s_%s' % (fref, self.funcInlinedCount[fref]))

            self.inlinedStack[-1] += (self._inliningFunction(self.Parser.funcASTNode[fref], n, False)) + '\n'

            if self.Parser.funcIsVoid[fref]:
                s = 'MARKERTOBEDELETED'
            else:
                s = '__retval_%s' % (self.indexStack[-1])
            self.indexStack.pop()
        return s

    def visit_Return(self, n):
        if len(self.indexStack) > 0:  # There is function to be inlined
            if self.Parser.funcIsVoid[self.currentFunction[-1]]:
                return 'goto __exit_%s;' % (self.indexStack[-1])  # void
            else:
                return '__retval_%s = %s; goto __exit_%s;' % (self.indexStack[-1],
                                                              self.visit(n.expr), self.indexStack[-1])  # non-void

        if self.currentFunction[-1] in self.Parser.threadName:
            # Goto exit point of that function
            return '%s(0);' % common.changeID['pthread_exit']
            # return 'goto __exit_%s; ' % (self.currentFunction[-1])
        elif self.currentFunction[-1] == 'main':
            return '%s(0);' % common.changeID['pthread_exit']
            # return 'goto __exit_main; '

        # Normal return of __VERIFIER_atomic functions
        s = 'return'
        if n.expr:
            s += ' ' + self.visit(n.expr)
        return s + ';'

    # TODO: Need to check again using self.Parser.funcLabels
    def visit_Label(self, n):
        if (len(self.indexStack) > 0 and
                self.__needsInlining_nonThreadFunc(self.currentFunction[-1]) and
                self.currentFunction[-1] not in self.Parser.threadName and  # Not a thread Function
                self.currentFunction[-1] not in self.Parser.funcReferenced):  # Not a pointer to function:
            return self._make_indent() + n.name + self.indexStack[-1] + ':\n' + self._generate_stmt(n.stmt)
        else:
            return self._make_indent() + n.name + ':\n' + self._generate_stmt(n.stmt)

    def visit_Goto(self, n):
        if (len(self.indexStack) > 0 and
                self.__needsInlining_nonThreadFunc(self.currentFunction[-1]) and
                self.currentFunction[-1] not in self.Parser.threadName and  # Not a thread Function
                self.currentFunction[-1] not in self.Parser.funcReferenced):  # Not a pointer to function:
            return self._make_indent() + 'goto ' + n.name + self.indexStack[-1] + ';'
        else:
            return self._make_indent() + 'goto ' + n.name + ';'

    def visit_Struct(self, n):
        oldParsingStruct = self.__parsingStruct
        self.__parsingStruct = True
        s = self._generate_struct_union(n, 'struct')
        self.__parsingStruct = oldParsingStruct
        return s

    def visit_Union(self, n):
        oldParsingStruct = self.__parsingStruct
        self.__parsingStruct = True
        s = self._generate_struct_union(n, 'union')
        self.__parsingStruct = oldParsingStruct
        return s

    def visit_Decl(self, n, no_type=False):
        # no_type is used when a Decl is part of a DeclList, where the type is
        # explicitly only for the first delaration in a list.
        #
        s = n.name if no_type else self._generate_decl(n)

        if n.bitsize:
            s += ' : ' + self.visit(n.bitsize)

        # Change local variables to be static vars,
        # needed for this particular encoding to remember the old values of local variables
        # between simulated context switches.
        #
        # If the variable is scalar or it is an array of fixed size,
        # then just add   static   to its declaration.
        # If the variable is an array of non fixed size, then change it to a static pointer and
        #  adds a call to malloc() to complete the initialization,
        # (e.g.    int x[size];  -->  static int * x; x = (int *)malloc(sizeof(int)*size);  )

        if (isinstance(n, c_ast.Decl) and
                self.currentFunction[-1] != '' and
                self.indent_level > 0 and
                not s.startswith('static ') and
                not self.__parsingStruct):
            if ((self.__isScalar(self.currentFunction[-1], n.name) or
                    self.__isStruct(self.currentFunction[-1], n.name) or
                    self.__isUnion(self.currentFunction[-1], n.name)) and
                    not self.Parser.varInitExpr[self.currentFunction[-1], n.name]):  # This variable is not initialized
                s = 'static ' + s
                # TODO: Need proper implementation
                if s.find('pthread_t') == -1:  # Type pthread does not need to be cared
                    s += '; __cs_init_scalar(&%s, sizeof(%s))' % (n.name,
                                                                  self.Parser.varType[self.currentFunction[-1], n.name])
            elif ((self.__isScalar(self.currentFunction[-1], n.name) or
                    self.__isStruct(self.currentFunction[-1], n.name) or
                    self.__isUnion(self.currentFunction[-1], n.name)) and
                  self.Parser.varInitExpr[self.currentFunction[-1], n.name]):
                s = 'static ' + s
            elif self.__isArray(self.currentFunction[-1], n.name):
                stars = '*' * self.Parser.varArity[self.currentFunction[-1], n.name]
                vartype = self.Parser.varType[self.currentFunction[-1], n.name]

                s = 'static %s %s %s; ' % (self.Parser.varType[self.currentFunction[-1], n.name],
                                           stars, n.name)
                # TODO: Need proper implementation
                if vartype.find('pthread_t') == -1:  # Type pthread does not need to be cared
                    s += n.name + ' = (%s %s) malloc(sizeof(%s)*%s)' % (vartype, stars, vartype,
                                                                        self._totalSize(self.currentFunction[-1], n.name))

        assignmentStmt = ''

        if n.init:
            if isinstance(n.init, c_ast.ExprList):
                assignmentStmt = ' = (' + self.visit(n.init) + ')'
            elif self.__parsingFunction:
                fname = self.currentFunction[-1]
                # Split local init off the declaration so sequentialization
                # can re-assign on ISR re-dispatch and skip it on resume via PC.
                if isinstance(n.init, c_ast.InitList):
                    if n.name and self.__isArray(fname, n.name):
                        assignmentStmt = self._array_init_assignments(n.name, n.init)
                    elif n.name:
                        vartype = self.Parser.varType[fname, n.name]
                        assignmentStmt = '; %s = (%s){ %s }' % (
                            n.name, vartype, self.visit(n.init))
                    else:
                        assignmentStmt = ' = {' + self.visit(n.init) + '}'
                elif (n.name and isinstance(n.init, c_ast.Constant) and
                        self.__isArray(fname, n.name) and
                        getattr(n.init, 'type', '') == 'string'):
                    assignmentStmt = self._string_array_assignments(n.name, n.init)
                else:
                    assignmentStmt = '; %s = (' % n.name + self.visit(n.init) + ')'
            else:  # Global variables keep the initializer on the declaration
                if isinstance(n.init, c_ast.InitList):
                    assignmentStmt = ' = {' + self.visit(n.init) + '}'
                elif isinstance(n.init, c_ast.Constant):
                    assignmentStmt = ' = ' + self.visit(n.init)
                else:
                    assignmentStmt = ' = (' + self.visit(n.init) + ')'

        return s + assignmentStmt

    def visit_Compound(self, n):
        s = self._make_indent() + '{\n'
        self.indent_level += 2

        if n.block_items:
            for stmt in n.block_items:
                s += self._inlineIfNeeded(stmt)

        self.indent_level -= 2
        s += self._make_indent() + '}\n'
        return s

    def visit_ExprList(self, n):
        visited_subexprs = []
        for expr in n.exprs:
            if isinstance(expr, c_ast.ExprList):
                visited_subexprs.append('{' + self.visit(expr) + '}')
            else:
                visited_subexprs.append(self.visit(expr))
        self.currentFunctionParams.append(visited_subexprs)
        return ', '.join(visited_subexprs)

    # -------------------------------------------------------------------------------
    # Private helper functions
    # -------------------------------------------------------------------------------
    def _inlineIfNeeded(self, stmt):
        # print('Generate stmt', stmt)
        self.inlinedStack.append('')
        original = self._generate_stmt(stmt)
        original = original.replace('MARKERTOBEDELETED;\n', '')
        original = self.inlinedStack[-1] + original
        self.inlinedStack.pop()
        return original

    def _inliningFunction(self, n, fcall_ast_node, simple):
        # print('Inlining function', n.decl.name)
        ''' Generate the function body or inlining,
            for either including it in a function definition, or
            for inserting it into a statement
        '''
        fref = n.decl.name
        # args = self.visit(fcall_ast_node.args)

        fInput = fOutput = ''

        # Simulate input parameter passing.
        # Build argument initialization statement(s) if needed, to simulate parameter passing
        # (see transformation details below)
        # TODO: pointer-to-function inlining
        if fcall_ast_node.args is not None:
            i = 0
            for p in self.Parser.varNames[fref]:
                if self.Parser.varKind[fref, p] == 'p':  # This variable is a parameter
                    if i != 0:
                        fInput += self._make_indent(delta=1)
                    if not self.__isPointerToFunction(fref, p) and not self.__isArray(fref, p):
                        fInput += 'static %s %s; %s = %s;\n' % (self.Parser.varTypeUnExpanded[fref, p], p, p,
                                                                self.currentFunctionParams[-1][i])
                        i += 1
                    elif not self.__isPointerToFunction(fref, p) and self.__isArray(fref, p):
                        stars = ''
                        for s in self.Parser.varSize[fref, p]:
                            stars += '*'
                        fInput += 'static %s %s%s; %s = %s;\n' % (self.Parser.varTypeUnExpanded[fref, p],
                                                                  stars, p, p, self.currentFunctionParams[-1][i])
                    else:
                        x = self.Parser.varTypeUnExpanded[fref, p].replace('(*)', '(*%s)' % p)
                        fInput += 'static %s; %s = %s;\n' % (x, p, self.currentFunctionParams[-1][i])
                        i += 1

        # Simulate output parameter returning.
        #
        if not self.Parser.funcIsVoid[fref]:
            fOutput = 'static %s __retval_%s;\n' % (self.Parser.funcBlockOut[fref], self.indexStack[-1])
        else:    # simple function call without assignment (e.g. f(x);)
            fOutput = ''

        # Transform the function body by:
        #   1. adding the initialization statement(s) (if any) at the top
        #   2. adding one exit label at the bottom where to jump to in order to simulate return statements
        #   3. change return statements to goto statements pointing to the exit label added in previous step
        #   4. all the rest is unchanged
        #

        # body (adds one indent each line)
        self.currentFunction.append(fref)
        inlined = self.visit(self.Parser.funcASTNode[fref].body)
        # top
        inlined = inlined.replace(self.INDENT_SPACING + '{',
                                  self.INDENT_SPACING + fOutput + self._make_indent() + '{\n' + self._make_indent(1) + fInput, 1)
        # bottom
        inlined = inlined[:inlined.rfind('}')] + '%s __exit_%s: ;  \n' % (self._make_indent(1),
                                                                          self.indexStack[-1]) + self._make_indent() + '}\n'
        self.currentFunction.pop()
        return inlined

    ''' Check whether variable  v  from function  f  has a fixed size,
        or not (e.g.  int x[expr]   with expr not constant.
    '''

    def _hasFixedSize(self, f, v):
        if self.Parser.varArity[f, v] > 0:
            for i in range(0, self.Parser.varArity[f, v]):
                if not self.Parser.varSize[f, v][i].isdigit():
                    return False
        return True

    ''' Return the total size of a given array in a string,
        as the expression of the product of all sizes.

        For example:

            int x[10][expr][3];

        returns:

            size = 10*(expr)*30;
    '''

    def _totalSize(self, f, v):
        sizeExpression = ''

        for i in range(0, self.Parser.varArity[f, v]):
            # if self.Parser.varSize[f,v][i].isdigit():     # simple digit
            sizeExpression += str(self.Parser.varSize[f, v][i]) + '*'

        sizeExpression = sizeExpression[:-1]

        return sizeExpression

    def _flatten_init_exprs(self, node):
        ''' Flatten nested InitList into a list of C expression strings. '''
        result = []
        if isinstance(node, c_ast.InitList):
            for expr in node.exprs:
                result.extend(self._flatten_init_exprs(expr))
        elif isinstance(node, c_ast.NamedInitializer):
            result.extend(self._flatten_init_exprs(node.expr))
        else:
            result.append(self.visit(node))
        return result

    def _array_init_assignments(self, name, init):
        exprs = self._flatten_init_exprs(init)
        if not exprs:
            return ''
        parts = []
        for i, expr in enumerate(exprs):
            parts.append('%s[%s] = (%s)' % (name, i, expr))
        return '; ' + '; '.join(parts)

    def _decode_c_string_constant(self, node):
        v = node.value
        if v.startswith('L') or v.startswith('u') or v.startswith('U'):
            v = v.lstrip('LUu')
        if len(v) >= 2 and v[0] == '"' and v[-1] == '"':
            try:
                import ast
                return ast.literal_eval(v)
            except Exception:
                return v[1:-1]
        return v

    def _c_char_literal(self, ch):
        o = ord(ch)
        if ch == "'":
            return "'\\''"
        if ch == '\\':
            return "'\\\\'"
        if 32 <= o <= 126:
            return "'%s'" % ch
        return "'\\x%02x'" % o

    def _string_array_assignments(self, name, const_node):
        chars = self._decode_c_string_constant(const_node)
        parts = []
        for i, ch in enumerate(chars):
            parts.append('%s[%s] = (%s)' % (name, i, self._c_char_literal(ch)))
        parts.append("%s[%s] = ('\\0')" % (name, len(chars)))
        return '; ' + '; '.join(parts)

    # Checks whether variable  v  from function  f  is an array.
    #
    def __isArray(self, f, v):
        if self.Parser.varArity[f, v] > 0:
            return True
        else:
            return False

    # Checks whether variable  v  from function  f  is scalar.
    # TODO redo properly at parser-level
    #
    def __isScalar(self, f, v):
        if (self.Parser.varArity[f, v] == 0 and
                not self.Parser.varType[f, v].startswith('struct ') and
                not self.Parser.varType[f, v].startswith('union ')):
            return True
        else:
            return False

    # Checks whether variable  v  from function  f  is a struct.
    # TODO redo properly at parser-level
    #
    def __isStruct(self, f, v):
        result = False
        if self.Parser.varType[f, v].startswith('struct '):
            result = True
        return result

    def __isUnion(self, f, v):
        return self.Parser.varType[f, v].startswith('union ')

    def __isPointerToFunction(self, f, v):
        if (f, v) in self.Parser.varPtrToFunct:
            return True
        else:
            return False

    ''' Check whether non thread function  f  needs to be inlined.
    '''

    def __needsInlining_nonThreadFunc(self, f):
        return (f in self.Parser.funcBlock and  # defined functions need to be inlined when called (if at all)
                not f.startswith('__VERIFIER_atomic') and
                not f.startswith(common.funcPrefixChange['__VERIFIER_atomic']) and
                not f == '__VERIFIER_assert' and
                not f == '__VERIFIER_assume' and
                f != '' and
                f != 'main')
