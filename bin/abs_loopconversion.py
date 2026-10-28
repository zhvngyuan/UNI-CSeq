# ------------------------------------------------------------------------------
# NAME = abs_loopconversion
# ------------------------------------------------------------------------------
# VERSION = 0.2
# -----------------------------------------------------------------------------
# Description:
#     Handling:
#           main(void)  --> main()
#           main(int argc, char* argv[]) --> main(void) {int argc; char* argv}
#           removing all statements have argc
#               if (argc != something)
#               {}
#
#
#     Based on remover module of Lazy-cseq
#     Convert every loop into while loop
#       -case 1: transform do..while  loops into equivalent  while  loops:
#                     do { block } while (cond)
#                     -->
#
#                     int i=0; // Special unique name here
#                     while (i < 1)
#                       {block;i++};
#                     while(cond) {block} // other iterations
#
#       -case 2, transform unbounded for loops into equivalent  while  loops:
#                     for (;;) { block }       -->   while(1) { block }
#
#       -case 3, transform potentially unbounded  for  loops into equivalent  while  loops:
#                     for (;stmt;) { block }   -->   while(stmt) { block }
#       -case 4, transform normal for loop into equivalent   while loop:
#                     for (init, cond, incr) {block} --------> init; while(cond){block;incr;}
#
#
#     Add additional feature:
#       Based on spinlook.py of Lazy-cseq with default feature
#               remove spin-looks:
#                   while (cond) {}    --->     assume(!cond);
#               which is safe to do only when  cond   has no side-effects.
#
# Limitations:
#   Currently, this model support ANSI C (C89) so there is no declaration inside for loop
#       if so, there might be a chance of redeclaration in a function
#
# TODO:
#   Fix this situation:
#       label:: do...while(); --> label:; int
# Changelog:
#
# -----------------------------------------------------------------------------

from pycparser import c_ast
from abs_module import ABS_Module
import re


