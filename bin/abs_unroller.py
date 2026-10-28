# -----------------------------------------------------------------------------
# NAME = abs_threadcreation
# -----------------------------------------------------------------------------
# VERSION = 0.2
# -----------------------------------------------------------------------------
# Description:
#   Additional features:
#       renaming thread function if it doesn't have argument
#           e.g. void * thr1() --> void* thr1(void * arg)
#
#
#   Based on unroller.py of Lazy-cseq
#   This module handle multiple form of thread creation in main thread
#   And will free pthread_create from loop for further thread duplication
#   A. Bounded thread creation
#       1. limited number of pthread
#           e.g.main()
#               {
#                   pthread(...)
#                   ...
#                   pthread(...)
#               }
#          --> handling in normal case (nothing special)
#       2. main thread acts as a thread to simulated
#           e.g. main()
#                {
#                   pthread(...)
#                   thr2() // call to a function
#                }
#          --> inline thr2() and treat as normal
#
#       3. in while loop (for loop does not exist from abs_loopconversion module)
#          with bounded number of loop
#           e.g. main()
#                {
#                   while (i < 4)
#                   {
#                       pthread_create(...)
#                   }
#                }
#          --> unroll this loop to exactly number of loops and
#               use thread duplicator
#               In addition, also removing redundant statement if possible
#
#       4. in while loop with potentially unbounded number of loop
#           e.g. main()
#               {
#                   int n = __VERIFIER_nondet_X();
#                   // or int n = undefined_func_call();
#
#                   while (i < n)
#                   {
#                       pthread_create(...)
#                   }
#               }
#          --> unroll while loop for a given bounded value
#   B. Unbounded thread creation
#       1. In infinite while loop
#           e.g. while(1)
#               {
#                   pthread_create(...)
#               }
#           --> unroll while loop for a given bounded value
#
#           e.g. while(1)
#               {
#                   if(__VERIFIER_nondet_X())
#                   {
#                       pthread_create(...)
#                   }
#                   else
#                   {
#                       pthread_create(...)
#                   }
#               }
#           --> unroll while loop for a given bounded value
#               leave pthread_create for thread duplicate handler
#
#       2. In potentially infinite while loop
#           e.g. while(__VERIFIER_nondet_X())
#               {
#                   pthread_create(...)
#               }
#           --> unroll while loop for a given bounded value
#
#
# Limitations:
#   - pthread_create must be in main thread (which is normal)
#   - there must not be label in this while loop
#   - no nested loops containing pthread_create
#   - only deal with some specific type of loop
#
# TODO:
#   - Fix generate layout to avoid compound statement when unrolling loop
#
# Changelog:
#   - 2016.05.04: Fix __unwindbound of unbounded thread creation, now this
#              is manually set by parameter
#   - 2014.10.28: Adding feature that will eliminate __VERIFIER_nondet_int
#               for potentially unbounded loop
# -----------------------------------------------------------------------------

from pycparser import c_ast
from abs_module import ABS_Module, ModuleError
import utils


