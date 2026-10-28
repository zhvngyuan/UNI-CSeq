# -----------------------------------------------------------------------------
# NAME = abs_module
# -----------------------------------------------------------------------------
# VERSION = 0.2
# -----------------------------------------------------------------------------
# Description:
#   Base on module.py of Lazy-cseq
#   Custom base module for all abs module
#   Use different annotation from Lazy-cseq
# TODO:
#   Removing redundant code to improve performance
#
# Changelog:
#
# -----------------------------------------------------------------------------

from pycparser import c_generator, c_ast
from abs_annotator import ABS_Annotator
import utils


class ModuleError(Exception):

    def __init__(self, value):
        self.value = value

    def __str__(self):
        return repr(self.value)


class ABS_Module(c_generator.CGenerator):
    # Statements start with indentation of self.indent_level spaces,
    # using the _make_indent method
    #
    indent_level = 0        # to keep track of the depth of the block {}
    INDENT_SPACING = '  '   # ....

    Parser = ABS_Annotator()  # Parser for preprocess the file

    output = ''

    # Handling line number
    __lineno = 0            # Current line number of generated file
    lastCoords = ''         # coords of the last fragment of code parsed
    coordMap = {}
    lines = []

    # ------------ Line changing function ------------------------------
    def visit_FuncDef(self, n):
        decl = self.visit(n.decl)
        self.indent_level = 0
        body = self.visit(n.body)
        if n.param_decls:
            knrdecls = ';\n'.join(self.visit(p) for p in n.param_decls)
            return decl + '\n' + knrdecls + ';\n' + body + '\n'
        else:
            return decl + '\n' + body + '\n'

    def visit_FileAST(self, n):
        s = ''
        for ext in n.ext:
            if isinstance(ext, c_ast.FuncDef):
                s += self.visit(ext)
            else:
                s += self.visit(ext) + ';\n'
                # Each ext calculates its own line already
                self.__lineno += 1
        return s

    def visit_Compound(self, n):
        s = self._make_indent() + '{\n'
        self.__lineno += 1
        self.indent_level += 2
        if n.block_items:
            # Eech statement calculate its own line
            s += ''.join(self._generate_stmt(stmt) for stmt in n.block_items)
        self.indent_level -= 2
        s += self._make_indent() + '}\n'
        self.__lineno += 1
        return s

    def visit_If(self, n):
        s = 'if ('
        if n.cond:
            s += self.visit(n.cond)
        s += ')\n'
        self.__lineno += 1
        s += self._generate_stmt(n.iftrue, add_indent=True)
        if n.iffalse:
            s += self._make_indent() + 'else\n'
            self.__lineno += 1
            s += self._generate_stmt(n.iffalse, add_indent=True)
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
        self.__lineno += 1
        s += self._generate_stmt(n.stmt, add_indent=True)
        return s

    def visit_While(self, n):
        s = 'while ('
        if n.cond:
            s += self.visit(n.cond)
        s += ')\n'
        self.__lineno += 1
        s += self._generate_stmt(n.stmt, add_indent=True)
        return s

    def visit_DoWhile(self, n):
        s = 'do\n'
        self.__lineno += 1
        s += self._generate_stmt(n.stmt, add_indent=True)
        s += self._make_indent() + 'while ('
        if n.cond:
            s += self.visit(n.cond)
        s += ');'
        return s

    def visit_Switch(self, n):
        s = 'switch (' + self.visit(n.cond) + ')\n'
        self.__lineno += 1
        s += self._generate_stmt(n.stmt, add_indent=True)
        return s

    def visit_Case(self, n):
        s = 'case ' + self.visit(n.expr) + ':\n'
        self.__lineno += 1
        for stmt in n.stmts:
            s += self._generate_stmt(stmt, add_indent=True)
        return s

    def visit_Default(self, n):
        s = 'default:\n'
        self.__lineno += 1
        for stmt in n.stmts:
            s += self._generate_stmt(stmt, add_indent=True)
        return s

    def visit_Label(self, n):
        s = n.name + ':\n'
        self.__lineno += 1
        s += self._generate_stmt(n.stmt)
        return s

    def _generate_struct_union(self, n, name):
        """ Generates code for structs and unions. name should be either
            'struct' or union.
        """
        s = name + ' ' + (n.name or '')
        if n.decls:
            s += '\n'
            self.__lineno += 1
            s += self._make_indent()
            self.indent_level += 2
            s += '{\n'
            self.__lineno += 1
            for decl in n.decls:
                s += self._generate_stmt(decl)
            self.indent_level -= 2
            s += self._make_indent() + '}'
        return s

    def _generate_stmt(self, n, add_indent=False):
        """ Generation from a statement node. This method exists as a wrapper
            for individual visit_* methods to handle different treatment of
            some statements in this context.
        """
        typ = type(n)
        if add_indent:
            self.indent_level += 2
        indent = self._make_indent()
        if add_indent:
            self.indent_level -= 2

        if typ in (
                c_ast.Decl, c_ast.Assignment, c_ast.Cast, c_ast.UnaryOp,
                c_ast.BinaryOp, c_ast.TernaryOp, c_ast.FuncCall, c_ast.ArrayRef,
                c_ast.StructRef, c_ast.Constant, c_ast.ID, c_ast.Typedef,
                c_ast.ExprList):
            # These can also appear in an expression context so no semicolon
            # is added to them automatically
            #
            return indent + self.visit(n) + ';\n'
            self.__lineno += 1
        elif typ in (c_ast.Compound,):
            # No extra indentation required before the opening brace of a
            # compound - because it consists of multiple lines it has to
            # compute its own indentation.
            #
            return self.visit(n)
        else:
            return indent + self.visit(n) + '\n'
            self.__lineno += 1
    # ------------ Line changing function ------------------------------

    # ------------ IO function ------------------------------------
    def loadfromstring(self, string, env):
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
    # ------------ END IO function ------------------------------------

    # ------------ VISITING generic functions ------------------------------------
    def visit(self, node):
        method = 'visit_' + node.__class__.__name__
        lineCoords = ''
        # Extracts node coords where possible.
        if hasattr(node, 'coord'):
            # print "visiting coords of node %s: %s" % (node.__class__.__name__, node.coord)
            if node.coord:
                self.lastCoords = str(node.coord)
                # print "visiting coords: %s" % (self.lastCoords)

                # line number handling borrowed from CSeq-0.5
                linenumber = str(node.coord)
                linenumber = linenumber[linenumber.rfind(':') + 1:]
                self.currentInputLineNumber = int(linenumber)

                # Each line of the output is annotated when
                # either it is coming from a new input line number
                # or the input line has generated many output lines,
                # in which case the annotation needs to be repeated at each line..
                #
                if linenumber not in self.lines and linenumber != '0':
                    # print "      adding line number %s" % linenumber
                    self.lines.append(linenumber)
                    lineCoords = self._getCurrentCoords(node)
        # print '# %s' % lineCoords
        tmp = ''
        return tmp + super(ABS_Module, self).visit(node)

    # ------------ GENERAL VISITING generic functions ------------------------------------

    # Extract the coords from an error condition
    #
    def parseErrorCoords(self, error):
        errorstring = str(error)
        k = utils.findNth(errorstring, ':', 2)
        if k != -1:
            errorcoords = errorstring[:utils.findNth(errorstring, ':', 2)]
        else:
            errorcoords = ':-1:-1'

        return errorcoords

    def getLineNumber(self, error):
        return int(self.parseErrorCoords(error).split(':')[1])

    def getColumnNumber(self, error):
        return int(self.parseErrorCoords(error).split(':')[2])

    def _getCurrentCoords(self, item):
        # return '/*cseq:coords '+ str(item.coord) +' */\n'
        return str(item.coord)

    def _make_indent(self, delta=0):
        return (self.indent_level + delta) * self.INDENT_SPACING
