# # # -*- coding: utf-8 -*-
# -----------------------------------------------------------------------------
# NAME = abs_varnames
# -----------------------------------------------------------------------------
# VERSION = 0.3
# -----------------------------------------------------------------------------
# Description:
#     Based on varnames.py from Lazy-cseq
#     Perform variable renaming to facilitate function inlining:
#     Criteria:
#       no two functions will share a variable identifier
#       handling function pointer
#       new variable name must be unique in its scope (block-level)
#       mapping variable to preserving consistency, including for multiple loops
#
# Changelog:
#   2024-06-11  Block-level renaming support, avoid multiple i in loops conflicting
# -----------------------------------------------------------------------------

from pycparser import c_ast
from abs_module import ABS_Module
import abs_common

class ABS_Varnames(ABS_Module):
    # INDENT_SPACING = ' '
    __stack = []
    __debug = False
    __visitingStructRef = False   # to avoid considering struct fields as local variables

    prefix = abs_common.namespace['prefix']

    def __init__(self, *args, **kwargs):
        super(ABS_Varnames, self).__init__(*args, **kwargs)
        self.newIDs = {}   # {(func, oldname, idx): newname}
        self.__currentFunction = ''
        self.__visitingParam = 0
        self.__visitingDecl = 0
        self.__visitFuncDef = 0
        self.__visitStructUnionEnum = 0
        # Block-level变量作用域栈，每层为{varname: idx}
        self.__block_stack = []
        # 当前函数中每个变量名出现的计数器
        self.__varname_counter = {}

    def visit(self, node):
        method = 'visit_' + node.__class__.__name__
        self.__stack.append(node.__class__.__name__)
        retval = getattr(self, method, self.generic_visit)(node)
        self.__stack.pop()
        return retval

    def visit_FuncDef(self, n):
        self.__currentFunction = n.decl.name
        self.__varname_counter = {}
        self.__block_stack = [{}]  # 根block
        s = super(ABS_Varnames, self).visit_FuncDef(n)
        self.__currentFunction = ''
        return s

    def visit_Compound(self, n):
        self.__block_stack.append({})
        s = super(ABS_Varnames, self).visit_Compound(n)
        self.__block_stack.pop()
        return s

    def visit_ParamList(self, n):
        out = ''
        for i, p in enumerate(n.params):
            spacer = '' if i == 0 else ', '
            self.__visitingParam += 1
            param_out = self.visit(p)
            self.__visitingParam -= 1
            
            # 将参数添加到当前块的作用域中（索引为0表示是参数）
            if p.name and self.__currentFunction:
                if self.__block_stack:
                    self.__block_stack[0][p.name] = 0
            
            out += spacer + param_out
        return out

    def visit_StructRef(self, n):
        sref = self._parenthesize_unless_simple(n.name)
        oldvisitingStructRef = self.__visitingStructRef
        self.__visitingStructRef = True
        retval = sref + n.type + self.visit(n.field)
        self.__visitingStructRef = oldvisitingStructRef
        return retval

    def visit_Decl(self, n, no_type=False):
        self.__visitingDecl += 1

        is_local_var = (
            n.name and
            self.__currentFunction and
            self.__visitingParam == 0 and
            self.__visitStructUnionEnum == 0 and
            n.name not in self.Parser.funcName
        )

        if is_local_var:
            idx = self.__varname_counter.get(n.name, 0) + 1
            self.__varname_counter[n.name] = idx

            # Python 2.7字符串拼接
            newname = "%s%s_%s_%d" % (self.prefix, self.__currentFunction, n.name, idx)
            self.newIDs[(self.__currentFunction, n.name, idx)] = newname
            self.__block_stack[-1][n.name] = idx

            # 保存原始名称，用于生成声明时替换
            old_name = n.name
            n.name = newname

            # 替换AST实际声明名
            if hasattr(n.type, 'declname'):
                n.type.declname = newname

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

        self.__visitingDecl -= 1

        return s

    def visit_ID(self, n):
        if (self.__currentFunction and not self.__visitingStructRef and 
            n.name not in self.Parser.funcName):
            # 首先检查是否是函数参数
            param_key = (self.__currentFunction, n.name, 0)
            if param_key in self.newIDs:
                return self.newIDs[param_key]
            
            # 然后检查是否是局部变量
            for block in reversed(self.__block_stack):
                if n.name in block:
                    idx = block[n.name]
                    key = (self.__currentFunction, n.name, idx)
                    newname = self.newIDs.get(key, None)
                    if newname:
                        return newname
                    break
        return super(ABS_Varnames, self).visit_ID(n)

    def _generate_type(self, n, modifiers=[]):
        typ = type(n)

        if typ == c_ast.TypeDecl:
            s = ''
            if n.quals:
                s += ' '.join(n.quals) + ' '
            s += self.visit(n.type)

            if self.__visitingParam == 1:
                newname = "%s%s_%s" % (self.prefix, self.__currentFunction, n.declname)
                self.newIDs[(self.__currentFunction, n.declname, 0)] = newname
                n.declname = newname if n.declname else ''
            elif (self.__visitingParam == 0 and
                  self.__visitFuncDef == 0 and
                  n.declname and
                  n.declname not in self.Parser.funcName and
                  self.__currentFunction != '' and
                  self.__visitStructUnionEnum == 0):
                # 对于局部变量，使用已经在visit_Decl中设置的新名称
                # 查找该变量的索引
                for block in reversed(self.__block_stack):
                    if n.declname in self.newIDs.values():
                        # 已经被重命名，保持不变
                        break
                    elif n.declname in block:
                        idx = block[n.declname]
                        key = (self.__currentFunction, n.declname, idx)
                        newname = self.newIDs.get(key, None)
                        if newname:
                            n.declname = newname
                        break

            nstr = n.declname if n.declname else ''

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
            return s
        elif typ == c_ast.Decl:
            return self._generate_decl(n.type)
        elif typ == c_ast.Typename:
            return self._generate_type(n.type)
        elif typ == c_ast.IdentifierType:
            return ' '.join(n.names) + ' '
        elif typ in (c_ast.ArrayDecl, c_ast.PtrDecl, c_ast.FuncDecl):
            return self._generate_type(n.type, modifiers + [n])
        else:
            return self.visit(n)

    def visit_Struct(self, n):
        self.__visitStructUnionEnum += 1
        s = super(ABS_Varnames, self).visit_Struct(n)
        self.__visitStructUnionEnum -= 1
        return s

    def visit_Union(self, n):
        self.__visitStructUnionEnum += 1
        s = super(ABS_Varnames, self).visit_Union(n)
        self.__visitStructUnionEnum -= 1
        return s

    def visit_Enum(self, n):
        self.__visitStructUnionEnum += 1
        s = super(ABS_Varnames, self).visit_Enum(n)
        self.__visitStructUnionEnum -= 1
        return s

    def visit_Typedef(self, n):
        self.__visitStructUnionEnum += 1
        s = super(ABS_Varnames, self).visit_Typedef(n)
        self.__visitStructUnionEnum -= 1
        return s