class ABS_Loopconversion(ABS_Module):
    INDENT_SPACING = ' '

    __debug = False

    # Count do..while loops
    __currentLoop = 0
    parsingSideEffect = False   # set when parsing a statement with side effects
    # (i.e., function call, assignment, unary op)
    __currentFunct = ''

    def visit_DoWhile(self, n):
        self.__currentLoop += 1
        var = '__cs_dowhile_onetime_%s' % self.__currentLoop
        # Block of stmts in do..while {block}
        block = self._generate_stmt(n.stmt, add_indent=True)
        cond = self.visit(n.cond) if n.cond else ''
        # One loop only for do
        s = 'int %s = 0;\n' % var
        s += self._make_indent() + 'while (%s < 1)\n' % var
        if not block.startswith(self._make_indent() + ('{\n')):
            block = self._make_indent() + '{\n' + block + self._make_indent() + '}\n'
        extrablock = block[:block.rfind('}')]
        extrablock += self._make_indent(delta=2) + '%s++;\n' % var
        extrablock += self._make_indent() + '}\n'
        s += extrablock
        # While statement
        s += self._make_indent() + 'while (%s)\n' % self.visit(n.cond)
        s += block
        return s

    def visit_For(self, n):
        init = self.visit(n.init) if n.init else ''
        cond = self.visit(n.cond) if n.cond else ''
        next = self.visit(n.next) if n.next else ''
        block = self._generate_stmt(n.stmt, add_indent=True)
        if not block.startswith(self._make_indent() + ('{\n')):
            block = self._make_indent() + '{\n' + block + self._make_indent() + '}\n'

        if not n.init and not n.cond and not n.next:  # unbounded for
            s = 'while(1)' + block
        elif not n.init and not n.next:  # potentially unbounded for
            s = 'while(%s)' % cond + block
        else:  # potentially bounded for
            s = self._make_indent() + '%s;\n' % init
            s += self._make_indent() + 'while (%s)' % cond
            block = block[:block.rfind('}')]
            block += self._make_indent(delta=2) + '%s;\n' % next
            block += self._make_indent() + '}\n'
            s += block
        return s

    def visit_FuncDef(self, n):
        self.__currentFunct = n.decl.name

        decl = self.visit(n.decl)
        self.indent_level = 0
        body = self.visit(n.body)

        # Transforming main function call
        if n.decl.name == 'main':
            # Change *argv[] and argv[][] --> **argv
            args = self.Parser.funcBlockIn['main']
            args = re.sub(r'\*(.*)\[\]', r'** \1', args)
            args = re.sub(r'(.*)\[\]\[\]', r'** \1', args)
            decl = re.sub(r' main(.*)', r' main()', decl)
            # TODO: need proper implementation
            # if args.find('void') == -1 and args != '':
            #     body = body[body.find('{')+1:]
            #     body = '{\n' + args.replace(',', ';')+';' + body

        if n.param_decls:
            knrdecls = ';\n'.join(self.visit(p) for p in n.param_decls)
            self.__currentFunct = ''
            return decl + '\n' + knrdecls + ';\n' + body + '\n'
        else:
            self.__currentFunct = ''
            return decl + '\n' + body + '\n'

    def visit_If(self, n):
        s = 'if ('
        if n.cond:
            cond = self.visit(n.cond)
            s += cond
        s += ')\n'
        s += self._generate_stmt(n.iftrue, add_indent=True)

        # Removing all statements that concerning about argc
        if (self.__currentFunct == 'main' and n.cond):
            if type(n.cond) == c_ast.BinaryOp and cond.find('argc') != -1:
                return ''

        if n.iffalse:
            t = self._generate_stmt(n.iffalse, add_indent=True)
            # add brakets for single non parenthesised statements after if
            if not t.startswith(self._make_indent() + ('{\n')):
                t = self._make_indent() + '{\n' + t + self._make_indent() + '}\n'

            if type(n.iffalse) in (c_ast.EmptyStatement,):
                t = ''
            else:
                t = self._make_indent() + 'else\n' + t
            s += t

        return s

    def visit_FuncCall(self, n):
        self.parsingSideEffect = True
        fref = self._parenthesize_unless_simple(n.name)
        return fref + '(' + self.visit(n.args) + ')'

    def visit_While(self, n):
        self.parsingSideEffect = False
        s = 'while ('
        if n.cond:
            s += self.visit(n.cond)
        s += ')\n'
        t = self._generate_stmt(n.stmt, add_indent=True)
        if not t.startswith(self._make_indent() + ('{\n')):      # add brakets for single non parenthesised statements after if
            t = self._make_indent() + '{\n' + t + self._make_indent() + '}\n'

        if not self.parsingSideEffect:
            if (not n.stmt.block_items or
                    (n.stmt.block_items and len(n.stmt.block_items) == 1 and
                        type(n.stmt.block_items[0]) == c_ast.EmptyStatement)):
                s = s.replace('while (', 'assume(!(', 1)
                s = s[:len(s) - 2] + '));\n'
                t = ''
        s += t
        return s

    def visit_UnaryOp(self, n):
        self.parsingSideEffect = True
        operand = self._parenthesize_unless_simple(n.expr)
        if n.op == 'p++':
            return '%s++' % operand
        elif n.op == 'p--':
            return '%s--' % operand
        elif n.op == 'sizeof':
            # Always parenthesize the argument of sizeof since it can be
            # a name.
            return 'sizeof(%s)' % self.visit(n.expr)
        else:
            return '%s%s' % (n.op, operand)

    def visit_Assignment(self, n):
        self.parsingSideEffect = True
        rval_str = self._parenthesize_if(
            n.rvalue,
            lambda n: isinstance(n, c_ast.Assignment))

        return '%s %s %s' % (self.visit(n.lvalue), n.op, rval_str)

    # Fix problem when do while loop has label
    def visit_Label(self, n):
        if type(n.stmt) != c_ast.DoWhile:
            return n.name + ':\n' + self._generate_stmt(n.stmt)
        else:
            return n.name + ':;\n' + self._generate_stmt(n.stmt)