class ABS_Unroller(ABS_Module):
    __unwindbound = 3       # chosen number of threads
    __threads = 3

    __loopCount = 0         # loops discovered so far
    __currentFunction = ''
    __has_pthread_stmt = False
    __has_break_stmt = False
    __has_continue_stmt = False
    __stmtCount = 0
    __labelCount = {}

    __varnames = {}  # Store variable with their value
    __potentialUnboundedVar = []

    __backend = 'cpachecker'

    def loadfromstring(self, string, env):
        self.__backend = env.backend
        self.__threads = env.threads       # maximum number of threads
        self.Parser.reset()  # resets all the parser datastructs
        self.Parser.loadfromstring(string)
        self.ast = self.Parser.ast
        self.output = self.visit(self.ast)

    def string(self):
        return self.output

    def save(self, filename):
        outfile = open(filename, "w")
        outfile.write(self.output)
        outfile.close()

    def show(self):
        print(self.output)

    def visit_Decl(self, n, no_type=False):
        if (n.name is not None and
                (self.__currentFunction == 'main' or
                    not self.__currentFunction)):
            self.__varnames[n.name] = []
            if n.init:
                init = self._visit_expr(n.init)
                if type(n.init) == c_ast.FuncCall:
                    self.__varnames[n.name].append(('assignCall', init))
                else:
                    self.__varnames[n.name].append(('=', init))
        # no_type is used when a Decl is part of a DeclList, where the type is
        # explicitly only for the first delaration in a list.
        #
        s = n.name if no_type else self._generate_decl(n)
        if n.bitsize:
            s += ' : ' + self.visit(n.bitsize)
        if n.init:
            s += ' = ' + self._visit_expr(n.init)
        return s

    def visit_Assignment(self, n):
        lvalue = self.visit(n.lvalue)
        rval_str = self._parenthesize_if(
            n.rvalue, lambda n: isinstance(n, c_ast.Assignment))

        if ((self.__currentFunction == 'main' or not self.__currentFunction) and
                lvalue in self.__varnames):
            if type(n.rvalue) == c_ast.FuncCall:
                self.__varnames[lvalue].append(('assignCall', rval_str))
            else:
                self.__varnames[lvalue].append((n.op, rval_str))

        return '%s %s %s' % (lvalue, n.op, rval_str)

    def visit_BinaryOp(self, n):
        lval_str = self._parenthesize_if(
            n.left, lambda d: not self._is_simple_node(d))
        rval_str = self._parenthesize_if(
            n.right, lambda d: not self._is_simple_node(d))

        if ((self.__currentFunction == 'main' or not self.__currentFunction) and
                lval_str in self.__varnames):
            self.__varnames[lval_str].append((n.op, rval_str))

        return '%s %s %s' % (lval_str, n.op, rval_str)

    def visit_UnaryOp(self, n):
        operand = self._parenthesize_unless_simple(n.expr)

        if ((self.__currentFunction == 'main' or not self.__currentFunction) and
                operand in self.__varnames):
            if n.op == 'p++' or n.op == '++' or n.op == 'p--' or n.op == '--':
                self.__varnames[operand].append((n.op, ''))

        if n.op == 'p++':
            return '%s++' % operand
        elif n.op == 'p--':
            return '%s--' % operand
        elif n.op == 'sizeof':
            return 'sizeof(%s)' % self.visit(n.expr)
        else:
            return '%s%s' % (n.op, operand)

    def visit_While(self, n):
        cond = ''
        if n.cond:
            cond = self.visit(n.cond)

        self.__loopCount += 1
        self.__has_pthread_stmt = False
        self.__has_break_stmt = False
        self.__has_continue_stmt = False
        self.__stmtCount = 0

        currentLoopID = self.__loopCount

        self.__labelCount = {}
        block = self._generate_stmt(n.stmt, add_indent=True)

        # Ad-hoc solution for unbounded number of threads
        if self.__currentFunction == 'main' and self.__has_pthread_stmt:
            condType = type(n.cond)
            # This is a while(1) loop
            if (condType == c_ast.Constant and n.cond.value != '0'):
                # Case B.1
                # Unwound for a given number of time
                s = ''
                for i in range(0, self.__threads):     # by the MAX number of threads
                    newBlock = block
                    # Label replacement if applicable
                    for l in self.__labelCount:
                        newBlock = newBlock.replace(l, '%s_%s' % (l, i))
                    # Break and continue replacement
                    if self.__has_break_stmt:
                        newBlock = newBlock.replace('<break-was-here>',
                                                    'goto __exit_loop_%s;' % currentLoopID)
                    if self.__has_continue_stmt:
                        newBlock = newBlock.replace('<continue-was-here>',
                                                    'goto __continue_%s_loop_%s;\n' % (i, currentLoopID))
                        newBlock = newBlock[:newBlock.rfind('}')] + '__continue_%s_loop_%s:;\n' % (i, currentLoopID) + '}\n'
                    s += newBlock
                # Exit loop
                if self.__has_break_stmt:
                    s += '__exit_loop_%s:;\n' % currentLoopID
                return s

            # This is a        while(__VERIFIER_nondet)          loop
            if condType == c_ast.FuncCall and cond.startswith('__VERIFIER_nondet'):
                # Case B.2
                s = ''
                for i in range(0, self.__threads):    # by the MAX number of threads
                    newBlock = 'if(!(' + cond + ')) { goto __exit_loop_%s; }\n' % currentLoopID
                    newBlock += block
                    # Label replacement if applicable
                    for l in self.__labelCount:
                        newBlock = newBlock.replace(l, '%s_%s' % (l, i))
                    # Break and continue replacement
                    if self.__has_break_stmt:
                        newBlock = newBlock.replace('<break-was-here>', 'goto __exit_loop_%s;' % currentLoopID)
                    if self.__has_continue_stmt:
                        newBlock = newBlock.replace('<continue-was-here>', 'goto __continue_%s_loop_%s;\n' % (i, currentLoopID))
                        newBlock = newBlock[:newBlock.rfind('}')] + '__continue_%s_loop_%s:;\n' % (i, currentLoopID) + '}\n'
                    s += newBlock
                # Exit loop
                s += '__exit_loop_%s:;\n' % currentLoopID
                return s

            # This is a while(counter < somevalue) loop
            if (condType == c_ast.BinaryOp and type(n.cond.left) == c_ast.ID):
                lvar_str = self._parenthesize_if(n.cond.left, lambda d: not self._is_simple_node(d))
                rvar_str = self._parenthesize_if(n.cond.right, lambda d: not self._is_simple_node(d))

                # Likely a translated of for loop  -  Case A.3
                if (type(n.cond.right) == c_ast.Constant and
                        self._loopIsBounded(lvar_str)):
                    # Unroll this loop for exactly number of of time
                    timesLoop = self._calculateLoopTimes(lvar_str)
                    if timesLoop != -1:
                        s = ''
                        reduceable = False
                        initValue = int(self.__varnames[lvar_str][-3][1])
                        lastValue = 0

                        for i in range(0, timesLoop):
                            newBlock = block[block.find('{') + 1:block.rfind('}')]
                            # Label replacement if applicable
                            for l in self.__labelCount:
                                newBlock = newBlock.replace(l, '%s_%s' % (l, i))
                            # Break and continue replacement
                            if self.__has_break_stmt:
                                newBlock = newBlock.replace('<break-was-here>', 'goto __exit_loop_%s;' % currentLoopID)
                            if self.__has_continue_stmt:
                                newBlock = newBlock.replace('<continue-was-here>', 'goto __continue_%s_loop_%s;\n' % (i, currentLoopID))
                                newBlock = newBlock[:newBlock.rfind('}')] + '__continue_%s_loop_%s:;\n' % (i, currentLoopID) + '}\n'
                            # Replacement of counter
                            if self.__stmtCount == 2:
                                if self.__varnames[lvar_str][-1][0] == 'p++':
                                    reduceable = True
                                    stringtoReplace = lvar_str + '++;'
                                    newBlock = newBlock.replace(stringtoReplace, '', 1)
                                    lastvalue = initValue + timesLoop
                                if self.__varnames[lvar_str][-1][0] == '++':
                                    reduceable = True
                                    stringtoReplace = '++' + lvar_str + ';'
                                    newBlock = newBlock.replace(stringtoReplace, '', 1)
                                    lastvalue = initValue + timesLoop
                                if self.__varnames[lvar_str][-1][0] == 'p--':
                                    reduceable = True
                                    stringtoReplace = lvar_str + '--;'
                                    newBlock = newBlock.replace(stringtoReplace, '', 1)
                                    lastvalue = initValue - timesLoop
                                if self.__varnames[lvar_str][-1][0] == '--':
                                    reduceable = True
                                    stringtoReplace = '--' + lvar_str + ';'
                                    newBlock = newBlock.replace(stringtoReplace, '', 1)
                                    lastvalue = initValue - timesLoop

                            s += newBlock
                        # Exit loop label
                        if reduceable:
                            s += '%s = %s;\n' % (lvar_str, lastvalue)
                        if self.__has_break_stmt:
                            s += '__exit_loop_%s:;\n' % currentLoopID
                        return s
                    else:
                        raise ModuleError('Something very wrong happened in this while loop\n')

                # Case when loop is potentially bounded
                elif (type(n.cond.right) == c_ast.ID and
                        self._loopIsPotentiallyBounded(lvar_str, rvar_str)):
                    # Unroll this loop for exactly number of times
                    timesLoop = self._calculateLoopTimes2(lvar_str, rvar_str)
                    if timesLoop != -1:
                        s = ''
                        for i in range(0, timesLoop):
                            newBlock = 'if(!(' + cond + ')) { goto __exit_loop_%s; }\n' % currentLoopID
                            newBlock += block
                            # Label replacement if applicable
                            for l in self.__labelCount:
                                newBlock = newBlock.replace(l, '%s_%s' % (l, i))
                            # Break and continue replacement
                            if self.__has_break_stmt:
                                newBlock = newBlock.replace('<break-was-here>',
                                                            'goto __exit_loop_%s;' % currentLoopID)
                            if self.__has_continue_stmt:
                                newBlock = newBlock.replace('<continue-was-here>',
                                                            'goto __continue_%s_loop_%s;\n' % (i, currentLoopID))
                                newBlock = newBlock[:newBlock.rfind('}')] + '__continue_%s_loop_%s:;\n' % (i, currentLoopID) + '}\n'
                            s += newBlock
                        # Exit loop
                        s += '__VERIFIER_assume(!(%s));__exit_loop_%s:;\n' % (cond, currentLoopID)
                        return s
                    else:
                        raise ModuleError('Something very wrong happened in this while loop\n')

                # Case when loop is potentially unbounded
                elif (type(n.cond.right) == c_ast.ID and
                        self._loopIsPotentiallyUnbounded(lvar_str, rvar_str) and
                        (n.cond.op == '<' or n.cond.op == '<=' or n.cond.op == '>' or n.cond.op == '>=')):
                    self.__potentialUnboundedVar.append(rvar_str)
                    # Normal translation
                    s = ''
                    for i in range(0, self.__threads):
                        newBlock = 'if(!(' + cond + ')) { goto __exit_loop_%s; }\n' % currentLoopID
                        newBlock += block
                        # Label replacement if applicable
                        for l in self.__labelCount:
                            newBlock = newBlock.replace(l, '%s_%s' % (l, i))
                        # Break and continue replacement
                        if self.__has_break_stmt:
                            newBlock = newBlock.replace(
                                '<break-was-here>', 'goto __exit_loop_%s;' % currentLoopID)
                        if self.__has_continue_stmt:
                            newBlock = newBlock.replace(
                                '<continue-was-here>', 'goto __continue_%s_loop_%s;\n' % (i, currentLoopID))
                            newBlock = newBlock[:newBlock.rfind('}')] + '__continue_%s_loop_%s:;\n' % (i, currentLoopID) + '}\n'
                        s += newBlock
                    # Exit loop
                    s += '__VERIFIER_assume(!(%s));__exit_loop_%s:;\n' % (cond, currentLoopID)
                    return s

                else:
                    # Normal translation
                    s = ''
                    for i in range(0, self.__threads):
                        newBlock = 'if(!(' + cond + ')) { goto __exit_loop_%s; }\n' % currentLoopID
                        newBlock += block
                        # Label replacement if applicable
                        for l in self.__labelCount:
                            newBlock = newBlock.replace(l, '%s_%s' % (l, i))
                        # Break and continue replacement
                        if self.__has_break_stmt:
                            newBlock = newBlock.replace(
                                '<break-was-here>', 'goto __exit_loop_%s;' % currentLoopID)
                        if self.__has_continue_stmt:
                            newBlock = newBlock.replace(
                                '<continue-was-here>', 'goto __continue_%s_loop_%s;\n' % (i, currentLoopID))
                            newBlock = newBlock[:newBlock.rfind('}')] + '__continue_%s_loop_%s:;\n' % (i, currentLoopID) + '}\n'
                        s += newBlock
                    # Exit loop
                    s += '__VERIFIER_assume(!(%s));__exit_loop_%s:;\n' % (cond, currentLoopID)
                    return s
            else:
                # Normal translation
                s = ''
                for i in range(0, self.__threads):
                    newBlock = 'if(!(' + cond + ')) { goto __exit_loop_%s; }\n' % currentLoopID
                    newBlock += block
                    # Label replacement if applicable
                    for l in self.__labelCount:
                        newBlock = newBlock.replace(l, '%s_%s' % (l, i))
                    # Break and continue replacement
                    if self.__has_break_stmt:
                        newBlock = newBlock.replace(
                            '<break-was-here>', 'goto __exit_loop_%s;' % currentLoopID)
                    if self.__has_continue_stmt:
                        newBlock = newBlock.replace(
                            '<continue-was-here>', 'goto __continue_%s_loop_%s;\n' % (i, currentLoopID))
                        newBlock = newBlock[:newBlock.rfind('}')] + '__continue_%s_loop_%s:;\n' % (i, currentLoopID) + '}\n'
                    s += newBlock
                # Exit loop
                s += '__VERIFIER_assume(!(%s));__exit_loop_%s:;\n' % (cond, currentLoopID)
                return s
        else:
            # Normal while loop
            block = block.replace('<break-was-here>', 'break;')
            block = block.replace('<continue-was-here>', 'continue;')
            return 'while (' + cond + ')\n' + block

    def visit_FuncCall(self, n):
        fref = self._parenthesize_unless_simple(n.name)
        args = self.visit(n.args)
        s = fref + '(' + args + ')'
        if fref == 'pthread_create' or fref == 'pthread_join':
            self.__has_pthread_stmt = True
        return s

    def visit_Label(self, n):
        # Labels defined inside loops need to be renamed to
        #   avoid multiple definition of the same label,
        if n.name not in self.__labelCount:
            self.__labelCount[n.name] = 0
        else:
            self.__labelCount[n.name] += 1
        return n.name + ':\n' + self._generate_stmt(n.stmt)

    def visit_Compound(self, n):
        s = self._make_indent() + '{\n'
        self.indent_level += 2
        if n.block_items:
            for stmt in n.block_items:
                s += ''.join(self._generate_stmt(stmt))
                self.__stmtCount += 1
        self.indent_level -= 2
        s += self._make_indent() + '}\n'
        return s

    def visit_Continue(self, n):
        self.__has_continue_stmt = True
        return '<continue-was-here>'

    def visit_Break(self, n):
        self.__has_break_stmt = True
        return '<break-was-here>'

    # ----------------- NEW FEATURES ---------------------------------------------------
    def visit_FuncDef(self, n):
        # At each function
        self.__currentFunction = n.decl.name
        self.__labelCount = {}
        decl = self.visit(n.decl)

        # This is a thread definition
        if n.decl.name in self.Parser.threadName and decl.find('()') != -1:
            newdecl = decl[:decl.rfind(')')]
            newdecl += 'void * arg)'
            decl = newdecl

        self.indent_level = 0
        body = self.visit(n.body)

        # Replace unbounded statement in the sack of CPAChecker rational integer!
        if (n.decl.name == 'main' and len(self.__potentialUnboundedVar) == 1 and
                self.__backend == 'cpachecker'):
            varName = self.__potentialUnboundedVar[-1]
            assignCnt = 0
            functioncallName = ''
            if varName in self.Parser.abs_varValues:
                for i in range(0, len(self.Parser.abs_varValues[varName])):
                    if self.Parser.abs_varValues[varName][i][0] == '=':
                        assignCnt += 1
                    if self.Parser.abs_varValues[varName][i][0] == 'assignCall':
                        assignCnt += 1
                        functioncallName = self.Parser.abs_varValues[varName][i][1]

            if (assignCnt == 1 and  # One time assigned to
                    functioncallName != '' and functioncallName.startswith('__VERIFIER_nondet_')):
                stringtoFind = varName + ' = ' + functioncallName
                stringtoReplace = varName + ' = ' + '%s' % self.__unwindbound
                body = body.replace(stringtoFind, stringtoReplace)

        if n.param_decls:
            knrdecls = ';\n'.join(self.visit(p) for p in n.param_decls)
            self.__currentFunction = ''
            return decl + '\n' + knrdecls + ';\n' + body + '\n'
        else:
            self.__currentFunction = ''
            return decl + '\n' + body + '\n'

    # ----------------------------  CALCULATE LOOP BOUND TYPE 1 ----------------------------------
    # This case is about some loop with bounded value explicitly shown on loop condition
    # for example while (i < 4) {...}
    #
    def _loopIsBounded(self, lvar):
        if lvar in self.__varnames and len(self.__varnames[lvar]) >= 3:
            # Increment statement
            if ((self.__varnames[lvar][-1][0] == 'p++' or self.__varnames[lvar][-1][0] == '++') and
                    (self.__varnames[lvar][-2][0] == '<' or self.__varnames[lvar][-2][0] == '<=') and
                    self.__varnames[lvar][-3][0] == '=' and
                    int(self.__varnames[lvar][-2][1]) >= int(self.__varnames[lvar][-3][1])):
                return True
            # Decrement statement
            if ((self.__varnames[lvar][-1][0] == 'p--' or self.__varnames[lvar][-1][0] == '--') and
                    (self.__varnames[lvar][-2][0] == '>' or self.__varnames[lvar][-2][0] == '>=') and
                    self.__varnames[lvar][-3][0] == '=' and
                    int(self.__varnames[lvar][-2][1]) <= (self.__varnames[lvar][-3][1])):
                return True
            return False
        else:
            return False

    def _calculateLoopTimes(self, lvar):
        if (self.__varnames[lvar][-1][0] == 'p++' or self.__varnames[lvar][-1][0] == '++'):
            times = int(self.__varnames[lvar][-2][1]) - int(self.__varnames[lvar][-3][1])
            if self.__varnames[lvar][-2][0] == '<=':
                return times + 1
            else:
                return times

        if (self.__varnames[lvar][-1][0] == 'p--' or self.__varnames[lvar][-1][0] == '--'):
            times = int(self.__varnames[lvar][-3][1]) - int(self.__varnames[lvar][-2][1])
            if self.__varnames[lvar][-2][0] == '>=':
                return times + 1
            else:
                return times

        return -1

    # ----------------------------  CALCULATE LOOP BOUND TYPE 2 ----------------------------------
    # This case is when loop is bounded by implicitly some value
    # For example n = 4; while (i < n) {...}
    #

    def _loopIsPotentiallyBounded(self, lvar, rvar):
        if (rvar in self.__varnames and len(self.__varnames[rvar]) >= 1 and
                rvar in self.__varnames and len(self.__varnames[rvar]) >= 1):
            index = -1
            for i in range(0, len(self.__varnames[rvar])):
                if (self.__varnames[rvar][i][0] == 'assignCall' or
                        self.__varnames[rvar][i][0] == '='):
                    index = i

            if (index != -1 and self.__varnames[rvar][index][0] == '=' and
                    self._loopIsBounded2(lvar, rvar, index)):
                return True
            return False
        else:
            return False

    def _loopIsBounded2(self, lvar, rvar, index):
        if lvar in self.__varnames and len(self.__varnames[lvar]) >= 3:
            # Increment statement
            if ((self.__varnames[lvar][-1][0] == 'p++' or self.__varnames[lvar][-1][0] == '++') and
                (self.__varnames[lvar][-2][0] == '<' or self.__varnames[lvar][-2][0] == '<=') and
                    self.__varnames[lvar][-3][0] == '='):
                if (self.__varnames[lvar][-2][1] == rvar and
                        utils.is_number(self.__varnames[rvar][index][1]) and
                        utils.is_number(self.__varnames[lvar][-3][1]) and
                        int(self.__varnames[rvar][index][1]) >= int(self.__varnames[lvar][-3][1])):
                    return True
                else:
                    return False

            # Decrement statement
            if ((self.__varnames[lvar][-1][0] == 'p--' or self.__varnames[lvar][-1][0] == '--') and
                (self.__varnames[lvar][-2][0] == '>' or self.__varnames[lvar][-2][0] == '>=') and
                    self.__varnames[lvar][-3][0] == '='):
                if (self.__varnames[lvar][-2][1] == rvar and
                        int(self.__varnames[rvar][index][1]) <= int(self.__varnames[lvar][-3][1])):
                    return True
                else:
                    return False
            return False
        else:
            return False

    def _calculateLoopTimes2(self, lvar, rvar):
        index = -1
        for i in range(0, len(self.__varnames[rvar])):
            if (self.__varnames[rvar][i][0] == 'assignCall' or
                    self.__varnames[rvar][i][0] == '='):
                index = i

        if (self.__varnames[lvar][-1][0] == 'p++' or self.__varnames[lvar][-1][0] == '++'):
            times = int(self.__varnames[rvar][index][1]) - int(self.__varnames[lvar][-3][1])
            if self.__varnames[lvar][-2][0] == '<=':
                return times + 1
            else:
                return times

        if (self.__varnames[lvar][-1][0] == 'p--' or self.__varnames[lvar][-1][0] == '--'):
            times = int(self.__varnames[lvar][-3][1]) - int(self.__varnames[rvar][index][1])
            if self.__varnames[lvar][-2][0] == '>=':
                return times + 1
            else:
                return times

        return -1

    # ----------------------------  CALCULATE LOOP BOUND TYPE 3 ----------------------------------
    def _loopIsPotentiallyUnbounded(self, lvar, rvar):
        if (lvar in self.__varnames and len(self.__varnames[lvar]) >= 3 and
                rvar in self.__varnames and len(self.__varnames[rvar]) >= 1):
            # Find the last index that is an assign call
            index = -1
            for i in range(0, len(self.__varnames[rvar])):
                if (self.__varnames[rvar][i][0] == 'assignCall' or
                        self.__varnames[rvar][i][0] == '='):
                    index = i

            if index != -1 and self.__varnames[rvar][index][0] == 'assignCall':
                fref = self.__varnames[rvar][index][1]
                fref = fref[:fref.find('(')]  # Get function name
                if fref.startswith('__VERIFIER_nondet_'):
                    return True
            return False
        else:
            return False

    # ----------------------------  HELPER FUNCTIONS ----------------------------------
    def _visit_expr(self, n):
        if isinstance(n, c_ast.InitList):
            return '{' + self.visit(n) + '}'
        elif isinstance(n, c_ast.ExprList):
            return '(' + self.visit(n) + ')'
        else:
            return self.visit(n)
