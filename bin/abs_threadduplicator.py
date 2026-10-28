# ------------------------------------------------------------------------------
# NAME = abs_threadduplicator
# ------------------------------------------------------------------------------
# VERSION = 0.2
# ------------------------------------------------------------------------------
# Description:
#   Based on duplicator.py of Lazy-cseq
#   Clones thread function so that all thread functions will have different names
#       and update pthread_create() calls to call such functions
#
#   Additional Feature:
#       Change thread ID so that from thread id we can track the actual thread
#       (remove all declaration of pthread_t and replace it with global variables
#       (in translation phase))
# TODO:
#    Change whole thread id array to decompose thread id
# Changelog:
#
# ------------------------------------------------------------------------------

from pycparser import c_ast
import common
import abs_common
from abs_module import ABS_Module, ModuleError
from collections import deque


class ABS_Threadduplicator(ABS_Module):
    __threadCallCnt = {}    # number of pthread_create()s on the same function generated so far
    __thread_id = 1         # Reserve threadid 0 for main thread
    __thread_dict = {}

    __lineno = 0            # Current line no of the generated file
    # coordMap = {}
    logoutput = ''

    def loadfromstring(self, string, env):
        super(ABS_Threadduplicator, self).loadfromstring(string, env)
        self._postprocess()
        # Log file
        # self.saveLogFile('___10_9___.linemap')

    # --------------- VISITING AST --------------------------------------
    def visit_FuncDef(self, n):
        ''' Each thread function is duplicated exactly the number of times
            that function is used to create a thread (as an argument to  pthread_call() )
        '''
        block = ''
        if n.decl.name == 'main':
            decl = self.visit(n.decl)
            body = self.visit(n.body)
            block = decl + '\n' + body + '\n'
        elif n.decl.name not in self.Parser.threadName:
            # Copy from parser, wont visit anything here
            block = self.Parser.funcBlock[n.decl.name]
        else:
            # Duplicate of thread happens here
            # TODO this needs proper implementation
            for i in range(0, self.Parser.threadCallCnt[n.decl.name]):
                # tmp = self.Parser.funcBlock[n.decl.name].replace(n.decl.name, n.decl.name+'_'+str(i), 1)
                tmp = self.visit(n.decl) + '\n' + self.visit(n.body) + '\n'
                tmp = tmp.replace(n.decl.name, n.decl.name + '_' + str(i), 1)
                block += tmp
        return block

    def visit_FuncCall(self, n):
        fref = self._parenthesize_unless_simple(n.name)
        args = self.visit(n.args)

        if (fref == common.changeID['pthread_create'] or
                fref == 'pthread_create'):
            # Find thread function name
            fName = self.visit(n.args.exprs[2])
            fName = fName[1:] if fName.startswith('&') else fName

            # thread ID to be
            threadName = args[:args.find(',')]
            threadName = threadName.replace('&', '')

            if threadName not in self.__thread_dict:
                self.__thread_dict[threadName] = deque([])
                self.__thread_dict[threadName].append(self.__thread_id)
            else:
                self.__thread_dict[threadName].append(self.__thread_id)

            # Count number of call thread
            if fName not in self.__threadCallCnt:
                self.__threadCallCnt[fName] = 0
            else:
                self.__threadCallCnt[fName] += 1
            args = args.replace(threadName, '%s' % abs_common.namespace['threadname'] + str(self.__thread_id), 1)
            args = args.replace(fName, fName + '_' + str(self.__threadCallCnt[fName]), 1)
            self.__thread_id += 1

        # Assume that pthread_join must be call after pthread_create
        # which is naturally true
        if (fref == common.changeID['pthread_join'] or fref == 'pthread_join'):
            threadName = args[:args.find(',')]
            if threadName not in self.__thread_dict:
                raise ModuleError('This thread name %s does not exist\n' % threadName)
            else:
                thread_id = self.__thread_dict[threadName][0]
            self.__thread_dict[threadName].popleft()
            args = args.replace(threadName, '%s' % abs_common.namespace['threadname'] + str(thread_id), 1)

        return fref + '(' + args + ')'

    # -------------------- REMOVING EMPTY STATEMENT ----------------------

    def visit_Label(self, n):
        return n.name + ':;\n' + self._generate_stmt(n.stmt)

    def visit_EmptyStatement(self, n):
        return ''

    # -------------------- REMOVING EMPTY STATEMENT ----------------------

    def _postprocess(self):
        # The thread functions prototypes of duplicated threads
        # need to be duplicated too.
        for f in self.Parser.threadName:
            if f in self.Parser.funcDecl:
                oldPrototype = self.Parser.funcDecl[f] + ';'
                newPrototype = ''
                for i in range(0, self.Parser.threadCallCnt[f]):
                    newPrototype += oldPrototype.replace(f + '(', f + '_' + str(i) + '(', 1)
                self.output = self.output.replace(oldPrototype, newPrototype)

    # --------------------------  LOG FILE FOR COUNTER EXAMPLE  --------------------------
    def saveLogFile(self, filename):
        outfile = open(filename, "w")
        outfile.write(self.logoutput)
        outfile.close()

    def logMapLine(self, oldline, currline, node, typ=''):
        pass
