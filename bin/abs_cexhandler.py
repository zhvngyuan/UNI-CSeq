#------------------------------------------------------------------------------
# NAME = abs_cexhandler
#------------------------------------------------------------------------------
# VERSION = 0.001
#------------------------------------------------------------------------------
# Description:
#   Handling counter example generated from CPA checker
#   Typical form of counter example
#   File ErrorPath.0.core.txt
#       three types of line:
#
#           line 56:    N978 -{int w = 0;}-> N979
#           lines 216-225:  N183 -{__VERIFIER_nondet_bool()}-> N13
#           none:   N566 -{}-> N545
#
#   File ErrorPath.0.txt (use this from the beginning)
#       Types of line
#           none:   N502 -{INIT GLOBAL VARS}-> N523
#           /usr/lib/gcc/x86_64-linux-gnu/4.8/include/stddef.h, line 212:
#           N523 -{typedef unsigned long int size_t;}-> N524
#           line 2: N775 -{typedef int __cs_mutex_t;}-> N776
#                 __cs_simulate = 2;
#
# TODO:
#   Refectoring to make function name readable
#   Parsing counter example file to this data structure
#       {
#           type:
#                - compound statement
#                - singleline statement
#           line:
#               (line1, line2)
#           start node :
#               (N233)
#           end node :
#               (N222)
#           string:
#               inside -{ }->
#       }
#   Data type statement:
#       Assignment:
#       BinaryOp:
#       Text:
#
# Changelog:
#
#------------------------------------------------------------------------------

import os
import re
from pycparser import c_ast
from abs_smallparser import ABS_SmallParser
from abs_module import ModuleError

transformedFiles = ['___11_abs_sequentializer_toC.c',
                    '___10_abs_threadduplicator.c',
                    '___9_abs_unroller.c',
                    '___8_abs_inliner.c',
                    '___7_abs_varnames.c',
                    '___6_abs_extractor.c',
                    '___5_abs_atomicitizer.c',
                    '___4_abs_loopconversion.c',
                    '___3_abs_switchconversion.c',
                    '___2_abs_simplifier.c',
                    '___1_abs_preprocessor.c',
                    '___0_original.c'
                    ]


