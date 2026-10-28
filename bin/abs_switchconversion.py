# ------------------------------------------------------------------------------
# NAME = abs_switchconversion
# -----------------------------------------------------------------------------
# VERSION = 0.2
# -----------------------------------------------------------------------------
# Description:
#   Additional features:
#       removing empty statement
#
# 	Convert switch stmt to if ... else with goto label
#
#   switch (x) {      will be come
#       case a:            ==>               if (x == a)
#           block1;        ==>               {
#           break;         ==>                   block1;
#           block0;        ==>                   goto exit_switch;
#                          ==>                   block0;
#                          ==>               }
#      case b:             ==>               if (x == b)
#          block2;         ==>               {
#          break;          ==>                   label_b:;
#                          ==>                   block2;
#                          ==>                   goto exit_switch;
#                          ==>                   goto label_c;
#                          ==>               }
#      case c:             ==>               if(x == c)
#          block3;         ==>               {
#                          ==>                   label_c:;
#                          ==>                   block 3;
#                          ==>                   goto label_d;
#                          ==>               }
#      case d:             ==>               if (x == d)
#          block4;         ==>               {
#                          ==>                   label_d:;
#                          ==>                   block4;
#                          ==>                   goto label_default;
#                          ==>               }
#      default:            ==>               if (! (x == a || x == b || x == c || x == d))
#          block5;         ==>               {
#                          ==>                   label_default:;
#   }                      ==>                   block5;
#                          ==>               }
#                                            exit_switch:;
#
# TODO:
#    add loadfromstring to removing overhead
# Changelog:
#
# -----------------------------------------------------------------------------

from pycparser import c_ast, c_parser
from abs_module import ABS_Module, ModuleError


class ABS_Switchconversion(ABS_Module):
    # INDENT_SPACING = ' '
    __stack = []
    __currentSwitchCount = 0
    __currentSwitchVar = []
    __currentSwitchExprALL = []
    __caseCount = {}

    def loadfromstring(self, string, env):
        self.ast = c_parser.CParser().parse(string)
        self.output = self.visit(self.ast)

    def string(self):
        return self.output

    def save(self, filename):
        outfile = open(filename, "w")
        outfile.write(self.output)
        outfile.close()

    def show(self):
        print(self.output)

    def visit(self, node):
        method = 'visit_' + node.__class__.__name__
        self.__stack.append(node.__class__.__name__)
        retval = getattr(self, method, self.generic_visit)(node)
        self.__stack.pop()
        return retval

    def visit_Switch(self, n):
        # Increase ID of switch
        cond = self.visit(n.cond)
        self.__currentSwitchCount += 1
        self.__currentSwitchVar.append(cond)
        self.__caseCount[self.__currentSwitchCount] = 0
        self.__currentSwitchExprALL.append([])
        s = self._generate_stmt(n.stmt, add_indent=True)
        s = s[s.find('{') + 1:s.rfind('}')]
        endCaseNumber = self.__caseCount[self.__currentSwitchCount] + 1
        switchEndLabel = '__switch_%s_case_%s' % (self.__currentSwitchCount, endCaseNumber)
        switchEndLabelFinal = '__switch_%s_exit' % self.__currentSwitchCount
        s += self._make_indent() + switchEndLabel + ':;'
        breakLabel = '<case-break-of-switch%s>' % self.__currentSwitchCount
        self.__currentSwitchExprALL.pop()
        self.__currentSwitchVar.pop()
        self.__currentSwitchCount -= 1
        s = s.replace(breakLabel, 'goto %s;' % switchEndLabel)
        s = s.replace(switchEndLabel, switchEndLabelFinal)
        return s

    def visit_Case(self, n):
        expr = self.visit(n.expr)
        self.__currentSwitchExprALL[-1].append(expr)
        ifcond = self.__currentSwitchVar[-1] + " == " + expr
        self.__caseCount[self.__currentSwitchCount] += 1
        caseNumber = self.__caseCount[self.__currentSwitchCount]
        s = 'if (%s)\n' % ifcond
        s += self._make_indent() + '{\n'
        self.indent_level += 1
        # Make a label for this case here
        if self.__caseCount[self.__currentSwitchCount] > 1:
            s += self._make_indent() + '__switch_%s_case_%s:;\n' % (
                self.__currentSwitchCount, caseNumber)
        hasBreak = False
        for i in range(0, len(n.stmts)):
            if type(n.stmts[i]) == c_ast.Break:
                hasBreak = True
                s += self.visit(n.stmts[i])
            else:
                s += self._generate_stmt(n.stmts[i], add_indent=False)
        if not hasBreak:
            s += self._make_indent(delta=0) + 'goto __switch_%s_case_%s;\n' % (
                self.__currentSwitchCount, caseNumber + 1)
        self.indent_level -= 1
        s += self._make_indent() + '}\n'
        return s

    def visit_Default(self, n):
        self.__caseCount[self.__currentSwitchCount] += 1
        caseNumber = self.__caseCount[self.__currentSwitchCount]
        cond = '!('
        for i, e in enumerate(self.__currentSwitchExprALL[-1]):
            if i != 0:
                cond += ' || '
            cond += self.__currentSwitchVar[-1] + ' == ' + e
        cond += ')'

        s = 'if (%s) \n' % cond
        s += self._make_indent() + '{\n'
        self.indent_level += 1
        s += self._make_indent() + '__switch_%s_case_%s:;\n' % (
            self.__currentSwitchCount, caseNumber)
        hasBreak = False
        for i in range(0, len(n.stmts)):
            if type(n.stmts[i]) == c_ast.Break:
                hasBreak = True
                s += self.visit(n.stmts[i])
            else:
                s += self._generate_stmt(n.stmts[i], add_indent=False)
        if not hasBreak:
            s += self._make_indent(delta=0) + 'goto __switch_%s_case_%s;\n' % (
                self.__currentSwitchCount, caseNumber + 1)
        self.indent_level -= 1
        s += self._make_indent() + '}\n'
        return s

    def visit_Break(self, n):
        innermostSwitch = -1
        # Find the innermost stmt that has this break stmt
        for i in reversed(range(0, len(self.__stack))):
            if self.__stack[i] == 'Case':
                innermostSwitch = 1
                break
            if self.__stack[i] == 'Default':
                innermostSwitch = 1
                break
            if self.__stack[i] == 'For':
                innermostSwitch = 0
                break
            if self.__stack[i] == 'While':
                innermostSwitch = 0
                break
            if self.__stack[i] == 'DoWhile':
                innermostSwitch = 0
                break

        if innermostSwitch == -1:
            raise ModuleError("break statement outside switch, for, while or do..while blocks.\n")

        if innermostSwitch == 1:
            return self._make_indent() + '<case-break-of-switch%s>\n' % self.__currentSwitchCount
        else:
            return 'break;'

    def visit_Label(self, n):
        if type(n.stmt) == c_ast.EmptyStatement:
            return n.name + ':;\n'
        else:
            return n.name + ':\n' + self._generate_stmt(n.stmt)

    def visit_EmptyStatement(self, n):
        return ''
