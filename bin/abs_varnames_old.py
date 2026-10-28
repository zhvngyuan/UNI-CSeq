# # # -*- coding: utf-8 -*-
# -----------------------------------------------------------------------------
# NAME = abs_varnames
# -----------------------------------------------------------------------------
# VERSION = 0.2
# -----------------------------------------------------------------------------
# Description:
#     Based on varnames.py from Lazy-cseq
#     Perform variable renaming to facilitate function inlining:
#     Criteria:
#       no two functions will share a variable identifier
#       handling function pointer
#       new variable name must be unique in its scope
#       mapping varible to preserving consistency
#
# TODO:
#       - variables in different block must be change the name
#           (to facilitate CONCURINTEPROC)
#       - removing duplicate declaration (external declaration)
#           int x;
#           int x = 0;
#           --->
#           int x = 0;
#
# Changelog:
#
# Yuan Zhang: When multiple loops in a function contain the same variable, a duplicate variable declaration error occurs.
# Add translation <-->
#               for(i=0; i<10; i++){...}
#               for(i=0; i<10; i++){...}
#            =>   
#            for(i_1=0; i_1<10; i_1++){...}
#            for(i_2=0; i_2<10; i_2++){...}
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

    newIDs = {}   # mapping of old variable names to new variable names

    __currentFunction = ''
    # add by zy 
    __visitingParam = 0    # depth of params in a function prototype
    __visitingDecl = 0
    __visitFuncDef = 0
    __visitStructUnionEnum = 0


    def visit(self, node):
        method = 'visit_' + node.__class__.__name__
        self.__stack.append(node.__class__.__name__)
        retval = getattr(self, method, self.generic_visit)(node)
        self.__stack.pop()
        return retval

    def visit_Decl(self, n, no_type=False):
        # no_type is used when a Decl is part of a DeclList, where the type is
        # explicitly only for the first delaration in a list.
        #
        self.__visitingDecl += 1

        # Safe since all decl's are separated
        if self.__debug:
            print "visiting Decl: [%s,%s]" % (self.__currentFunction, n.name)

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

    def visit_FuncDef(self, n):
        self.__currentFunction = n.decl.name
        s = super(ABS_Varnames, self).visit_FuncDef(n)
        self.__currentFunction = ''

        return s

    def visit_ParamList(self, n):
        out = ''
        for i, p in enumerate(n.params):
            spacer = '' if i == 0 else ', '
            self.__visitingParam += 1
            out += spacer + self.visit(p)
            self.__visitingParam -= 1
        return out

    def visit_StructRef(self, n):
        sref = self._parenthesize_unless_simple(n.name)
        oldvisitingStructRef = False
        self.__visitingStructRef = True
        if self.__debug:
            print "------- ------- ------- ------- VISITING STRUCT REF START (%s)" % sref
        retval = sref + n.type + self.visit(n.field)
        if self.__debug:
            print "------- ------- ------- ------- VIITING STRUCT REF END"
        self.__visitingStructRef = oldvisitingStructRef
        return retval

    def visit_ID(self, n):
        prefix = ''
        if n.name in self.Parser.varNames[self.__currentFunction]:
            if self.__debug:
                print "visiting ID: [%s,%s]" % (self.__currentFunction, n.name)

        if (n.name in self.Parser.varNames[self.__currentFunction] and
                self.__currentFunction != '' and
                not self.__visitingStructRef):
            if self.__debug:
                print "     local PARAMETER"
            if self.__debug:
                print "     stack: " + str(self.__stack) + '   prev:' + str(self.__stack[len(self.__stack) - 2])
            prefix = self.newIDs[self.__currentFunction, super(ABS_Varnames, self).visit_ID(n)]

        return prefix + super(ABS_Varnames, self).visit_ID(n)

    # Variable rename happen here
    def _generate_type(self, n, modifiers=[]):
        """ Recursive generation from a type node. n is the type node.
            modifiers collects the PtrDecl, ArrayDecl and FuncDecl modifiers
            encountered on the way down to a TypeDecl, to allow proper
            generation from it.
        """
        typ = type(n)

        if typ == c_ast.TypeDecl:
            s = ''
            if n.quals:
                s += ' '.join(n.quals) + ' '
            s += self.visit(n.type)

            # Local variables & parameter renaming.
            #
            # Variable name substitution only applies to local variables or
            #           parameters names within function prototypes
            # (thus, global variables and function names need to be excluded)
            #
            # case 1: level-0 function parameters (no remanimg for nested parameters)
            # case 2: local variable declaration (thus excluding functions, global vars,
            #                   struct-enum-union fields, nested parameters)
            #
            if self.__debug:
                print "Generating Decl: [%s,%s]" % (self.__currentFunction, n.declname)

            if self.__visitingParam == 1:                          # case 1
                if self.__debug:
                    print "SETTING NEWID for [%s,%s] (case I)" % (
                        self.__currentFunction, n.declname)

                self.newIDs[self.__currentFunction, n.declname] = self.prefix + self.__currentFunction + '_'
                n.declname = (self.prefix + self.__currentFunction + '_' + n.declname) if n.declname else ''

            elif (self.__visitingParam == 0 and                    # case 2
                  self.__visitFuncDef == 0 and
                  n.declname not in self.Parser.funcName and
                  # n.declname not in self.Parser.varNames[''] and
                  self.__currentFunction != '' and
                  self.__visitStructUnionEnum == 0):

                if self.__debug:
                    print "SETTING NEWID for [%s,%s] (case II)" % (self.__currentFunction, n.declname)

                self.newIDs[self.__currentFunction, n.declname] = self.prefix + self.__currentFunction + '_'
                n.declname = self.prefix + self.__currentFunction + '_' + n.declname if n.declname else ''

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


    def outputparam(self,id,description='',datatype=''):
            self.outputparamdefs.append(ModuleParam(id,description,datatype))