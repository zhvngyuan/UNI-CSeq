# ------------------------------------------------------------------------------
# NAME = abs_simplifier
# ------------------------------------------------------------------------------
# VERSION = 0.2
# -----------------------------------------------------------------------------
# Description:
#   This module will simplify some of obstructions in source file
#
#    - Change the name of thread local variable to
#      facilitate thread duplication
#
#    - Ignorant of fprintf, printf, sscanf, ...
#
#    - Simplify expression of constant integers
#    - Strip of name of the parameters in a pointer-to-function when passing it to
#       another function
#       e.g. int f (int (*g)(int *a, int))
#            -->
#            int f (int (*g)(int *, int))
#    - Handling error label
#           - goto ERROR; ---> __VERIFIER_assert(0);
#           - ERROR :;    ----> __VERIFIER_assert(0);
#
# TODO:
#   + Removing function call definition to
#           __VERIFIER_error
#           and __VERIFIER_assert
#
#   + Multiple form of integer literal to facility CONCURINTEPROC
#           e.g. 100u
#               0xfee
#
# Changelog:
#
# -----------------------------------------------------------------------------

from pycparser import c_parser, c_ast
from abs_module import ABS_Module
import abs_common


class ABS_Simplifier(ABS_Module):
    # INDENT_SPACING = ' '
    __stack = []
    __errorlabel = 'ERROR'

    # For thread local
    __parsingFunction = False
    __threadLocals = []

    def loadfromstring(self, string, env):
        if env is not None:
            self.__errorlabel = env.errorlabel
        self.ast = c_parser.CParser().parse(string)
        self.output = self.visit(self.ast)

    def visit(self, node):
        method = 'visit_' + node.__class__.__name__
        self.__stack.append(node.__class__.__name__)
        retval = getattr(self, method, self.generic_visit)(node)
        self.__stack.pop()
        return retval

    def visit_BinaryOp(self, n):
        lval_str = self._parenthesize_if(n.left, lambda d: not self._is_simple_node(d))
        rval_str = self._parenthesize_if(n.right, lambda d: not self._is_simple_node(d))

        if self._isInteger(lval_str) and self._isInteger(rval_str):
            if n.op == '-':
                return str(int(lval_str) - int(rval_str))
            if n.op == '+':
                return str(int(lval_str) + int(rval_str))
            if n.op == '*':
                return str(int(lval_str) * int(rval_str))
            if n.op == '/':
                return str(int(lval_str) / int(rval_str))

        return '%s %s %s' % (lval_str, n.op, rval_str)

    # ---------------------   REDUNDANT FUNCCALL HANDLING -----------------------------------
    def visit_FuncCall(self, n):
        fref = self._parenthesize_unless_simple(n.name)
        if (fref == 'fprintf' or
                fref == 'printf' or
                fref == 'sscanf'):
            return ''
        return fref + '(' + self.visit(n.args) + ')'

    # ---------------------   REDUNDANT FUNCCALL HANDLING -----------------------------------

    # ---------------------   THREAD LOCAL VARIABLE HANDLING -----------------------------------
    def visit_Decl(self, n, no_type=False):
        # no_type is used when a Decl is part of a DeclList, where the type is
        # explicitly only for the first delaration in a list.
        #
        s = n.name if no_type else self._generate_decl(n)

        if n.bitsize:
            s += ' : ' + self.visit(n.bitsize)

        if n.init:
            if isinstance(n.init, c_ast.InitList):
                s += ' = {' + self.visit(n.init) + '}'
            elif isinstance(n.init, c_ast.ExprList):
                s += ' = (' + self.visit(n.init) + ')'
            else:
                s += ' = ' + self.visit(n.init)

        if (n.name is not None and
                n.name.startswith(abs_common.namespace['threadlocal'])):  # Thread local variable
            varname = n.name
            self.__threadLocals.append(varname.replace(abs_common.namespace['threadlocal'], ''))
            # print "FOUND %s --> %s\n" % (n.name, varname)
        return s

    def visit_ID(self, n):
        if n.name in self.__threadLocals:
            return abs_common.namespace['threadlocal'] + n.name + '[' + abs_common.namespace['threadid'] + ']'
        else:
            return n.name
    # ---------------------   THREAD LOCAL VARIABLE HANDLING -----------------------------------

    # ---------------------   ERROR LABEL HANDLING -----------------------------------
    def visit_Goto(self, n):
        if n.name == self.__errorlabel:
            return '__VERIFIER_error();'
        else:
            return 'goto ' + n.name + ';'

    def visit_Label(self, n):
        if n.name == self.__errorlabel:
            return '__VERIFIER_error();'
        else:
            return n.name + ':\n' + self._generate_stmt(n.stmt)

    # ---------------------   ERROR LABEL HANDLING -----------------------------------

    # --------------------- HELPER FUNCTION FOR REMOVING 2LEVEL PARAMETER  -----------
    def _generate_type(self, n, modifiers=[]):
        """ Recursive generation from a type node. n is the type node.
            modifiers collects the PtrDecl, ArrayDecl and FuncDecl modifiers
            encountered on the way down to a TypeDecl, to allow proper
            generation from it.
        """
        typ = type(n)
        #~ print(n, modifiers)

        retstr = ''

        if typ == c_ast.TypeDecl:
            s = ''
            if n.quals:
                s += ' '.join(n.quals) + ' '
            s += self.visit(n.type)

            nstr = n.declname if n.declname else ''
            # Resolve modifiers.
            # Wrap in parens to distinguish pointer to array and pointer to
            # function syntax.
            #
            for i, modifier in enumerate(modifiers):
                if isinstance(modifier, c_ast.ArrayDecl):
                    if (i != 0 and isinstance(modifiers[i - 1], c_ast.PtrDecl)):
                        nstr = '(' + nstr + ')'
                    nstr += '[' + self.visit(modifier.dim) + ']'
                elif isinstance(modifier, c_ast.FuncDecl):
                    if (i != 0 and isinstance(modifiers[i - 1], c_ast.PtrDecl)):
                        nstr = '(' + nstr + ')'
                    nstr += '(' + self.visit(modifier.args) + ')'
                elif isinstance(modifier, c_ast.PtrDecl):
                    if modifier.quals:
                        nstr = '* %s %s' % (' '.join(modifier.quals), nstr)
                    else:
                        nstr = '*' + nstr
            if nstr:
                s += ' ' + nstr
            retstr = s
            # When generating nested parameter declarations,
            # strip off the names of the parameters
            # (e.g. names of parameters in a pointer to function).
            #
            if self.__stack.count('ParamList') > 1 and n.declname:
                retstr = retstr[:retstr.rfind(str(n.declname))]
                if retstr[-1] == ' ':
                    retstr = retstr[:-1]
        elif typ == c_ast.Decl:
            retstr = self._generate_decl(n.type)
        elif typ == c_ast.Typename:
            retstr = self._generate_type(n.type)
        elif typ == c_ast.IdentifierType:
            retstr = ' '.join(n.names) + ' '
        elif typ in (c_ast.ArrayDecl, c_ast.PtrDecl, c_ast.FuncDecl):
            retstr = self._generate_type(n.type, modifiers + [n])
        else:
            retstr = self.visit(n)

        return retstr

    def _isInteger(self, s):
        if s[0] in ('-', '+'):
            return s[1:].isdigit()
        else:
            return s.isdigit()
