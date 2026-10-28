# -----------------------------------------------------------------------------
# NAME = abs_preprocessor
# -----------------------------------------------------------------------------
# VERSION = 0.2
# -----------------------------------------------------------------------------
# Description:
#   Based on merger of Lazy-cseq
#   - Preprocessing C file
#   - Inherit from Merger Module
#       split decl into mutiple line
#           int x, y --> int x; int y;
#
#   - Preprocess C file
#       + header file handler
#       + macro expansion
#       + remove qualifier
#           + auto inline volatile register
#           + static
#       + remove dead code
#           + if (!1) {} if(0){} while(0){}
#       + add brackets to single-statements blocks
#           + for (...) stmt; --> for (...) {stmt;}
#           + if (...) else if; --> if (...) else {if}
# TODO:
#   - Handling weirdo non-standard GNU C extensions
#
#
# Changelog:
#
# -----------------------------------------------------------------------------

from pycparser import c_ast, c_parser
from abs_module import ABS_Module
import re
import subprocess
import shlex
import os.path


class ABS_Preprocessor(ABS_Module):
    # INDENT_SPACING = ' '
    indent_level = 0            # to keep track of the depth of the block {}

    ___inputfilename = ''
    __output = ''

    __parsingFunction = False

    need_gnu_fix = False

    currentAnonStructsCount = 0   # counts the number of anonymous structures
    # (used to assign consecutive names)

    def loadfromstring(self, string, env=None):
        # Preprocess the string
        string = self._sanitise(string)
        # utils.saveFile('___0_original.1.c', string)

        includeDir = "./include"
        cmdline = 'gcc -I%s -P -E - ' % includeDir  # hyphen at the end forces input from stdin
        p = subprocess.Popen(shlex.split(cmdline), stdout=subprocess.PIPE,
                             stdin=subprocess.PIPE, stderr=subprocess.PIPE)
        out = p.communicate(input=string)[0]
        # p.stdin.close()

        if self.need_gnu_fix:
            out = self._gnu_extension_fix(out)

        # utils.saveFile('___0_original.2.c', out)

        print out

        parser = c_parser.CParser()
        self.ast = parser.parse(out)
        self.__output = self.visit(self.ast)

    def save(self, filename):
        outfile = open(filename, "w")
        outfile.write(self.__output)
        outfile.close()

    def show(self):
        print(self.__output)

    def string(self):
        return self.__output

    def showAST(self):
        self.ast.show(attrnames=True)

    def visit_Decl(self, n, no_type=False):
        # no_type is used when a Decl is part of a DeclList, where the type is
        # explicitly only for the first delaration in a list.
        #
        s = n.name if no_type else self._generate_decl(n)

        if n.bitsize:
            s += ' : ' + self.visit(n.bitsize)

        # when an init expression is used,
        # remove it from the declaration statement and insert a separate
        # statement for the assignment.
        #
        assignmentStmt = ''

        if n.init:
            if isinstance(n.init, c_ast.InitList):
                assignmentStmt = ' = {' + self.visit(n.init) + '}'
            elif isinstance(n.init, c_ast.ExprList):
                assignmentStmt = ' = (' + self.visit(n.init) + ')'
            else:
                assignmentStmt = ' = ' + self.visit(n.init)

        # Remove storage class keywords from any declaration,
        # as they are not used at all in this tool for verification.
        #
        if s.startswith('auto '):
            s = s[5:]
        if s.startswith('inline '):
            s = s[7:]
        if s.startswith('volatile '):
            s = s[9:]
        if s.startswith('register '):
            s = s[9:]

        # Split the declaration statement from initialization statement.
        #
        '''
        if self.__parsingFunction and n.init:
            return s + '; ' + n.name + assignmentStmt
        else:
            return s + assignmentStmt
        '''
        return s + assignmentStmt

    def visit_FuncDef(self, n):
        self.__parsingFunction = True

        decl = self.visit(n.decl)

        # print "decl: %s\n" % decl

        if decl.startswith('static '):
            decl = decl[7:]

        self.indent_level = 0
        body = self.visit(n.body)

        if n.param_decls:
            knrdecls = ';\n'.join(self.visit(p) for p in n.param_decls)
            self.__parsingFunction = False
            return decl + '\n' + knrdecls + ';\n' + body + '\n'
        else:
            self.__parsingFunction = False
            return decl + '\n' + body + '\n'

    def visit_If(self, n):
        cond = ''

        s = 'if ('
        cond = self.visit(n.cond)
        if n.cond:
            s += cond
        s += ')\n'

        # Eliminate dead code
        if cond == '0' or cond == '!1':
            return ''

        t = self._generate_stmt(n.iftrue, add_indent=True)

        if not t.startswith(self._make_indent() + ('{\n')):   # always add brackets when missing
            t = self._make_indent() + '{\n' + t + self._make_indent() + '}\n'

        s += t

        if (cond == '!0' and not n.iffalse):
            return t

        if n.iffalse:
            s += self._make_indent() + 'else\n'
            e = self._generate_stmt(n.iffalse, add_indent=True)

            if not e.startswith(self._make_indent() + ('{\n')):   # always add brackets when missing
                e = self._make_indent() + '{\n' + e + self._make_indent() + '}\n'

            s += e

        return s

    def visit_For(self, n):
        s = 'for ('

        if n.init:
            s += self.visit(n.init)

        s += ';'

        if n.cond:
            s += ' ' + self.visit(n.cond)

        s += ';'

        if n.next:
            s += ' ' + self.visit(n.next)

        s += ')\n'
        t = self._generate_stmt(n.stmt, add_indent=True)

        if not t.startswith(self._make_indent() + ('{\n')):   # always add brackets when missing
            t = self._make_indent() + '{\n' + t + self._make_indent() + '}\n'

        return s + t

    def visit_While(self, n):
        s = 'while ('

        if n.cond:
            s += self.visit(n.cond)

        s += ')\n'

        t = self._generate_stmt(n.stmt, add_indent=True)

        if not t.startswith(self._make_indent() + ('{\n')):   # always add brackets when missing
            t = self._make_indent() + '{\n' + t + self._make_indent() + '}\n'

        return s + t

    def visit_DoWhile(self, n):
        s = 'do\n'

        t = self._generate_stmt(n.stmt, add_indent=True)

        if not t.startswith(self._make_indent() + ('{\n')):   # always add brackets when missing
            t = self._make_indent() + '{\n' + t + self._make_indent() + '}\n'

        s += t
        s += self._make_indent() + 'while ('

        if n.cond:
            s += self.visit(n.cond)

        s += ');'

        return s

    def visit_Struct(self, n):
        # Assign a name to anonymous structs
        if n.name is None:
            n.name = 'anonstruct_' + str(self.currentAnonStructsCount)
            self.currentAnonStructsCount += 1

        return self._generate_struct_union(n, 'struct')

    def _sanitise(self, input):
        lines = input.splitlines()
        text = ''

        # Fix thread local variable
        for line in lines:
            line = re.sub(r'__thread _Bool (.*) = 0', r'_Bool __cs_thread_local_\1[THREADS] ', line)
            line = re.sub(r'_Thread_local _Bool (.*) = 0', r'_Bool __cs_thread_local_\1[THREADS] ', line)
            text += line + '\n'

            if not self.need_gnu_fix and "typeof" in line:
                self.need_gnu_fix = True

        # get rid of non-standard GNU C extensions by inserting preprocessor directives
        # that will cause such extensions to be preprocessed out
        #
        text = text.replace('__const ', 'const ')
        text = text.replace('__inline ', 'inline ')
        text = text.replace('__extension__', '')
        text = text.replace('__restrict', '')

        text = '#define __extension__(x)\n' + text
        text = '#define __attribute__(x)\n' + text
        text = '#define __asm__(x)\n' + text
        text = '#define __builtin_va_list int\n' + text

        return text

    def _gnu_extension_fix(self, input):
        text = ''
        ''' 1. Fix Empty Structure (partial for some particular benchmarks in svcomp16)
        https://gcc.gnu.org/onlinedocs/gcc/Empty-Structures.html
        '''
        text = input.replace('''\
struct device {
};''', '''\
struct device {
    char unused;
};''')

        ''' 2. Fix typeof (partial for some particular benchmarks in svcomp16)
        https://gcc.gnu.org/onlinedocs/gcc/Typeof.html#Typeof
        '''
        text = text.replace("typeof( ((struct my_data *)0)->dev )", "struct device ")

        ''' 3. Fix Statement Expression (partial for some particular benchmarks in svcomp16)
        https://gcc.gnu.org/onlinedocs/gcc/Statement-Exprs.html#Statement-Exprs
        '''
        ret = ''
        for l in text.splitlines():
            if "({" in l:
                m = re.match(r'^(.+)\({(.*)}\)', l)
                newline = ''
                if m:
                    firstpart = m.group(1)
                    secondpart = m.group(2)
                    stmts = secondpart.split(";")
                    stmts = stmts[:-1]
                    firstpart += stmts[-1] + ';'
                    stmts = stmts[:-1]
                    for s in stmts:
                        newline += s + '; '
                    newline += firstpart
                else:
                    newline = l
                ret += newline + '\n'
            else:
                ret += l + '\n'

        return ret
