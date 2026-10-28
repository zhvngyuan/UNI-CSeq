# -----------------------------------------------------------------------------
# NAME = abs_extractor
# -----------------------------------------------------------------------------
# VERSION = 0.2
# -----------------------------------------------------------------------------
# Description:
#     This is based on extractor.py of Lazy-cseq
#
#     Extracting function call from condition to prepare for inlining
#     Transformation from:
#        if (complex_cond) { block }
#        while (complex_cond) { block }
#     respectively into:
#        _Bool tmp = complex_cond  if (tmp) { block }
#        _Bool tmp = complex_cond  while (tmp) { block; tmp = complex_cond }
#
#     where an expression is considered to be complex if
#     it contains calls to functions which body is defined in the source.
#
#    Note that: in case of these STMTs are in __VERIFIER_atomic or __VERIFIER_nondet
#     We will not do anything
#
#    Additional Features:
#      Extracts pthread functions family from conditional statement
#       e.g.
#           if (0 != (err = pthread_mutex_init(data1Lock, NULL))) {
#               fprintf(stderr, "pthread_mutex_init error: %d\n", err);
#               exit(-1);
#           }
#       becoming ....
#               pthread_mutex_init(data1Lock, NULL);
#               if_cond = 0 != (err = 0);
#               if (if_cond)
#               {
#                   ...
#               }
#               and replace that function with return value 0 (assuming always success)
#      assuming that calls to pthread function family are always sucessful
#
# TODO:
#
# Changelog:
#
# -----------------------------------------------------------------------------

from abs_module import ABS_Module


class ABS_Extractor(ABS_Module):
    # INDENT_SPACING = ' '
    funcCallFound = False

    ifCondCount = whileCondCount = forCondCount = 0

    pthreadCallFound = False
    pthreadCallString = ''

    def visit_If(self, n):
        extraBlock = ''
        s = 'if ('
        if n.cond:
            self.funcCallFound = False
            self.pthreadCallFound = False
            cond = self.visit(n.cond)

            if self.funcCallFound:
                extraBlock += 'static _Bool __if_cond_%s; __if_cond_%s = (%s); ' % (
                    self.ifCondCount, self.ifCondCount, cond)

                if self.pthreadCallFound:
                    extraBlock = extraBlock.replace(self.pthreadCallString, '0', 1)
                    extraBlock = self.pthreadCallString + ';\n' + extraBlock
                    self.pthreadCallString = ''

                s += '__if_cond_%s' % (self.ifCondCount)
                s = extraBlock + '\n' + self._make_indent() + s
                self.ifCondCount += 1
            else:
                s += cond

        s += ')\n'

        t = self._generate_stmt(n.iftrue, add_indent=True)

        # add brakets for single non parenthesised statements after if
        if not t.startswith(self._make_indent() + ('{\n')):
            t = self._make_indent() + '{\n' + t + self._make_indent() + '}\n'

        s += t

        if n.iffalse:
            s += self._make_indent() + 'else\n'
            e = self._generate_stmt(n.iffalse, add_indent=True)

            # add brakets for single non parenthesised statements after if
            if not e.startswith(self._make_indent() + ('{\n')):
                e = self._make_indent() + '{\n' + e + self._make_indent() + '}\n'
            s += e
        return s

    def visit_While(self, n):
        extraBlock = ''
        cond = ''

        s = 'while ('

        t = self._generate_stmt(n.stmt, add_indent=True)

        if n.cond:
            self.funcCallFound = False
            self.pthreadCallFound = False
            cond = self.visit(n.cond)

            if self.funcCallFound:
                extraBlock += 'static _Bool __while_cond_%s; __while_cond_%s = (%s); ' % (
                    self.whileCondCount, self.whileCondCount, cond)

                if self.pthreadCallFound:
                    extraBlock = extraBlock.replace(self.pthreadCallString, '0', 1)
                    extraBlock = self.pthreadCallString + ';\n' + extraBlock
                    self.pthreadCallString = ''

                s += '__while_cond_%s' % (self.whileCondCount)
                s = extraBlock + '\n' + self._make_indent() + s
                s += ')\n'

                # add brakets for single non parenthesised statements after if
                if not t.startswith(self._make_indent() + ('{\n')):
                    t = self._make_indent() + '{\n' + t + self._make_indent() + '}\n'

                t = t[:t.rfind('}')]
                t = t + self._make_indent() + '__while_cond_%s = (%s);\n' % (
                    self.whileCondCount, cond)
                t = t + self._make_indent() + '}'

                self.whileCondCount += 1
            else:
                s += cond
                s += ')\n'

                # add brakets for single non parenthesised statements after if
                if not t.startswith(self._make_indent() + ('{\n')):
                    t = self._make_indent() + '{\n' + t + self._make_indent() + '}\n'

        return s + t

    def visit_FuncCall(self, n):
        fref = self._parenthesize_unless_simple(n.name)
        args = self.visit(n.args)

        if (fref in self.Parser.funcBody and not fref.startswith('__VERIFIER_atomic') or
                fref.startswith('pthread_')):
            self.funcCallFound = True

        if n.args is None:
            self.lastFuncParams = []
        inl = fref + '(' + args + ')'

        if fref.startswith('pthread'):
            self.pthreadCallFound = True
            self.pthreadCallString = inl

        return inl
