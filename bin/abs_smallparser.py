#------------------------------------------------------------------------------
# NAME = abs_smallparser
#------------------------------------------------------------------------------
# VERSION = 0.001
#------------------------------------------------------------------------------
# Description:
#   Small parser for dealing with collected data from Counter example file
#
# TODO:
#
# Changelog:
#
#------------------------------------------------------------------------------

import re

from pycparser import c_generator, c_ast, c_parser
from abs_module import ModuleError


class ABS_SmallParser(c_generator.CGenerator):
    Parser = c_parser.CParser()

    # Return data type and node (in C style)
    def parseData(self, data=''):
        if data.startswith('INIT GLOBAL'):
            return ('STR', data)
        elif data.startswith('Function start dummy'):
            return ('STR', data)
        elif data.startswith('Return edge from'):
            s = re.sub(r'Return edge from (.*) to (.*)', r'\1,\2', data)
            s = s.split(',')
            return ('RET', tuple(s))
        else:     # Any other case
            if data.startswith('[') and data.endswith(']'):    # A conditional node
                # Wrap data in a function and collecting it
                data = data.lstrip('[').rstrip(']') + ';'
            if not data.endswith(';'):
                data = data + ';'
            block = 'int foo(){' + data + '}'
            node = self.Parser.parse(block)
            node = self._extractNode(node)
            return (node.__class__.__name__, node)

    def _extractNode(self, n):
        if type(n) == c_ast.FileAST:
            if (isinstance(n.ext[0], c_ast.FuncDef) and
                    isinstance(n.ext[0].body, c_ast.Compound) and
                    n.ext[0].body.block_items):
                # print self.visit(n.ext[0].body.block_items[0])
                return n.ext[0].body.block_items[0]
            else:
                raise ModuleError('Counter example data is wrong\n')
        else:
            raise ModuleError('Counter example data is wrong\n')

        return n


# For testing
if __name__ == "__main__":
    parser = ABS_SmallParser()
    parser.parseData(data='[__cs_simulate == 1]')
