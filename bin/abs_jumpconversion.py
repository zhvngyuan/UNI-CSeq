# ------------------------------------------------------------------------------
# NAME = abs_jumpconversion
# ------------------------------------------------------------------------------
# VERSION = 0.1
# -----------------------------------------------------------------------------
# Description:
#     Transform any break and continue statement inside loop to goto
# Prerequisites:
#     There should be only while loop at this stage
# Limitations:
#
# TODO:
#     - Consider loop inside atomic function
# Changelog:
#   2016.05.06   Intial version
# -----------------------------------------------------------------------------

# from pycparser import c_ast
from abs_module import ABS_Module, ModuleError


class ABS_Jumpconversion(ABS_Module):
    INDENT_SPACING = ' '

    __debug = False

    __currentFunct = ''
    __current_loop_id = -1
    __loop_stack = []        # store the label of loop

    def visit_FuncDef(self, n):
        self.__currentFunct = n.decl.name
        self.__current_loop_id = -1           # reset for each function
        decl = self.visit(n.decl)
        self.indent_level = 0
        body = self.visit(n.body)

        if n.param_decls:
            knrdecls = ';\n'.join(self.visit(p) for p in n.param_decls)
            self.__currentFunct = ''
            return decl + '\n' + knrdecls + ';\n' + body + '\n'
        else:
            self.__currentFunct = ''
            return decl + '\n' + body + '\n'

    def visit_While(self, n):
        self.__current_loop_id += 1
        newlabel = self.__currentFunct + '_loop_%s' % (self.__current_loop_id)
        self.__loop_stack.append(newlabel)
        s = '%s:; while (' % ('__begin_' + newlabel)
        if n.cond:
            s += self.visit(n.cond)
        s += ')\n'
        s += self._generate_stmt(n.stmt, add_indent=True)
        s += '%s:;' % ('__end_' + newlabel)
        self.__loop_stack.pop()
        return s

    def visit_Label(self, n):
        # Separate label from its statement
        return n.name + ':;\n' + self._generate_stmt(n.stmt)

    def visit_Break(self, n):
        if len(self.__loop_stack) == 0:
            raise ModuleError("break statement not inside a while loop")
        label = self.__loop_stack[-1]
        return 'goto __end_%s;' % (label)

    def visit_Continue(self, n):
        if len(self.__loop_stack) == 0:
            raise ModuleError("continue statement not inside a while loop")
        label = self.__loop_stack[-1]
        return 'goto __begin_%s;' % (label)