class ABS_Cexhandler():
    __cex_text = ''
    __seq2thr_log = ''

    # __seqf_text = ''

    Processor = ABS_SmallParser()

    __currlineno = 0

    def __init__(self):
        self.cex_data = []   # List to store counter example data
        self.seq2thr_data = {}  # List to store map line from abs_sequentializer_toC to abs_threadduplicator
        # self.seqf_data = []   # List to store lines of sequentialized file

    #----------------- READ COUNTER EXAMPLE -------------------------
    def openCEXFile(self, filename=''):
        if filename == '':
            filename = '../output/ErrorPath.0.txt'

        if not os.path.isfile(filename):
            raise ModuleError('Cannot open counter example file\n')
        else:
            myfile = open(filename)
            self.__cex_text = myfile.read()
            myfile.close()

    def readCEXFile(self, text=''):
        if text == '':
            text = self.__cex_text
        lines = text.splitlines(False)

        for l in lines:
            if l.startswith('none'):
                s = re.sub(r'(.*):(.*)-{(.*)}->(.*)', r'\1,\2,\3,\4', l)
                s = s.split(',')
                self._make_data(0, lines=None, data=s[2], sNode=s[1], dNode=s[3])
            elif l.startswith('lines'):
                s = re.sub(r'(.*):(.*)-{(.*)}->(.*)', r'\1,\2,\3,\4', l)
                s = s.split(',')
                self._make_data(2, lines=s[0], data=s[2], sNode=s[1], dNode=s[3])
            elif l.startswith('line'):
                s = re.sub(r'(.*):(.*)-{(.*)}->(.*)', r'\1,\2,\3,\4', l)
                s = s.split(',')
                self._make_data(1, lines=s[0], data=s[2], sNode=s[1], dNode=s[3])
            elif l.startswith('/'):
                pass
            elif l.find(':') == -1:
                self._make_data(3, lines=None, data=l.strip(), sNode=None, dNode=None)
            else:
                raise ModuleError('Unsupported type\n')

    def _make_data(self, type, lines=None, data=None, sNode=None, dNode=None):
        if type == 0:  # None type line
            n = {}
            n['type'] = 0
            n['line'] = None
            d = []
            d.append(data.strip())
            n['data'] = d
            # sNode = sNode.strip().replace('N', '')
            # n.append(sNode)
            # dNode = dNode.strip().replace('N', '')
            # n.append(dNode)
            self.cex_data.append(n)
        elif type == 1:  # single line node
            n = {}
            # process line
            n['type'] = 1
            lines = lines.strip().replace('line', '').strip()
            n['line'] = lines
            d = []
            d.append(data.strip())
            n['data'] = d
            # sNode = sNode.strip().replace('N', '')
            # n.append(sNode)
            # dNode = dNode.strip().replace('N', '')
            # n.append(dNode)
            self.cex_data.append(n)
        elif type == 2:  # multiple lines node
            n = {}
            n['type'] = 2
            lines = lines.strip().replace('lines', '').strip()
            lines = lines.split('-')
            n['lines'] = lines
            d = []
            d.append(data.strip())
            n['data'] = d
            # sNode = sNode.strip().replace('N', '')
            # n.append(sNode)
            # dNode = dNode.strip().replace('N', '')
            # n.append(dNode)
            self.cex_data.append(n)
        elif type == 3:  # Additional information node
            if len(self.cex_data) > 0:
                self.cex_data[-1]['data'].append(data.strip())
            else:
                raise ModuleError('Counter example file has some problems\n')
        else:  # Ignored type
            raise ModuleError('This type of data is not supported\n')

    def showCEXText(self):
        print self.__cex_text

    def showCEXData(self):
        print self.cex_data

    # -------------------- READ CBMC Counter example ----------------------
    def openCBMCCEXFile(self, filename=''):
        if filename == '':
            filename = '../___12_cex.log'

        if not os.path.isfile(filename):
            raise ModuleError('Cannot open counter example file\n')
        else:
            myfile = open(filename)
            self.__cex_text = myfile.read()
            myfile.close()

    def readCBMCCEXFile(self, text=''):
        if text == '':
            text = self.__cex_text
        lines = text.splitlines(False)
        hasErrorTrace = False
        for l in lines:
            if l.startswith('Counterexample:'):
                hasErrorTrace = True
            elif l.startswith('Violated'):
                hasErrorTrace = False
            elif hasErrorTrace:
                if l.startswith('State'):
                    self._make_CBMC_data(1, l)
                elif l.startswith('  '):
                    self._make_CBMC_data(2, l)

    def _make_CBMC_data(self, typ, string):
        if typ == 1:
            n = {}  # Node to be added to cex data
            n['type'] = typ
            tup = string.split()
            for i in range(0, len(tup)):
                if i % 2 == 0:
                    n[tup[i]] = tup[i+1]
            self.cex_data.append(n)
        else:
            string = string.strip().split()
            data = string[0]
            if len(self.cex_data) > 0:
                self.cex_data[-1]['data'] = data

    # ---------------- END OF READ CBMC Counter example -------------------

    # ----------------- READ SEQUENTIALIZED FILES -------------------------
    # def openSequentializedFile(self, inputfile):
    #     if inputfile == '':
    #         inputfile = '___11_abs_sequentializer_toC.c'

    #     if not os.path.isfile(inputfile):    #Test file exists
    #         raise ModuleError('Cannot open sequentialized file\n')
    #     else:
    #         myfile = open(inputfile)
    #         self.__seqf_text = myfile.read()
    #         myfile.close()

    # def readSequentializedFile(self, text=''):
    #     if text == '':
    #         text = self.__seqf_text
    #     self.seqf_data = text.splitlines(False)

    #----------------- PROCESS LOG FILES -------------------------
    def openMapLineFile(self, inputfile=''):
        if inputfile == '':
            inputfile = '../___11_10___.linemap'
        if not os.path.isfile(inputfile):    # Test file exists
            raise ModuleError('Cannot open mapline log file\n')
        else:
            myfile = open(inputfile)
            self.__seq2thr_log = myfile.read()
            myfile.close()

    def readMapLineFile(self, text=''):
        if text == '':
            text = self.__seq2thr_log
        lines = text.splitlines(False)
        for l in lines:
            s = l.split(':')
            self._make_mapline_data(s[0], s[1], s[2])

    def _make_mapline_data(self, source, dest, typestr):
        if source in self.seq2thr_data:
            self.seq2thr_data[source][1].append(typestr)
        else:
            n = []
            n.append(dest)
            n.append([])
            n[1].append(typestr)
            self.seq2thr_data[source] = tuple(n)

    #----------------- GENERATING COUNTER EXAMPLE -------------------------
    """
        Generating line number of execution from CEX file, Sequentialized file
        and the last Multithread transformation file
    """
    def fromCexToSeqThr(self):
        for i in range(0, len(self.cex_data)):
            # A cex node has 5 elements
            # type: single line, multiple line or none
            # line: followup type
            # data: data for that line to trace back
            # source node:
            # destination node:
            cexNode = self.cex_data[i]
            # Collect line from counter example data
            # Check if that line also appears in log file
            # Extract line from ___10_abs... file
            if cexNode['type'] == 1:    # Single line node from counter example
                line = cexNode['line']
                if line in self.seq2thr_data:  # this line is also in map line
                    mapNode = self.seq2thr_data[line]
                    print 'found line %s' % mapNode[0]


if __name__ == "__main__":
    handler = ABS_Cexhandler()
    # handler.openCEXFile()
    # handler.readCEXFile()
    handler.openCBMCCEXFile()
    handler.readCBMCCEXFile()

    handler.openMapLineFile()
    handler.readMapLineFile()

    # handler.showCEXData()
    handler.fromCexToSeqThr()