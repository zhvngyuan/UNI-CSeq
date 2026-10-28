# ------------------------------------------------------------------------------
# NAME = abs_tomicitizer
# -----------------------------------------------------------------------------
# VERSION = 0.2
# -----------------------------------------------------------------------------
# Description:
#   This module turns function calls in atomic region into
#       __VERIFIER_atomic_function
#
#   Additional features:
#      + Decompose multiple assignment in one line into multiple lines
#
# TODO:
#   Fix name __VERIFIER_atomic_cseq_ for CBMC
# Changelog:
#
# -----------------------------------------------------------------------------

from pycparser import c_ast
from abs_module import ABS_Module


class ABS_Atomicitizer(ABS_Module):
    __currentFunct = ''
    __lvals = []

    # --------------------------- ATOMICIZE FUNCTION -------------------------
    def visit_FuncCall(self, n):
        fref = self._parenthesize_unless_simple(n.name)
        if (fref in self.Parser.abs_atomicLikeFunc and
                fref in self.Parser.funcBody and
                not fref.startswith('__VERIFIER_')):
            fref = '__VERIFIER_atomic_cseq_' + fref

        return fref + '(' + self.visit(n.args) + ')'

    def visit_FuncDef(self, n):
        self.__currentFunct = n.decl.name
        decl = self.visit(n.decl)
        if (n.decl.name in self.Parser.abs_atomicLikeFunc and
                n.decl.name in self.Parser.funcBody and
                not n.decl.name.startswith('__VERIFIER_')):
            decl = decl.replace(n.decl.name, '__VERIFIER_atomic_cseq_' + n.decl.name, 1)
        self.indent_level = 0
        body = self.visit(n.body)
        if n.param_decls:
            knrdecls = ';\n'.join(self.visit(p) for p in n.param_decls)
            self.__currentFunct = ''
            return decl + '\n' + knrdecls + ';\n' + body + '\n'
        else:
            self.__currentFunct = ''
            return decl + '\n' + body + '\n'

    def visit_Decl(self, n, no_type=False):
        # no_type is used when a Decl is part of a DeclList, where the type is
        # explicitly only for the first delaration in a list.
        #
        s = n.name if no_type else self._generate_decl(n)

        if (self.__currentFunct == '' and
                n.name in self.Parser.abs_atomicLikeFunc and
                n.name in self.Parser.funcBody and
                not n.name.startswith('__VERIFIER_')):
            s = s.replace(n.name, '__VERIFIER_atomic_cseq_' + n.name, 1)

        if n.bitsize:
            s += ' : ' + self.visit(n.bitsize)
        if n.init:
            s += ' = ' + self._visit_expr(n.init)
        return s

    def _visit_expr(self, n):
        if isinstance(n, c_ast.InitList):
            return '{' + self.visit(n) + '}'
        elif isinstance(n, c_ast.ExprList):
            return '(' + self.visit(n) + ')'
        else:
            return self.visit(n)

    # --------------------------- END OF ATOMICIZE FUNCTION -------------------------
    # --------------------------- DECOMPOSE ASSIGNMENT -------------------------
    def visit_Assignment(self, n):
        self.__lvals = []
        self.__lvals.append((n.lvalue, n.op))
        rval_str = self._visit_Assignment(n.rvalue)
        self.__lvals.reverse()
        s = ''
        if len(self.__lvals) > 1:
            for i in range(0, len(self.__lvals)):
                if i == 0:
                    s += '%s %s %s' % (self.visit(self.__lvals[i][0]), self.__lvals[i][1], rval_str)
                else:
                    s += self._make_indent(delta=0) + '%s %s %s' % (self.visit(self.__lvals[i][0]),
                                                                    self.__lvals[i][1], self.visit(self.__lvals[i - 1][0]))
                if i != len(self.__lvals) - 1:
                    s += ';\n'
        else:
            s += '%s %s %s' % (self.visit(n.lvalue), n.op, rval_str)
        return s

    def _visit_Assignment(self, n):
        if type(n) == c_ast.Assignment:
            self.__lvals.append((n.lvalue, n.op))
            return self._visit_Assignment(n.rvalue)
        else:
            return self.visit(n)
    # --------------------------- DECOMPOSE ASSIGNMENT -------------------------
