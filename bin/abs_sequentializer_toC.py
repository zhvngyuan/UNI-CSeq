# # -*- coding: utf-8 -*-
# ------------------------------------------------------------------------------
# NAME = abs_sequentializer_toC
# ------------------------------------------------------------------------------
# VERSION = 0.2a   (new schema)
# ----------------------------------------------------------------------------
# Description:
#   This module sequentializes a concurrent C programs to a sequential C program
#
#   Limitations:
#       - Does not support goto and label inside atomic region (which is logical)
#       - Does not support weirdo things in __VERIFIER_atomic function (or atomic region)
#          pthread_call
#
# TODO:
#
# Changelog:
#   2016.05.11 - add backends (alot)
#   2014.10.28 - Change turn atomic function (__VERIFIER_atomic_cseq_ prefix) to
#               their original
# ----------------------------------------------------------------------------

import json
import os
import sys
import re
from pycparser import c_ast
from abs_module import ABS_Module, ModuleError

import abs_common
import utils


class ABS_Sequentializer_toC(ABS_Module):
    custom_indent = 0
    debug = False
    debug_log = ''
    output = ''
    __pc_stack = []                            # Associated compound node to its start pc
    __currentGenerateFunct = ''
    # Simulation stuff
    __svar = '__cs_simulate'
    __error_var = '__cs_ERROR'

    # Counter example stuff
    __lineno = 0
    # coordMap = {}
    logoutput = ''

    __backend = 'cpachecker'        # Default backend

    __round = 0

    __threadIsVoid = {}

    __threadNameByID = {}

    __threadDic = {} # add by zy 存储中断函数名和对应的优先级（包括主任务）

    __currentFun = None # add by zy 初始化表示当前函数的变量

    __RespCount = 1

    __thread_index = {}

    __use_switch_goto = False  # Use switch+goto optimization instead of Res/Exe/Sus mode

     

    def loadfromstring(self, string, env):
        self.debug = env.debug
        self.__backend = env.backend
        self.__round = env.round
        self.__RespCount = env.RespCount
        self.__use_switch_goto = getattr(env, 'switch_goto', False)
        self.__ignore_masking = getattr(env, 'ignore_masking', False)
        self.Parser.reset()  # resets all the parser datastructs
        self.Parser.loadfromstring(string)
        self.ast = self.Parser.ast
        self.__thread_index = self.Parser.get_thread_index()

        # self.output = self.visit(self.ast)
        self.output = self.sequentialize(env)

        if self.debug:
            f = open("debug.log", "w")
            f.write(self.debug_log)
            f.close()

        # Log file
        # if self.debug:
        #     self.saveLogFile('___11_10___.linemap')

    def string(self):
        return self.output

    def save(self, filename):
        outfile = open(filename, "w")
        outfile.write(self.output)
        outfile.close()

    def show(self):
        print(self.output)

    def getInputList(self):  # add by zy generate priority conditions

        current_dir = os.path.dirname(os.path.abspath(__file__))
        json_file_path = os.path.join(current_dir, 'data.json')

        # 读取 data.json 文件并更新 self.__threadDic
        with open(json_file_path, 'r') as file:
            data = json.load(file)

        self.__threadDic.update(data)

        threadName = list(self.__threadDic.keys())
        HighestPrio = max(self.__threadDic.values())

        # 获取所有优先级小于最高优先级的线程名称
        higherPriorityList = [key for key, value in self.__threadDic.items() if value < HighestPrio]

        inputList = {}

        # 遍历每个线程（函数名）并生成对应的键值
        for t in threadName:
            inputList[t] = ''
            if self.__threadDic[t] == HighestPrio:
                continue
            if t == 'main_task':
                for j in higherPriorityList:
                        if j != t:
                            inputList[t] += '(__cs_pc_%s == 0 || __cs_pc_%s == %s)&&' % (
                                self.__thread_index[j],
                                self.__thread_index[j],
                                self.Parser.abs_functionMaxPC[j]
                            )
            
            else:
                for j in higherPriorityList:
                    # 仅选择优先级高于或等于当前线程的键（排除j本身）
                    if self.__threadDic[j] >= self.__threadDic[t]:
                        if t != j:
                            inputList[t] += '(__cs_pc_%s == 0 || __cs_pc_%s == %s)&&' % (
                                self.__thread_index[j],
                                self.__thread_index[j],
                                self.Parser.abs_functionMaxPC[j]
                            )

        return inputList  
        

    # -------------------------------------------------------------------
    #   Sequentialization into C program
    # -------------------------------------------------------------------
    def sequentialize(self, env):
        output = ''
        # #include <stdlib.h>
        # if ('realloc' not in self.Parser.abs_symbols and
        #         '__fsid_t' not in self.Parser.abs_symbols):
        #     if env.backend != 'seahorn':
        #         output += abs_common.namespace['stdlib']
        #         self.__lineno += 1
        

        for threadname in self.Parser.funcBlockOut:
            if self.Parser.funcBlockOut[threadname] != 'void':
                self.__threadIsVoid[threadname] = ' ;'
            else:
                self.__threadIsVoid[threadname] = ' 0;'

        for fref in self.__thread_index:
            tid = self.__thread_index[fref]
            self.__threadNameByID[str(tid)] = fref

        # TODO: this need proper implementation
        # if ('_IO_vfprintf' not in self.Parser.abs_symbols and
        #     '__fsid_t' not in self.Parser.abs_symbols):
        #     output += abs_common.namespace['stdio']

        ''' abs_common.namespace['include']
            typedef int __cs_mutex_t;
            #define pthread_mutex_t __cs_mutex_t
            typedef int __cs_cond_t;
            #define pthread_cond_t __cs_cond_t
            typedef int __cs_t;
            #define pthread_t __cs_t
        '''

        # output += abs_common.namespace['include']
        # self.__lineno += utils.countline(abs_common.namespace['include'])

        # output += '/* Translation information */\n'
        # self.__lineno += 1

        # For main thread
        # output += '// Main thread\n'
        # self.__lineno += 1
        # add by zy for main task
        output += '// Main task\n'
        self.__lineno += 1

        current_dir = os.path.dirname(os.path.abspath(__file__))
        json_file_path = os.path.join(current_dir, 'data.json')

        with open(json_file_path, 'r') as file:
            data = json.load(file)
        
        # 统计键的数量
        keyNum = len(data.keys())

        if 'main' not in self.__thread_index:
            raise ModuleError('There is a problem with source file (no main function)\n')
        else:
            if self.__backend in ('cbmc', '2ls'):
                import math
                k = int(math.floor(math.log(self.Parser.abs_functionMaxPC['main'], 2))) + 1   # number of bit required
                output += 'unsigned __CPROVER_bitvector[%s] %s%s;\n' % (k, abs_common.namespace['threadpc'], self.__thread_index['main'])
            else:
                output += 'unsigned int %s%s;\n' % (abs_common.namespace['threadpc'],
                                                    self.__thread_index['main'])
            self.__lineno += 1

        ''' Simulation variable declaration
        '''
        # for i in range(0, len(self.Parser.abs_threadID_stack)):
        #     threadname = self.Parser.abs_threadID_stack[i]
        #     maxPC = self.Parser.abs_functionMaxPC[threadname]
        #     output += '// %s\n' % threadname
        #     self.__lineno += 1
        #     if self.__backend in ('cbmc', '2ls'):
        #         # thread pc
        #         import math
        #         k = int(math.floor(math.log(maxPC, 2))) + 1   # number of bit required
        #         output += 'unsigned __CPROVER_bitvector[%s] %s%s;\n' % (k, abs_common.namespace['threadpc'], self.__thread_index[threadname])
        #     else:
        #         output += 'unsigned int %s%s;\n' % (abs_common.namespace['threadpc'],
        #                                             self.__thread_index[threadname])

        # 统一按照编号排序输出
        for threadname, idx in sorted(self.__thread_index.items(), key=lambda x: x[1]):
            if threadname == 'main':
                continue  # main 已在前面单独声明
            maxPC = self.Parser.abs_functionMaxPC[threadname]
            output += '// %s\n' % threadname
            self.__lineno += 1
            if self.__backend in ('cbmc', '2ls'):
                import math
                k = int(math.floor(math.log(maxPC, 2))) + 1
                output += 'unsigned __CPROVER_bitvector[%s] %s%s;\n' % (k, abs_common.namespace['threadpc'], idx)
            else:
                output += 'unsigned int %s%s;\n' % (abs_common.namespace['threadpc'], idx)


        # simulation variable
        if self.__backend in ('cbmc', '2ls'):
            output += 'unsigned __CPROVER_bitvector[2] %s;\n' % self.__svar
        else:
            output += 'int %s;\n' % self.__svar
        self.__lineno += 1
        # Error variable
        # output += '_Bool %s;\n' % self.__error_var
        # self.__lineno += 1
        # If there exists thread local variables
        # if self.Parser.abs_hasThreadLocal:
        #     output += '/* Thread information */\n'
        #     self.__lineno += 1
        #     output += '#define THREADS %s\n' % (len(self.Parser.abs_threadID_stack) + 1)
        #     self.__lineno += 1
        #     for f in self.Parser.abs_threadID:
        #         output += '#define THREAD_%s_INDEX %s\n' % (f, self.Parser.abs_threadID[f] - 1)
        #         self.__lineno += 1

        # declare some predefined function
        output += '/* Predefined functions type 1 */\n'
        self.__lineno += 1

        # ERROR function
        if env.backend == 'cpachecker':
        # if env.backend in ('cpachecker', 'cbmc'):
            output += '%s' % abs_common.namespace['error1']
            self.__lineno += utils.countline(abs_common.namespace['error1'])
        elif env.backend in ('cbmc', 'uautomizer'):
        # elif env.backend in ('cbmc'):
            pass  
        elif env.backend in ('esbmc', 'llbmc', '2ls'):
            output += '%s' % abs_common.namespace['error2']
        # # ERROR function
        # if env.backend in ('cbmc', 'esbmc', 'llbmc', '2ls'):
        #     output += '%s' % abs_common.namespace['error2']
        #     self.__lineno += utils.countline(abs_common.namespace['error2'])
        # elif env.backend in ('uautomizer', 'ukojak'):
        #     output += '%s' % abs_common.namespace['error3']
        elif env.backend in ('ukojak'):
            output += '%s' % abs_common.namespace['error3']
            self.__lineno += utils.countline(abs_common.namespace['error3'])
        elif env.backend in ('seahorn',):
            output += '%s' % abs_common.namespace['error4']
            self.__lineno += utils.countline(abs_common.namespace['error3'])
        elif env.backend in ('vvt',):
            output += '%s' % abs_common.namespace['error4']
            self.__lineno += utils.countline(abs_common.namespace['error3'])
        else:
            output += '%s' % abs_common.namespace['error1']
            self.__lineno += utils.countline(abs_common.namespace['error1'])

        # ASSUME function
        if env.backend == 'cbmc' or env.backend == '2ls':
            output += '#define __VERIFIER_assume(X) __CPROVER_assume(X)\n'
            output += '#define assume(X) __CPROVER_assume(X)\n'
            self.__lineno += 2
        elif env.backend == 'esbmc':
            output += '#define assume(X) __VERIFIER_assume(X)\n'
            self.__lineno += 1
        elif env.backend == 'llbmc':
            output += abs_common.namespace['llbmc_macro']
            self.__lineno += utils.countline(
                abs_common.namespace['llbmc_macro'])
        elif env.backend == 'cpachecker':
            output += '%s' % abs_common.namespace['assume']
            output += '#define __CPROVER_assume(X) __VERIFIER_assume(X)\n'
            self.__lineno += utils.countline(abs_common.namespace['assume'])
        elif env.backend in ('uautomizer', 'ukojak'):
            output += '#define assume(X) __VERIFIER_assume(X)\n'
            self.__lineno += 1
        elif env.backend in ('seahorn',):
            output += 'extern void __VERIFIER_assume(int e);\n'
            output += '#define assume(X) __VERIFIER_assume(X)\n'
            self.__lineno += 2
        elif env.backend in ('vvt', ):
            output += 'extern void __VERIFIER_assume(int e);\n'
            output += '#define assume(X) __VERIFIER_assume(X)\n'
            self.__lineno += 2
        else:
            output += '%s' % abs_common.namespace['assume']
            self.__lineno += utils.countline(abs_common.namespace['assume'])

        # NONDET
        if env.backend == 'cpachecker':
            output += '%s' % abs_common.namespace['nondet_type1']
            self.__lineno += utils.countline(abs_common.namespace['nondet_type1'])
        elif env.backend in ('uautomizer', 'ukojak'):
            output += '//Already defined\n'
            self.__lineno += 1
        elif env.backend in ('seahorn', ):
            output += '%s' % abs_common.namespace['nondet_type3']
            self.__lineno += utils.countline(abs_common.namespace['nondet_type3'])
        elif env.backend in ('vvt', ):
            output += '%s' % abs_common.namespace['nondet_type3']
            self.__lineno += utils.countline(abs_common.namespace['nondet_type3'])
        else:
            output += '%s' % abs_common.namespace['nondet_type2']
            self.__lineno += utils.countline(abs_common.namespace['nondet_type2'])

        # declare some predefined function
        output += '/* Predefined functions type 2 */\n'
        self.__lineno += 1
        output += '%s' % abs_common.namespace['functions2']
        self.__lineno += utils.countline(abs_common.namespace['functions2'])

        # add by zy
        # Generating ISR Masking variables
        output += '/* ISR Masking variables */\n'
        self.__lineno += 1

        # 生成输出语句
        # output += "int __cs_disable_isr[%s];\n" % keyNum  
        # 替换声明数组为声明变量（为了更好的使用其他验证工具，如CPAChecker）
        for i in range(keyNum):
            output += "int __cs_disable_isr_%d;\n" % i
            self.__lineno += 1

        # Generating global information of the file
        output += '/* Global variables */\n'
        self.__lineno += 1


        for i in range(0, len(self.Parser.abs_globalScope)):
            typename = self.Parser.abs_globalScope[i][0]
            # Declaration, typedef, struct and union
            if (typename == 'Decl' or typename == 'Typedef' or
                    typename == 'Struct' or typename == 'Union'):
                # s = self.Parser.abs_globalScope[i][1] + ';\n'
                # 当前语句内容
                stmtStr = self.Parser.abs_globalScope[i][1]
                # 跳过生成 typedef int pthread_t 语句
                if typename == 'Typedef' and "pthread_t" in stmtStr:
                    continue  # 跳过当前循环
                # 生成其他语句
                s = stmtStr + ';\n'                

                # Filtering out those '__VERIFIER_' family functions
                if s.find('__VERIFIER_error') != -1:
                    s = ''
                if s.find('__VERIFIER_assume') != -1:
                    s = ''
                if s.find('__VERIFIER_nondet_') != -1:
                    s = ''

                # Filter turned atomic function
                s = s.replace('__VERIFIER_atomic_cseq_', '', 1)

                output += s
                # Coordinate map
                n = self.Parser.abs_globalScope[i][2]
                oldlineno = self.__lineno + 1
                self.__lineno += utils.countline(s)
                self.logMapLine(oldlineno, self.__lineno, n, typ=typename)

            elif typename == 'FuncDef':  # __VERIFIER_atomic prefix functions
                n = self.Parser.abs_globalScope[i][2]
                s = self.visit(n)
                output += s
                oldlineno = self.__lineno + 1
                self.__lineno += utils.countline(s)
                self.logMapLine(oldlineno, self.__lineno, n, typ='FuncDefAtomic')

        self.__currentGenerateFunct = ''

        # Some functions pointer if any (ad hoc solution)
        functionReferenced = {}
        for functionPtr in self.Parser.funcReferenced:
            functionReferenced[functionPtr] = True

        for functionPtr in functionReferenced:
            if functionPtr in self.Parser.funcBlock:
                s = self.Parser.funcBlock[functionPtr]
                output += s

                n = None
                if functionPtr in self.Parser.funcASTNode:
                    n = self.Parser.funcASTNode[functionPtr]
                oldlineno = self.__lineno + 1
                self.__lineno += utils.countline(s)
                self.logMapLine(oldlineno, self.__lineno, n, typ='FuncDefPtr')

        if self.debug: print 'Before thread functions line is %s' % self.__lineno

        ''' Generating thread functions
        '''

        self.__threadDic.update(data)

        # add by zy 增加处理最高优先级中断函数的逻辑
        for fref in self.__thread_index:  # function (thread) name
            self.__currentGenerateFunct = fref
            # funcID = self.Parser.abs_threadID[fref]
            funcID = self.__thread_index[fref] # 不限制main函数在程序中的位置

            self.custom_indent = 0

            if fref == 'main':
                output += "/* Simulate original main */\n"
            else:
                output += "/* Simulate %s */\n" % fref    
            
            # if fref == 'main':
            #     currentPriority = self.__threadDic['main_task']
            # else:
            #     currentPriority = self.__threadDic[fref]
            # # 获取最大优先级
            # if not self.__threadDic:
            #     raise ValueError("Thread dictionary is empty. Cannot calculate highest priority.")
            if fref == 'main':
                currentPriority = self.__threadDic.get('main_task', None)
            else:
                currentPriority = self.__threadDic.get(fref, None)

            if currentPriority is None:
                raise KeyError("Thread '%s' not found in __threadDic. Current keys: %s" % (fref, list(self.__threadDic.keys())))
            
            HighestPrio = max(self.__threadDic.values())

            # 根据配置选择生成模式
            if self.__use_switch_goto:
                # 使用 switch+goto 优化模式
                output += self._generate_SwitchGoto_Function(fref, funcID)
            elif currentPriority == HighestPrio:  # 如果是最高优先级函数
                output += self.generate_HighestPrioFunction(fref, funcID)
            else:  # 非最高优先级函数，按照原有逻辑处理            
                for i in range(0, self.Parser.abs_functionMaxID[fref]):  # For each pc
                    key = (fref, i)  # Function name and each statement pc
                    stmtType = self.Parser.abs_functionScope[key][0]  # abs_functionScope stores everything in a function
                    pc = self.Parser.abs_functionScope[key][4]  # pc tuple
                    self.custom_indent = self.Parser.abs_functionScope[key][3]

                    # 原有逻辑：处理其他语句
                    if stmtType == 'FuncDef':  # The declaration of function (not the whole function)
                        output += self.generate_FuncDef(fref, i, pc, funcID)
                    elif stmtType == 'OpenBracket':  # only {
                        output += self.generate_OpenBracket(fref, i, pc, funcID)
                    elif stmtType == 'CloseBracket':  # only }
                        output += self.generate_CloseBracket(fref, i, pc, funcID)
                    elif stmtType == 'Typedef':  # typedef
                        output += self.generate_TypeDef(fref, i, pc, funcID)
                    elif stmtType == 'Decl':  # declaration inside function (as it stated)
                        output += self.generate_Decl(fref, i, pc, funcID)
                    elif stmtType == 'AtomicRegion':
                        output += self.generate_AtomicRegion(fref, i, pc, funcID)
                    elif stmtType == 'UnaryOp':
                        output += self.generate_UnaryOp(fref, i, pc, funcID)
                    elif stmtType == 'Assignment':
                        output += self.generate_Assignment(fref, i, pc, funcID)
                    elif stmtType == 'InlinedReturn':  # not anymore
                        output += self.generate_InlinedReturn(fref, i, pc, funcID)
                    elif stmtType == 'Goto':
                        output += self.generate_Goto(fref, i, pc, funcID)
                    elif stmtType == 'GotoSpecial':
                        output += self.generate_GotoSpecial(fref, i, pc, funcID)
                    elif stmtType == 'EmptyStatement':
                        output += self.generate_EmptyStatement(fref, i, pc, funcID)
                    elif stmtType == 'If':
                        output += self.generate_If(fref, i, pc, funcID)
                    elif stmtType == 'Else':
                        output += self.generate_Else(fref, i, pc, funcID)
                    elif stmtType == 'While':
                        output += self.generate_While(fref, i, pc, funcID)
                    elif stmtType == 'Break':  # Not anymore
                        output += self.generate_Break(fref, i, pc, funcID)
                    elif stmtType == 'Continue':  # Not anymore
                        output += self.generate_Continue(fref, i, pc, funcID)
                    elif stmtType == 'FuncCall':
                        output += self.generate_FuncCall(fref, i, pc, funcID)
                    elif stmtType == 'Label':
                        output += self.generate_Label(fref, i, pc, funcID)
                    else:
                        raise ModuleError('Unsupported type of statement\n')
                        output += ''
        # for fref in self.Parser.abs_threadID:                 # function (thread) name
        #     self.__currentGenerateFunct = fref
        #     funcID = self.Parser.abs_threadID[fref]
        #     self.custom_indent = 0
        #     output +=  "/* abs_threadID %s */\n"   % self.Parser.abs_threadID[fref] # add by zy                        # Set indentation
        #     for i in range(0, self.Parser.abs_functionMaxID[fref]):   # For each pc
        #         key = (fref, i)        # Function name and each statement pc
        #         stmtType = self.Parser.abs_functionScope[key][0]      # abs_functionScope store everything in a function
        #         pc = self.Parser.abs_functionScope[key][4]            # pc tuple
        #         self.custom_indent = self.Parser.abs_functionScope[key][3]
        #         # Each statement type will count its own line number
        #         if stmtType == 'FuncDef':               # The declaration of function (not the whole function)
        #             output += self.generate_FuncDef(fref, i, pc, funcID)
        #         elif stmtType == 'OpenBracket':         # only {
        #             output += self.generate_OpenBracket(fref, i, pc, funcID)
        #         elif stmtType == 'CloseBracket':        # only }
        #             output += self.generate_CloseBracket(fref, i, pc, funcID)
        #         elif stmtType == 'Typedef':             # typedef
        #             output += self.generate_TypeDef(fref, i, pc, funcID)
        #         elif stmtType == 'Decl':                # declaration inside function (as it stated)
        #             output += self.generate_Decl(fref, i, pc, funcID)
        #         elif stmtType == 'AtomicRegion':
        #             output += self.generate_AtomicRegion(fref, i, pc, funcID)
        #         elif stmtType == 'UnaryOp':
        #             output += self.generate_UnaryOp(fref, i, pc, funcID)
        #         elif stmtType == 'Assignment':
        #             output += self.generate_Assignment(fref, i, pc, funcID)
        #         elif stmtType == 'InlinedReturn':       # not anymore
        #             output += self.generate_InlinedReturn(fref, i, pc, funcID)
        #         elif stmtType == 'Goto':
        #             output += self.generate_Goto(fref, i, pc, funcID)
        #         elif stmtType == 'GotoSpecial':
        #             output += self.generate_GotoSpecial(fref, i, pc, funcID)
        #         elif stmtType == 'EmptyStatement':
        #             output += self.generate_EmptyStatement(fref, i, pc, funcID)
        #         elif stmtType == 'If':
        #             output += self.generate_If(fref, i, pc, funcID)
        #         elif stmtType == 'Else':
        #             output += self.generate_Else(fref, i, pc, funcID)
        #         elif stmtType == 'While':
        #             output += self.generate_While(fref, i, pc, funcID)
        #         elif stmtType == 'Break':                 # Not anymore
        #             output += self.generate_Break(fref, i, pc, funcID)
        #         elif stmtType == 'Continue':              # Not anymore
        #             output += self.generate_Continue(fref, i, pc, funcID)
        #         elif stmtType == 'FuncCall':
        #             output += self.generate_FuncCall(fref, i, pc, funcID)
        #         elif stmtType == 'Label':
        #             output += self.generate_Label(fref, i, pc, funcID)
        #         else:
        #             raise ModuleError('Unsupported type of statement\n')
        #             output += ''

        self.__currentGenerateFunct = ''

        # output += '/*   Thread simulation */\n'
        output += '/* main function (scheduler) */\n'
        self.__lineno += 1
        output += 'int main()\n'
        self.__lineno += 1
        # Thread simulation
        # if self.debug: print 'Thread simulation line is %s' % self.__lineno
        output += '{\n'
        self.__lineno += 1
        output += '  %s = 0;\n' % self.__svar
        self.__lineno += 1
        # output += '  %s = 0;\n' % self.__error_var
        # self.__lineno += 1

        # For main thread
        if 'main' not in self.__thread_index:
            raise ModuleError('There is a problem with source file\n')
        else:
            output += '  %s%s = 0;\n' % (abs_common.namespace['threadpc'],
                                         self.__thread_index['main'])
            self.__lineno += 1


        '''
            __cs_pc_1 = 0;
            __cs_pc_2 = 0;
            __cs_pc_3 = 0;
            __cs_pc_4 = 0;
            ...
        '''
        # for i in range(0, len(self.Parser.abs_threadID_stack)):
        #     threadname = self.Parser.abs_threadID_stack[i]
        #     output += '  %s%s = 0;\n' % (abs_common.namespace['threadpc'],
        #                                  self.__thread_index[threadname])
        #     self.__lineno += 1
        for threadname, idx in sorted(self.__thread_index.items(), key=lambda x: x[1]):
            if threadname == 'main':
                continue
            output += '  %s%s = 0;\n' % (abs_common.namespace['threadpc'], idx)
            self.__lineno += 1
        '''
            __cs_disable_isr_1 = 0;
            __cs_disable_isr_2 = 0;
            __cs_disable_isr_3 = 0;
            __cs_disable_isr_4 = 0;
            ...
        '''
        for i in range(0, keyNum):
            output += '  __cs_disable_isr_%d = 0;\n' % i
            self.__lineno += 1
        

        if self.__round == 0:
            # Simualting in while loop
            output += '  while (1)\n'
            self.__lineno += 1
            output += '  {\n'
            self.__lineno += 1
            output += '    %s = 0;\n' % self.__svar
            self.__lineno += 1
            # add by zy 主任务的调用，主任务对应的ID为0，
            inputList = {}
            inputList = self.getInputList()
            # output += '    if (%s__cs_disable_isr[0] != 1) main_task();\n' % inputList['main_task'] 
            ic0 = inputList['main_task'].rstrip('&')
            output += '    if (%s) main_task();\n' % (ic0 if ic0 else '1')
            self.__lineno += 1
            # if self.debug: print 'main_thread line is: %s' % self.__lineno
            for i in range(0, len(self.Parser.abs_threadID_stack)):
                threadname = self.Parser.abs_threadID_stack[i]
                output += '    %s = 0;\n' % self.__svar
                self.__lineno += 1


                # output += '    if (%s%s) %s(%s%s);\n' % (
                #     abs_common.namespace['activethread'], self.Parser.abs_threadID[
                #         threadname], threadname,
                #     abs_common.namespace['threadargs'], self.Parser.abs_threadID[threadname])

                # add by zy 按照优先级调度执行主任务和中断函数
                # output += '    if (%s__cs_disable_isr_%s != 1) %s();\n' % (inputList[threadname], self.Parser.abs_threadID[threadname], threadname) 
                if self.__RespCount == 1:
                    output += '    if (%s__cs_disable_isr_%s != 1) %s();\n' % (inputList[threadname], self.__thread_index[threadname], threadname)
                else:
                    output += '    if (%s__cs_disable_isr_%s != 1) {\n' % (inputList[threadname], self.__thread_index[threadname])
                    output += '        %s();\n' % (threadname)
                    output += '        if (__cs_pc_%s == %s) __cs_pc_%s = 0;\n' % (self.__thread_index[threadname], self.Parser.abs_functionMaxPC[threadname], self.__thread_index[threadname])
                    output += '    }\n'

                # output += '    if (%s__cs_disable_isr_%s != 1) %s();\n' % (inputList[threadname], self.Parser.abs_threadID[threadname]-1, threadname) # main zy: 其他函数在前面时候需要用这条语句转化
                self.__lineno += 1
            
            # 在 switch+goto 模式下，添加轮末重置逻辑（确保完成态的 ISR 可以在下一轮再次触发）
            if self.__use_switch_goto:
                output += '\n'
                output += '    // Round end: reset completed ISRs for next round\n'
                for threadname_reset, idx_reset in sorted(self.__thread_index.items(), key=lambda x: x[1]):
                    if threadname_reset == 'main' or threadname_reset == 'main_task':
                        continue
                    maxPC_thread = self.Parser.abs_functionMaxPC.get(threadname_reset, 0)
                    if maxPC_thread > 0:
                        output += '    if (__cs_pc_%d == %d) __cs_pc_%d = 0;\n' % (idx_reset, maxPC_thread, idx_reset)
                        self.__lineno += 1
                output += '\n'
            
            output += '  }\n'
            self.__lineno += 1
        else:
            for u in range(0, self.__round):
                output += '  {\n'
                self.__lineno += 1
                output += '    %s = 0;\n' % self.__svar
                self.__lineno += 1

                output += '    main_thread();\n'
                self.__lineno += 1
                # if self.debug: print 'main_thread line is: %s' %
                # self.__lineno
                for i in range(0, len(self.Parser.abs_threadID_stack)):
                    threadname = self.Parser.abs_threadID_stack[i]
                    output += '    %s = 0;\n' % self.__svar
                    self.__lineno += 1


                    output += '    if (%s%s) %s(%s%s);\n' % (
                        abs_common.namespace['activethread'], self.__thread_index[
                            threadname], threadname,
                        abs_common.namespace['threadargs'], self.__thread_index[threadname])
                    self.__lineno += 1
                output += '  }\n'
                self.__lineno += 1

            # Last call to main
            output += '  {\n'
            self.__lineno += 1
            output += '    %s = 0;\n' % self.__svar
            self.__lineno += 1
            output += '    main_thread();\n'
            self.__lineno += 1
            output += '  }\n'
            self.__lineno += 1

        output += '}\n'
        self.__lineno += 1

        # if self.debug: print 'Total lines is: %s' % self.__lineno

        return output

    # ----------------------------- HARDEST STUFF ----------------------------
    def generate_FuncCall(self, fname, id, pc, funcID):
        s = ''
        fref = self.Parser.abs_functionScope[(fname, id)][1]
        node = self.Parser.abs_functionScope[(fname, id)][2]
        args = self.visit(node.args)
        addIndent = len(self.__pc_stack) * 4  # Indentation
        realpc = pc[0]
        mutexes = self.Parser.abs_functionScope[(fname, id)][5]

        current_dir = os.path.dirname(os.path.abspath(__file__))
        json_file_path = os.path.join(current_dir, 'data.json')

        with open(json_file_path, 'r') as file:
            data = json.load(file)

        __cs_ISRIndex = {}
        __cs_ISRIndex = self.__thread_index.copy()
        # for key in data.keys():
        #     if key == "main_task":
        #         __cs_ISRIndex[key] = 0 
        #     else:
        #         # 获取键的最后一个字符并转为整数
        #         __cs_ISRIndex[key] = int(key[-1])

        '''
                __cs_ISRIndex = {
                    "main_task": 0,
                    "isr_1": 1,
                    "isr_2": 2
                }
        '''

        # 判断是否为特定函数调用
        if fref == 'disable_isr':

            s += self._make_custom_indent(delta=addIndent + 4) + '/*%s(%s);*/\n' % (fref, args)
            if not self.__ignore_masking:
                if args == '-1':  # 如果参数是 -1，禁用除当前函数外的所有线程
                    for i in __cs_ISRIndex.keys():
                        if i != self.__currentFun:  # 排除当前函数
                            # s += self._make_custom_indent(delta=addIndent + 4) + '__cs_disable_isr[%d] = 1;\n' % __cs_ISRIndex[i]
                            s += self._make_custom_indent(delta=addIndent + 4) + '__cs_disable_isr_%d = 1;\n' % __cs_ISRIndex[i]
                            self.__lineno += 1
                    # s += self._make_custom_indent(delta=addIndent + 4) + '__cs_disable_isr[0] = 1;\n'   # 禁用主线程
                else:
                    # 如果参数是线程编号，匹配 __cs_ISRIndex 的值
                    for i, idx in __cs_ISRIndex.items():
                        if str(idx) == args:  # 匹配线程编号
                            # s += self._make_custom_indent(delta=addIndent + 4) + '__cs_disable_isr[%d] = 1;\n' % idx
                            s += self._make_custom_indent(delta=addIndent + 4) + '__cs_disable_isr_%d = 1;\n' % idx
                            self.__lineno += 1
            s = self._generate_SingleStmt(funcID, realpc, s, mutexes=mutexes, typ='FuncCall_disable_isr', nodes=node, visible=True)

        elif fref == 'enable_isr':
            s += self._make_custom_indent(delta=addIndent + 4) + '/*%s(%s);*/\n' % (fref, args)
            # 
            if not self.__ignore_masking:
                if args == '-1':  # 如果参数是 -1，启用除当前函数外的所有线程
                    for i in __cs_ISRIndex.keys():
                        if i != self.__currentFun:  # 排除当前函数
                            # s += self._make_custom_indent(delta=addIndent + 4) + '__cs_disable_isr[%d] = 0;\n' % __cs_ISRIndex[i]
                            s += self._make_custom_indent(delta=addIndent + 4) + '__cs_disable_isr_%d = 0;\n' % __cs_ISRIndex[i]
                            self.__lineno += 1
                    # s += self._make_custom_indent(delta=addIndent + 4) + '__cs_disable_isr[0] = 0;\n'  # 启用主线程
                else:
                    # 如果参数是线程编号，匹配 __cs_ISRIndex 的值
                    for i, idx in __cs_ISRIndex.items():
                        if str(idx) == args:  # 匹配线程编号
                            # s += self._make_custom_indent(delta=addIndent + 4) + '__cs_disable_isr[%d] = 0;\n' % idx
                            s += self._make_custom_indent(delta=addIndent + 4) + '__cs_disable_isr_%d = 0;\n' % idx
                            self.__lineno += 1
            s = self._generate_SingleStmt(funcID, realpc, s, mutexes=mutexes, typ='FuncCall_enable_isr', nodes=node, visible=True)  
        # ------------------------------------------------------------------
        # PTHREAD EXPLAIN
        # pthread_create
        # pthread_join
        # pthread_exit
        # ------------------------------------------------------------------
        elif fref == 'pthread_create':
            fname = args[:args.rfind(',')]
            fname = fname[fname.rfind(',') + 2:]
            fname = fname.replace('&', '')
            fArg = args[args.rfind(',') + 2:]
            # fArg = fArg.replace('&', '')
            # fArg = re.sub(r'\(.+\)', r'', fArg)
            if (fArg == '0' or
                    fArg == 'NULL' or
                    fArg.find(' 0') != -1 or
                    fArg.find(' NULL') != -1):
                fArg = '0'
            # else:
                # fArg = '&' + fArg

            threadID = self.__thread_index[fname]
            s += self._make_custom_indent(delta=addIndent + 4) + '%s%s = 1;\n' % (
                abs_common.namespace['activethread'], threadID)
            s += self._make_custom_indent(delta=addIndent + 4) + '%s%s = %s;\n' % (
                abs_common.namespace['threadargs'], threadID, fArg)
            s = self._generate_SingleStmt(funcID, realpc, s, mutexes=mutexes,
                                          typ='FuncCall_pthread_create', nodes=node)

        elif fref == 'pthread_join':
            threadname = args[:args.find(',')]
            fname = self.Parser.abs_threadNameToF[threadname]
            threadID = self.__thread_index[fname]
            maxPC = self.Parser.abs_functionMaxPC[fname]
            s += self._make_custom_indent(delta=addIndent + 4) + '__VERIFIER_assume(%s%s == %s);\n' % (
                abs_common.namespace['threadpc'], threadID, maxPC)
            s = self._generate_SingleStmt(funcID, realpc, s, mutexes=mutexes,
                                          typ='FuncCall_pthread_join', nodes=node)

        elif fref == 'pthread_exit':
            raise ModuleError(
                'pthread_exit statement exists in the translation\n')

        # ------------------------------------------------------------------
        # PTHREAD MUTEX (MUTUAL EXCLUSION)
        # a mutex has these value
        # INIT or FREE (0) : this mutex has not been acquired by any threads
        # > 0 : the thread id which acquiring the mutex
        # ------------------------------------------------------------------
        elif fref == 'pthread_mutex_init':
            mutexname = args[:args.rfind(',')]  # Mutex name in this function
            if args.startswith('&'):
                mutexname = mutexname.replace('&', '', 1)
            else:
                mutexname = '*' + mutexname
            s += self._make_custom_indent(delta=addIndent + 4) + \
                '%s = 0;\n' % mutexname
            s = self._generate_SingleStmt(funcID, realpc, s, mutexes=mutexes,
                                          typ='FuncCall_pthread_mutex_init', nodes=node)

        elif fref == 'pthread_mutex_lock':
            mutexname = args
            if mutexname.startswith('&'):
                mutexname = mutexname.replace('&', '', 1)
            else:
                mutexname = '*' + mutexname
            # s += self._make_custom_indent(delta=addIndent+4) + '__VERIFIER_assume(%s != -1);\n' % mutexname
            s += self._make_custom_indent(delta=addIndent + 4) + \
                '__VERIFIER_assume(%s == 0);\n' % mutexname
            s += self._make_custom_indent(delta=addIndent + 4) + '%s = %s;\n' % (
                mutexname, funcID)
            s = self._generate_SingleStmt(funcID, realpc, s, mutexes=mutexes,
                                          typ='FuncCall_pthread_mutex_lock', nodes=node)

        elif fref == 'pthread_mutex_unlock':
            mutexname = args
            if mutexname.startswith('&'):
                mutexname = mutexname.replace('&', '', 1)
            else:
                mutexname = '*' + mutexname
            s += self._make_custom_indent(delta=addIndent + 4) + \
                '%s = 0;\n' % mutexname
            s = self._generate_SingleStmt(funcID, realpc, s, mutexes=mutexes,
                                          typ='FuncCall_pthread_mutex_unlock', nodes=node)

        elif fref == 'pthread_mutex_destroy':
            mutexname = args
            if mutexname.startswith('&'):
                mutexname = mutexname.replace('&', '', 1)
            else:
                mutexname = '*' + mutexname
            s += self._make_custom_indent(delta=addIndent + 4) + \
                '%s = -1;\n' % mutexname
            s = self._generate_SingleStmt(funcID, realpc, s, mutexes=mutexes,
                                          typ='FuncCall_pthread_mutex_destroy', nodes=node)

        # ---------------------------------------------------------------
        # CONDITIONAL VARIABLE EXPLANATION
        # a conditional variable has these values
        # NO_SIGNAL (0): initialized value (or after this thread wake up
        #                       from pthread_cond_signal)
        # DESTROYED (-1): being destroyed
        # SIGNAL (1): being signaled by phread_cond_signal
        # BROADCAST (2): being broadcast by pthread_cond_broadcast
        # ---------------------------------------------------------------
        elif fref == 'pthread_cond_init':
            condname = args[:args.rfind(',')]
            if condname.startswith('&'):
                condname = condname.replace('&', '', 1)
            else:
                condname = '*' + condname
            s += self._make_custom_indent(delta=addIndent + 4) + \
                '%s = 0;\n' % condname
            s = self._generate_SingleStmt(funcID, realpc, s, mutexes=mutexes,
                                          typ='FuncCall_pthread_cond_init', nodes=node)

        elif fref == 'pthread_cond_destroy':
            condname = args
            if condname.startswith('&'):
                condname = condname.replace('&', '', 1)
            else:
                condname = '*' + condname
            s += self._make_custom_indent(delta=addIndent + 4) + \
                '%s = -1;\n' % condname
            s = self._generate_SingleStmt(funcID, realpc, s, mutexes=mutexes,
                                          typ='FuncCall_pthread_cond_destroy', nodes=node)

        elif fref == 'pthread_cond_wait':
            # First stage
            # (Atomically unlock the mutex and block on this conditional variable)
            condname = args[:args.rfind(',')]
            if condname.startswith('&'):
                condname = condname.replace('&', '', 1)
            else:
                condname = '*' + condname
            mutexname = args[args.find(',') + 2:]
            if mutexname.startswith('&'):
                mutexname = mutexname.replace('&', '', 1)
            else:
                mutexname = '*' + mutexname

            # s += self._make_custom_indent(delta=addIndent+4) + '__VERIFIER_assume(%s != -1);\n' % condname
            s += self._make_custom_indent(delta=addIndent + 4) + '__VERIFIER_assume(%s == %s);\n' % (
                mutexname, funcID)
            s += self._make_custom_indent(delta=addIndent + 4) + \
                '%s = 0;\n' % mutexname
            # force context switch
            s += self._make_custom_indent(delta=addIndent + 4) + '%s%s = %s;\n' % (
                abs_common.namespace['threadpc'], funcID, realpc + 1)

            # s += self._make_custom_indent(delta=addIndent+4) + 'return %s\n' % self.__threadIsVoid[fname]
            s += self._make_custom_indent(delta=addIndent + 4) + \
                '%s = 2;\n' % self.__svar

            firststmt = self._generate_SingleStmt(funcID, realpc, s, mutexes=mutexes,
                                                  typ='FuncCall_pthread_cond_wait', nodes=node)

            # Reacquire the mutex by the signal from conditional variable
            s = ''
            s += self._make_custom_indent(delta=addIndent + 4) + '__VERIFIER_assume(%s == 1 || %s == 2);\n' % (
                condname, condname)
            s += self._make_custom_indent(delta=addIndent + 4) + \
                '__VERIFIER_assume(%s == 0);\n' % mutexname
            s += self._make_custom_indent(delta=addIndent + 4) + \
                '%s = %s;\n' % (mutexname, funcID)
            newmutexes = []
            for i in range(0, len(mutexes)):
                if mutexes[i] != mutexname:
                    newmutexes.append(mutexes[i])
            secondstmt = self._generate_SingleStmt(funcID, realpc + 1, s, mutexes=tuple(newmutexes),
                                                   typ='FuncCall_pthread_cond_wait', nodes=node)
            s = firststmt + secondstmt

        elif fref == 'pthread_cond_signal':
            condname = args
            if condname.startswith('&'):
                condname = condname.replace('&', '', 1)
            else:
                condname = '*' + condname
            # s += self._make_custom_indent(delta=addIndent+4) + '__VERIFIER_assume(%s != -1);\n' % condname
            s += self._make_custom_indent(delta=addIndent + 4) + \
                '%s = 1;\n' % condname
            s = self._generate_SingleStmt(funcID, realpc, s, mutexes=mutexes,
                                          typ='FuncCall_pthread_cond_signal', nodes=node)

        elif fref == 'pthread_cond_broadcast':
            condname = args
            if condname.startswith('&'):
                condname = condname.replace('&', '', 1)
            else:
                condname = '*' + condname
            # s += self._make_custom_indent(delta=addIndent+4) + '__VERIFIER_assume(%s != -1);\n' % condname
            s += self._make_custom_indent(delta=addIndent + 4) + \
                '%s = 2;\n' % condname
            s = self._generate_SingleStmt(funcID, realpc, s, mutexes=mutexes,
                                          typ='FuncCall_pthread_cond_broadcast', nodes=node)

        # __VERIFIER__ family
        elif fref == '__VERIFIER_assume':
            s += self._make_custom_indent(delta=addIndent + 4) + \
                '%s(%s);\n' % (fref, args)
            s = self._generate_SingleStmt(funcID, realpc, s, mutexes=mutexes,
                                          typ='FuncCall___VERIFIER_assume', nodes=node)

        elif fref == '__VERIFIER_assert':
            error = '__cseq_error();'
            s += self._make_custom_indent(delta=addIndent + 4) + \
                'if (!(%s)) %s\n' % (args, error)
            # s += self._make_custom_indent(delta=addIndent+4) + 'if (!(%s)) %s = 1;\n' % (args, self.__error_var)
            s = self._generate_SingleStmt(funcID, realpc, s, mutexes=mutexes,
                                          typ='FuncCall___VERIFIER_assert', nodes=node)

        elif fref == '__VERIFIER_error':
            error = '__cseq_error();'
            s += self._make_custom_indent(delta=addIndent + 4) + '%s\n' % error
            # s += self._make_custom_indent(delta=addIndent+4) + '%s = 1;\n' % self.__error_var
            s = self._generate_SingleStmt(funcID, realpc, s, mutexes=mutexes,
                                          typ='FuncCall___VERIFIER_error', nodes=node)

        elif fref.startswith('__VERIFIER_nondet'):
            s += self._make_custom_indent(delta=addIndent + 4) + \
                '%s(%s);\n' % (fref, args)
            s = self._generate_SingleStmt(funcID, realpc, s, mutexes=mutexes,
                                          typ='FuncCall_%s' % fref, nodes=node)

        elif fref.startswith('__VERIFIER_atomic'):
            fref = fref.replace('__VERIFIER_atomic_cseq_', '', 1)
            s += self._make_custom_indent(delta=addIndent + 4) + \
                '%s(%s);\n' % (fref, args)
            s = self._generate_SingleStmt(funcID, realpc, s, mutexes=mutexes,
                                          typ='FuncCall_%s' % fref, nodes=node)

        # malloc and free
        elif fref == 'malloc':
            s += self._make_custom_indent(delta=addIndent + 4) + '%s(%s);\n' % (
                abs_common.namespace['malloc'], args)
            s = self._generate_SingleStmt(funcID, realpc, s, mutexes=mutexes,
                                          typ='FuncCall_malloc', nodes=node)

        elif fref == 'free':
            s += self._make_custom_indent(delta=addIndent + 4) + \
                '%s(%s);\n' % (fref, args)
            s = self._generate_SingleStmt(funcID, realpc, s, mutexes=mutexes,
                                          typ='FuncCall_free', nodes=node)

        # __cs__ family
        elif fref == '__cs_exit':
            # This statement is treated as the return statement of thread
            # Assign destpc to the last statement
            destpc = self.Parser.abs_functionMaxPC[self.__currentGenerateFunct]
            s = self._generate_Exit_stmt(funcID, realpc, destpc, mutexes,
                                         typ='FuncCall___cs_exit', nodes=node)

        elif fref == '__cs_init_scalar':
            s += self._make_custom_indent(delta=addIndent + 4) + \
                '%s(%s);\n' % (fref, args)
            s = self._generate_SingleStmt(funcID, realpc, s, mutexes=mutexes,
                                          typ='FuncCall___cs_init_scalar', nodes=node)

        # non-defined funccall
        elif fref == 'assume':
            s += self._make_custom_indent(delta=addIndent + 4) + \
                '__VERIFIER_assume(%s);\n' % args
            s = self._generate_SingleStmt(funcID, realpc, s, mutexes=mutexes,
                                          typ='FuncCall_assume', nodes=node)

        elif fref == 'assert':
            # zhangyuan 如果验证后端是CBMC，不修改断言的格式，便于一次性查看多个断言的真假
            if self.__backend == 'cbmc':# or self.__backend == 'uautomizer':
                s += self._make_custom_indent(delta=addIndent + 4) + 'assert(%s);\n' % args
            elif self.__backend == 'uautomizer':
                    error = '__VERIFIER_error();'
                    s += self._make_custom_indent(delta=addIndent + 4) + \
                    'if (!(%s)) %s\n' % (args, error)
            else:    
                error = '__cseq_error();'
                s += self._make_custom_indent(delta=addIndent + 4) + \
                    'if (!(%s)) %s\n' % (args, error)
            s = self._generate_SingleStmt(funcID, realpc, s, mutexes=mutexes,
                                        typ='FuncCall_assert', nodes=node)
            # error = '__cseq_error();'
            # s += self._make_custom_indent(delta=addIndent + 4) + \
            #     'if (!(%s)) %s\n' % (args, error)
            # # s += self._make_custom_indent(delta=addIndent+4) + 'if (!(%s)) %s = 1;\n' % (args, self.__error_var)
            # s = self._generate_SingleStmt(funcID, realpc, s, mutexes=mutexes,
            #                               typ='FuncCall_assert', nodes=node)

        elif fref.startswith('nondet_uint'):
            s += self._make_custom_indent(delta=addIndent + 4) + \
                '__VERIFIER_nondet_uint();\n'
            s = self._generate_SingleStmt(funcID, realpc, s, mutexes=mutexes,
                                          typ='FuncCall_%s' % fref, nodes=node)

        elif fref.startswith('nondet'):
            s += self._make_custom_indent(delta=addIndent + 4) + \
                '__VERIFIER_nondet_int();\n'
            s = self._generate_SingleStmt(funcID, realpc, s, mutexes=mutexes,
                                          typ='FuncCall_%s' % fref, nodes=node)
        # Prevent false analysis
        elif fref == 'strcpy' and self.__backend in ('cpachecker', 'seahorn'):
            raise ModuleError('Unsupported type of function %s\n' % fref)
            sys.exit(1)

        elif fref not in self.Parser.funcBody:
            s += self._make_custom_indent(delta=addIndent + 4) + \
                '%s(%s);\n' % (fref, args)
            s = self._generate_SingleStmt(funcID, realpc, s, mutexes=mutexes,
                                          typ='FuncCall_%s' % fref, nodes=node)

        else:
            s += self._make_custom_indent(delta=addIndent + 4) + \
                '%s(%s);\n' % (fref, args)
            s = self._generate_SingleStmt(funcID, realpc, s, mutexes=mutexes,
                                          typ='FuncCall_%s' % fref, nodes=node)

            raise ModuleError(
                'Some function call: %s should not be here\n' % fref)
        return s
    # ----------------------------- HARDEST STUFF ----------------------------

    # ----------------------------- BIT NOISY STUFF --------------------------
    def generate_While(self, fname, id, pc, funcID):
        node = self.Parser.abs_functionScope[(fname, id)][2]
        startpc = pc[0]
        endpc = pc[2]
        # Put this while to stack
        addIndent = len(self.__pc_stack) * 4  # Indentation
        self.__pc_stack.append(('While', pc))
        cond = ''
        if node.cond:
            cond = self.visit(node.cond)
        if not cond:
            cond = '1'

        # There will be no mutex checking in WHILE, each stmt inside must check
        # by its own
        # if (s == RESUME  && pc == L)  s = EXECUTE;
        s = self._make_custom_indent(delta=addIndent)
        s += 'if (%s == 0 && %s%s == %s) %s = 1;\n' % (
            self.__svar, abs_common.namespace['threadpc'], funcID, startpc, self.__svar)
        # if (s == EXECUTE && * )          { pc = L; s = SUSPEND;}
        s += self._make_custom_indent(delta=addIndent)
        s += 'if (%s == 1 && __VERIFIER_nondet_bool()) {%s%s = %s; %s = 2;}\n' % (
            self.__svar, abs_common.namespace['threadpc'], funcID, startpc, self.__svar)
        # while (     (s == RESUME && pc > Li && pc <= Lj)
        #            || (s == EXECUTE && condition))
        # {
        #    // {translation of statement}
        # }
        s += self._make_custom_indent(delta=addIndent)
        s += 'while ((%s == 0 && %s%s <= %s) || ((%s == 1) && (%s)))\n' % (
            self.__svar, abs_common.namespace['threadpc'], funcID, endpc,
            self.__svar, cond)
        self.__lineno += 1
        self.logMapLine(self.__lineno, self.__lineno, node, typ='While')
        return s

    def generate_Break(self, fname, id, pc, funcID):
        # Find innermost while loop
        whilePC = (-1, -1, -1)
        for i in reversed(range(0, len(self.__pc_stack))):
            # print self.__pc_stack
            if self.__pc_stack[i][0] == 'While':
                whilePC = self.__pc_stack[i][1]  # get the pc of while loop
                break
        realpc = pc[0]
        node = self.Parser.abs_functionScope[(fname, id)][2]
        mutexes = self.Parser.abs_functionScope[(fname, id)][5]
        # hasMutex = False if len(mutexes) == 0 else True
        destpc = whilePC[2]
        if destpc == -1:
            destpc = realpc
            raise ModuleError(
                'Destination pc of break statement should exist\n')
        # Set destination pc to the one after while loop
        destpc += 1
        return self._generate_Goto_like_stmt(funcID, realpc, destpc, mutexes,
                                             typ='Break', nodes=node)

    def generate_Continue(self, fname, id, pc, funcID):
        # Find innermost while loop
        whilePC = (-1, -1, -1)
        for i in reversed(range(0, len(self.__pc_stack))):
            if self.__pc_stack[i][0] == 'While':
                whilePC = self.__pc_stack[i][1]  # get the pc
                break
        realpc = pc[0]
        node = self.Parser.abs_functionScope[(fname, id)][2]
        mutexes = self.Parser.abs_functionScope[(fname, id)][5]
        # hasMutex = False if len(mutexes) == 0 else True
        destpc = whilePC[0]
        if destpc == -1:
            # TODO: adhoc fix for competition
            destpc = realpc + 1
            raise ModuleError('Destination of continue stmt must exist\n')
        return self._generate_Goto_like_stmt(funcID, realpc, destpc, mutexes,
                                             typ='Continue', nodes=node)

    def generate_If(self, fname, id, pc, funcID):
        node = self.Parser.abs_functionScope[(fname, id)][2]
        startpc = pc[0]
        midpc = pc[1]
        endpc = pc[2]
        # Put if to stack to know where the other statement goes
        addIndent = len(self.__pc_stack) * 4
        cond = ''
        if node.cond:
            cond = self.visit(node.cond)
        if not cond:
            cond = '1'

        if node.iffalse:
            self.__pc_stack.append(('Ifelse', pc, startpc, midpc, endpc, cond))
        else:
            self.__pc_stack.append(('If', pc))
            endpc = midpc

        # There will be no mutex checking in IF, each stmts inside must check
        # by its own
        # if (s == RESUME  && pc == L)  s = EXECUTE;
        s = self._make_custom_indent(delta=addIndent)
        # s += '// s: %s, m: %s, e: %s\n' % (startpc, midpc, endpc)
        s += 'if (%s == 0 && %s%s == %s) %s = 1;\n' % (
            self.__svar, abs_common.namespace['threadpc'], funcID, startpc, self.__svar)
        # if (s == EXECUTE && * )          { pc = L; s = SUSPEND;}
        s += self._make_custom_indent(delta=addIndent)
        s += 'if (%s == 1 && __VERIFIER_nondet_bool()) {%s%s = %s; %s = 2;}\n' % (
            self.__svar, abs_common.namespace['threadpc'], funcID, startpc, self.__svar)
        # if (     (s == RESUME && pc > Li && pc <= Lj)
        #      || (s == EXECUTE && condition))
        # {
        #    // {translation of  LBlock1;}
        # } [else
        # {
        #    // {translation of L Block2;}
        # }]
        s += self._make_custom_indent(delta=addIndent)
        s += 'if ((%s == 0 && %s%s <= %s) || (%s == 1 && (%s)))\n' % (
            self.__svar, abs_common.namespace['threadpc'], funcID, midpc,
            self.__svar, cond)
        # Log map line
        self.__lineno += 1
        if node.iffalse:
            self.logMapLine(self.__lineno, self.__lineno, node, typ='IfElse')
        else:
            self.logMapLine(self.__lineno, self.__lineno, node, typ='If')
        return s

    def generate_Else(self, fname, id, pc, funcID):
        addIndent = len(self.__pc_stack) * 4
        if len(self.__pc_stack) == 0:
            raise ModuleError("Else statement does not have if")
        if self.__pc_stack[-1][0] != 'Ifelse':
            raise ModuleError("Else statement does not have if again")
        s = self._make_custom_indent(delta=addIndent - 4) + 'else\n'
        midpc, endpc, cond = self.__pc_stack[-1][3], self.__pc_stack[-1][4], self.__pc_stack[-1][5]
        #  if (   (RESUME && pc > Li && pc < Lk)
        # || (EXECUTE))
        s += 'if ((%s == 0 && %s%s <= %s) || (%s == 1))' % (
            self.__svar, abs_common.namespace['threadpc'], funcID, endpc,
            self.__svar)
        self.__lineno += 1
        # No need to record line here
        return s

    def generate_OpenBracket(self, fname, id, pc, funcID):
        addIndent = len(self.__pc_stack) * 4
        bracketType = self.Parser.abs_functionScope[(fname, id)][1]
        s = ''
        if (len(self.__pc_stack) > 0 and
                bracketType in ('While', 'If', 'Else')):
            s = self._make_custom_indent(delta=addIndent - 4) + '{\n'
            self.__lineno += 1
            return s
        elif bracketType in ('FuncDef', 'Block'):
            self.__lineno += 1
            return self._make_custom_indent(delta=addIndent) + '{\n'
        else:
            self.__lineno += 1
            return '/* wrong type (%s) open bracket */\n' % (bracketType)
        # No need to record line here

    def generate_CloseBracket(self, fname, id, pc, funcID):
        # Pop while or if from stack
        s = ''
        addIndent = len(self.__pc_stack) * 4
        bracketType = self.Parser.abs_functionScope[(fname, id)][1]
        if (len(self.__pc_stack) > 0 and
                bracketType in ('While', 'If', 'Else')):
            addIndent -= 4
            s = self._make_custom_indent(delta=addIndent) + '}\n'
            self.__lineno += 1
            if (bracketType == 'While' or bracketType == 'Else'):
                self.__pc_stack.pop()
            if bracketType == 'If' and self.__pc_stack[-1][0] == 'If':
                self.__pc_stack.pop()
            return s
        elif bracketType in ('FuncDef'):
            self.__lineno += 1
            return self._make_custom_indent(delta=addIndent) + '}\n'
        elif bracketType in ('Block'):
            self.__lineno += 1
            return self._make_custom_indent(delta=addIndent) + '}\n'
        else:
            self.__lineno += 1
            return '/* wrong type (%s) close bracket */\n' % (bracketType)
        # No need to record line here

    # ----------------------------- END BIT NOISY STUFF ----------------------

    # ----------------------------- LITTLE NOISY STUFF -----------------------
    def generate_Goto(self, fname, id, pc, funcID):
        realpc = pc[0]
        node = self.Parser.abs_functionScope[(fname, id)][2]
        mutexes = self.Parser.abs_functionScope[(fname, id)][5]
        label = node.name
        labelpc = self.Parser.abs_functionLabels[fname][label]
        return self._generate_Goto_stmt(funcID, realpc, labelpc, mutexes,
                                        typ='Goto', nodes=node)

    def generate_GotoSpecial(self, fname, id, pc, funcID):
        realpc = pc[0]
        node = self.Parser.abs_functionScope[(fname, id)][2]
        mutexes = self.Parser.abs_functionScope[(fname, id)][5]
        label = node.name
        labelpc = self.Parser.abs_functionLabels[fname][label]
        return self._generate_GotoSpecial_stmt(funcID, realpc, labelpc, mutexes,
                                               typ='Goto', nodes=node)

    def generate_Label(self, fname, id, pc, funcID):
        node = self.Parser.abs_functionScope[(fname, id)][2]
        if type(node.stmt) == c_ast.EmptyStatement:
            self.logMapLine(self.__lineno + 11, self.__lineno + 11, node, typ='Label')
        else:
            raise ModuleError("Label has non empty statement")
        addIndent = len(self.__pc_stack) * 4
        return self._make_custom_indent(delta=addIndent) + node.name + ':;\n'

    # Not use anymore
    def generate_InlinedReturn(self, fname, id, pc, funcID):
        addIndent = len(self.__pc_stack) * 4
        s = ''
        nodelist = self.Parser.abs_functionScope[(fname, id)][2]
        mutexes = self.Parser.abs_functionScope[(fname, id)][5]
        realpc = pc[0]
        if len(nodelist) != 2:
            raise ModuleError('There are more than two statements in this inlined return\n')

        # simple statement first and a goto
        s += self._make_custom_indent(delta=addIndent + 4) + \
            self.visit(nodelist[0]) + ';\n'
        label = nodelist[1].name
        labelpc = self.Parser.abs_functionLabels[fname][label]

        s += self._make_custom_indent(delta=addIndent + 4) + '%s%s = %s;\n' % (
            abs_common.namespace['threadpc'], funcID, labelpc)

        s += self._make_custom_indent(delta=addIndent + 4) + \
            'if(__VERIFIER_nondet_bool()) %s = 2; else %s = 0;\n' % (
                self.__svar, self.__svar)

        s = self._generate_SingleStmt(funcID, realpc, s, mutexes=mutexes,
                                      typ='InlinedReturn', nodes=nodelist)
        return s

    # ----------------------------- END LITTLE NOISY STUFF -------------------

    # ----------------------------- NOT SO EASY STUFF ------------------------
    def generate_UnaryOp(self, fname, id, pc, funcID):
        s = ''
        node = self.Parser.abs_functionScope[(fname, id)][2]
        mutexes = self.Parser.abs_functionScope[(fname, id)][5]
        visible = self.Parser.abs_functionScope[(fname, id)][6]
        realpc = pc[0]
        # This will return exactly what it is
        addIndent = len(self.__pc_stack) * 4
        s += self._make_custom_indent(delta=addIndent + 4) + \
            self.visit(node) + ';\n'
        s = self._generate_SingleStmt(funcID, realpc, s, mutexes=mutexes,
                                      typ='UnaryOp', nodes=node, visible=visible)
        return s

    def generate_Assignment(self, fname, id, pc, funcID):
        s = ''
        addIndent = len(self.__pc_stack) * 4
        node = self.Parser.abs_functionScope[(fname, id)][2]
        mutexes = self.Parser.abs_functionScope[(fname, id)][5]
        visible = self.Parser.abs_functionScope[(fname, id)][6]
        realpc = pc[0]
        # This will return exactly what it is
        s += self._make_custom_indent(delta=addIndent + 4) + \
            self.visit(node) + ';\n'
        s = self._generate_SingleStmt(funcID, realpc, s, mutexes=mutexes,
                                      typ='Assignment', nodes=node, visible=visible)
        return s

    def generate_EmptyStatement(self, fname, id, pc, funcID):
        addIndent = len(self.__pc_stack) * 4
        s = self._make_custom_indent(
            delta=addIndent + 4) + '/* EmptyStatement */;\n'
        # node = self.Parser.abs_functionScope[(fname, id)][2]
        # mutexes = self.Parser.abs_functionScope[(fname, id)][5]
        # realpc = pc[0]
        # # This will return exactly what it is
        # s = self._generate_SingleStmt(funcID, realpc, s, mutexes=mutexes,
        #                               typ='EmptyStatement', nodes=node)
        return ''
        return s

    def generate_AtomicRegion(self, fname, id, pc, funcID):
        s = ''      # string
        nodelist = self.Parser.abs_functionScope[(fname, id)][2]   # list of nodes
        mutexes = self.Parser.abs_functionScope[(fname, id)][5]    # list of mutexes
        realpc = pc[0]                                             # start pc
        # This will return exactly what it is
        addIndent = len(self.__pc_stack) * 4
        gnodelist = []
        for i in range(0, len(nodelist)):
            a = self.visit(nodelist[i]) + ';\n'   # generate each stmts in atomic region
            gnodelist.append((nodelist[i], utils.countline(a)))
            s += self._make_custom_indent(delta=addIndent + 4) + a

        s = self._generate_SingleStmt(funcID, realpc, s, mutexes=mutexes,
                                      typ='AtomicRegion', nodes=tuple(gnodelist))
        return s

    # ----------------------------- END NOT SO EASY STUFF --------------------

    # ----------------------------- EASY STUFF -------------------------------
    def generate_TypeDef(self, fname, id, pc, funcID):
        ''' No pc require '''
        addIndent = len(self.__pc_stack) * 4
        s = self._make_custom_indent(
            delta=addIndent) + self.Parser.abs_functionScope[(fname, id)][1] + ';\n'
        # Log line
        n = self.Parser.abs_functionScope[(fname, id)][2]
        oldlineno = self.__lineno + 1
        self.__lineno += utils.countline(s)
        self.logMapLine(oldlineno, self.__lineno, n, typ='TypedefF')
        return s

    def generate_Decl(self, fname, id, pc, funcID):
        ''' No pc require '''
        addIndent = len(self.__pc_stack) * 4
        s = self._make_custom_indent(
            delta=addIndent) + self.Parser.abs_functionScope[(fname, id)][1] + ';\n'
        # log line
        n = self.Parser.abs_functionScope[(fname, id)][2]
        oldlineno = self.__lineno + 1
        self.__lineno += utils.countline(s)
        self.logMapLine(oldlineno, self.__lineno, n, typ='DeclF')
        return s

    def generate_FuncDef(self, fname, id, pc, funcID):
        s = self.Parser.abs_functionScope[(fname, id)][1] + '\n'

        # log line
        n = self.Parser.abs_functionScope[(fname, id)][2]
        self.__lineno += 1
        self.logMapLine(self.__lineno, self.__lineno, n, typ='FuncDef')

        if fname == 'main':
            # return s.replace('main', 'main_thread', 1)
            return s.replace('main', 'main_task', 1)
        else:
            return s

    # ----------------------------- END EASY STUFF ---------------------------

    # -------------------------  TEMPLATE ------------------------------------
    def _generate_SingleStmt(self, funcID, currpc, stmts, mutexes=[], typ='', nodes=None, visible=True):
        if visible:
            # fname = self.__threadNameByID[str(funcID)]
            hasMutex = False if len(mutexes) == 0 else True
            addIndent = len(self.__pc_stack) * 4
            s = self._make_custom_indent(delta=addIndent)

            # if (s == RESUME  && pc == L)  s = EXECUTE;
            s += 'if (%s == 0 && %s%s == %s) %s = 1;\n' % (
                self.__svar, abs_common.namespace['threadpc'], funcID, currpc, self.__svar)
            # if (s == EXECUTE )            if(*) { pc = L; s = SUSPEND;} else { statement; }
            s += self._make_custom_indent(delta=addIndent)
            cond = '(%s == 1)' % (self.__svar)
            if hasMutex:
                condMutex = ''
                for i in range(0, len(mutexes)):
                    condMutex += ' && (%s == %s)' % (mutexes[i], funcID)
                s += 'if (' + cond + condMutex + '){\n'
            else:
                s += 'if ' + cond + '{\n'
            self.__lineno += 1

            s += self._make_custom_indent(delta=addIndent)
            s += 'if (__VERIFIER_nondet_bool()) {%s%s = %s; %s = 2;} else' % (
                abs_common.namespace['threadpc'], funcID, currpc, self.__svar)


            s += self._make_custom_indent(delta=addIndent) + '{\n'
            self.__lineno += 1

            stmtlines = utils.countline(stmts)
            if typ.startswith('FuncCall'):
                self.logMapLine(self.__lineno + 1, self.__lineno +
                                stmtlines, nodes, typ=typ)
            elif typ == 'InlinedReturn':
                # One line for return value assignment
                self.logMapLine(self.__lineno + 1, self.__lineno +
                                1, nodes[0], typ='Assignment')
                # Another line for goto
                self.logMapLine(self.__lineno + 2, self.__lineno +
                                stmtlines, nodes[1], typ='Goto')
            elif typ == 'UnaryOp':
                self.logMapLine(self.__lineno + 1, self.__lineno +
                                1, nodes, typ='UnaryOp')
            elif typ == 'Assignment':
                self.logMapLine(self.__lineno + 1, self.__lineno +
                                1, nodes, typ='Assignment')
            elif typ == 'EmptyStatement':
                self.logMapLine(self.__lineno + 1, self.__lineno +
                                1, nodes, typ='EmptyStatement')
            elif typ == 'AtomicRegion':
                if len(nodes) > 0:
                    lastline = self.__lineno
                    nextline = lastline
                    for i in range(0, len(nodes)):
                        node = nodes[i][0]
                        extraline = nodes[i][1]
                        nextline = lastline + extraline
                        self.logMapLine(lastline + 1, nextline, node,
                                        typ=node.__class__.__name__)
                        lastline = nextline
            else:
                raise ModuleError('This statement is invalid to map line\n')

            s += stmts
            self.__lineno += stmtlines
            s += self._make_custom_indent(delta=addIndent) + '}}\n'
            self.__lineno += 1
            return s
        else:
            # fname = self.__threadNameByID[str(funcID)]
            hasMutex = False if len(mutexes) == 0 else True
            addIndent = len(self.__pc_stack) * 4
            s = self._make_custom_indent(delta=addIndent)
            cond = '(%s == 1)' % (self.__svar)
            if hasMutex:
                condMutex = ''
                for i in range(0, len(mutexes)):
                    condMutex += ' && (%s == %s)' % (mutexes[i], funcID)
                s += 'if (' + cond + condMutex + ')\n'
            else:
                s += 'if ' + cond + '\n'
            self.__lineno += 1

            s += self._make_custom_indent(delta=addIndent) + '{\n'
            self.__lineno += 1

            stmtlines = utils.countline(stmts)

            if typ.startswith('FuncCall'):
                self.logMapLine(self.__lineno + 1, self.__lineno +
                                stmtlines, nodes, typ=typ)
            elif typ == 'InlinedReturn':
                # One line for return value assignment
                self.logMapLine(self.__lineno + 1, self.__lineno +
                                1, nodes[0], typ='Assignment')
                # Another line for goto
                self.logMapLine(self.__lineno + 2, self.__lineno +
                                stmtlines, nodes[1], typ='Goto')
            elif typ == 'UnaryOp':
                self.logMapLine(self.__lineno + 1, self.__lineno +
                                1, nodes, typ='UnaryOp')
            elif typ == 'Assignment':
                self.logMapLine(self.__lineno + 1, self.__lineno +
                                1, nodes, typ='Assignment')
            elif typ == 'EmptyStatement':
                self.logMapLine(self.__lineno + 1, self.__lineno +
                                1, nodes, typ='EmptyStatement')
            elif typ == 'AtomicRegion':
                if len(nodes) > 0:
                    lastline = self.__lineno
                    nextline = lastline
                    for i in range(0, len(nodes)):
                        node = nodes[i][0]
                        extraline = nodes[i][1]
                        nextline = lastline + extraline
                        self.logMapLine(lastline + 1, nextline, node,
                                        typ=node.__class__.__name__)
                        lastline = nextline
            else:
                raise ModuleError('This statement is invalid to map line\n')

            s += stmts
            self.__lineno += stmtlines

            s += self._make_custom_indent(delta=addIndent) + '}\n'
            self.__lineno += 1
            return s

    def _generate_Exit_stmt(self, funcID, currpc, destpc, mutexes=[], typ='', nodes=None):
        # fname = self.__threadNameByID[str(funcID)]
        s = ''
        addIndent = len(self.__pc_stack) * 4
        hasMutex = False if len(mutexes) == 0 else True
        s = self._make_custom_indent(delta=addIndent)
        cond = '(%s == 1 || (%s == 0 && %s%s == %s))' % (
            self.__svar, self.__svar, abs_common.namespace['threadpc'], funcID, currpc)
        if hasMutex:
            condMutex = ''
            for i in range(0, len(mutexes)):
                condMutex += ' && (%s == %s)' % (mutexes[i], funcID)
            s += 'if (' + cond + condMutex + ')\n'
        else:
            s += 'if ' + cond + '\n'
        self.__lineno += 1

        s += self._make_custom_indent(delta=addIndent) + '{\n'
        self.__lineno += 1

        # Record line number
        self.logMapLine(self.__lineno + 1, self.__lineno + 2, nodes, typ=typ)

        s += self._make_custom_indent(delta=addIndent + 2) + '%s%s = %s;\n' % (
            abs_common.namespace['threadpc'], funcID, destpc)
        self.__lineno += 1

        s += self._make_custom_indent(delta=addIndent + 2) + '%s = 2;\n' % self.__svar
        self.__lineno += 1

        s += self._make_custom_indent(delta=addIndent) + '}\n'
        self.__lineno += 1
        return s

    def _generate_Goto_like_stmt(self, funcID, currpc, destpc, mutexes=[], typ='', nodes=None):
        # fname = self.__threadNameByID[str(funcID)]
        s = ''
        addIndent = len(self.__pc_stack) * 4
        hasMutex = False if len(mutexes) == 0 else True
        s = self._make_custom_indent(delta=addIndent)
        cond = '(%s == 1 || (%s == 0 && %s%s == %s))' % (
            self.__svar, self.__svar, abs_common.namespace['threadpc'], funcID, currpc)
        if hasMutex:
            condMutex = ''
            for i in range(0, len(mutexes)):
                condMutex += ' && (%s == %s)' % (mutexes[i], funcID)
            s += 'if (' + cond + condMutex + ')\n'
        else:
            s += 'if ' + cond + '\n'
        self.__lineno += 1

        s += self._make_custom_indent(delta=addIndent) + '{\n'
        self.__lineno += 1

        # Record line number
        self.logMapLine(self.__lineno + 1, self.__lineno + 2, nodes, typ=typ)

        s += self._make_custom_indent(delta=addIndent + 2) + '%s%s = %s;\n' % (
            abs_common.namespace['threadpc'], funcID, destpc)
        self.__lineno += 1

        # s += self._make_custom_indent(delta=addIndent+2) + 'return %s\n' % self.__threadIsVoid[fname]
        s += self._make_custom_indent(delta=addIndent + 2) + \
            'if(__VERIFIER_nondet_bool()) %s = 2; else %s = 0;\n' % (
                self.__svar, self.__svar)
        # s += self._make_custom_indent(delta=addIndent+2) + '%s = 0;\n' % self.__svar
        self.__lineno += 1

        s += self._make_custom_indent(delta=addIndent) + '}\n'
        self.__lineno += 1
        return s

    def _generate_Goto_stmt(self, funcID, currpc, destpc, mutexes=[], typ='', nodes=None):
        # fname = self.__threadNameByID[str(funcID)]
        s = ''
        addIndent = len(self.__pc_stack) * 4
        hasMutex = False if len(mutexes) == 0 else True
        s = self._make_custom_indent(delta=addIndent)
        cond = '(%s == 1)' % (self.__svar)
        if hasMutex:
            condMutex = ''
            for i in range(0, len(mutexes)):
                condMutex += ' && (%s == %s)' % (mutexes[i], funcID)
            s += 'if (' + cond + condMutex + ')\n'
        else:
            s += 'if ' + cond + '\n'
        self.__lineno += 1

        s += self._make_custom_indent(delta=addIndent) + '{\n'
        self.__lineno += 1

        s += self._make_custom_indent(delta=addIndent + 2) + 'goto %s;\n' % nodes.name

        s += self._make_custom_indent(delta=addIndent) + '}\n'
        self.__lineno += 1
        return s

    def _generate_GotoSpecial_stmt(self, funcID, currpc, destpc, mutexes=[], typ='', nodes=None):
        # fname = self.__threadNameByID[str(funcID)]
        s = ''
        addIndent = len(self.__pc_stack) * 4
        hasMutex = False if len(mutexes) == 0 else True
        s = self._make_custom_indent(delta=addIndent)
        # if (s == RESUME  && pc == L)  s = EXECUTE;
        s += 'if (%s == 0 && %s%s == %s) %s = 1;\n' % (
            self.__svar, abs_common.namespace['threadpc'], funcID, currpc, self.__svar)
        # if (s == EXECUTE )            if(*) { pc = L; s = SUSPEND;} else { statement; }
        s += self._make_custom_indent(delta=addIndent)
        cond = '(%s == 1)' % (self.__svar)
        if hasMutex:
            condMutex = ''
            for i in range(0, len(mutexes)):
                condMutex += ' && (%s == %s)' % (mutexes[i], funcID)
            s += 'if (' + cond + condMutex + ')\n'
        else:
            s += 'if ' + cond + '\n'
        self.__lineno += 1
        s += 'if (__VERIFIER_nondet_bool()) {%s%s = %s; %s = 2;} else\n' % (
            abs_common.namespace['threadpc'], funcID, currpc, self.__svar)

        s += self._make_custom_indent(delta=addIndent) + '{\n'
        self.__lineno += 1

        # Record line number
        self.logMapLine(self.__lineno + 1, self.__lineno + 2, nodes, typ=typ)

        s += self._make_custom_indent(delta=addIndent + 2) + 'goto %s;\n' % (nodes.name)
        self.__lineno += 1

        s += self._make_custom_indent(delta=addIndent) + '}\n'
        self.__lineno += 1
        return s

    # ---------------------------  END TEMPLATE ------------------------------
    def _make_custom_indent(self, delta=0):
        return (self.custom_indent + delta) * self.INDENT_SPACING

    # ---------------------------  NORMAL STMT -------------------------------
    def visit_FuncCall(self, n):
        # When this function call is in Atomic region or in Atomic function
        fref = self._parenthesize_unless_simple(n.name)
        args = self.visit(n.args)

        s = ''
        # Limitations: pthread function family here !!!!
        # __VERIFIER__ family
        if fref.startswith('__VERIFIER_nondet'):
            s = fref + '(' + args + ')'
        elif fref.startswith('__VERIFIER_atomic_cseq_'):
            s = fref.replace('__VERIFIER_atomic_cseq_',
                             '', 1) + '(' + args + ')'
        elif fref.startswith('__VERIFIER_atomic'):
            s = fref + '(' + args + ')'
        elif fref == '__VERIFIER_assume':
            s = fref + '(' + args + ')'
        elif fref == '__VERIFIER_assert':
            error = '__cseq_error()'
            s = 'if (!(%s)) %s' % (args, error)
            # s = 'if (!(%s)) %s = 1' % (args, self.__error_var)
        elif fref == '__VERIFIER_error':
            s = '__cseq_error()'
            # s = '%s' % self.__error_var
        # malloc and free
        elif fref == 'malloc':
            s = '%s(%s)' % (abs_common.namespace['malloc'], args)
        elif fref == 'free':
            s = '%s(%s)' % (abs_common.namespace['free'], args)
        # __cs_ family
        elif fref == '__cs_init_scalar':
            s = fref + '(' + args + ')'
        elif fref == '__cs_exit':   # This will not happen
            s = 'return 0'
        # non defined funcall
        elif fref == 'assume':
            s = '__VERIFIER_assume(%s)' % args
        elif fref == 'assert':
            # 判断是否CBMC后端
            if hasattr(self, '__backend'): 
                if self.__backend == 'cbmc':#or self.__backend == 'uautomizer': # zhangyuan
                    s = 'assert(%s)' % args
            elif self.__backend == 'uautomizer':
                    error = '__VERIFIER_error();'
                    s += self._make_custom_indent(delta=addIndent + 4) + \
                    'if (!(%s)) %s\n' % (args, error)
            else:
                error = '__cseq_error()'
                s = 'if (!(%s)) %s' % (args, error)
        # elif fref == 'assert':
        #     error = '__cseq_error()'
        #     s = 'if (!(%s)) %s' % (args, error)
        #     # s = 'if (!(%s)) %s = 1' % (args, self.__error_var)
        elif fref not in self.Parser.funcBody:  # Not defined functions
            s = fref + '(' + args + ')'
        else:
            s = fref + '(' + args + ')'
            # raise ModuleError('This function %s cannot be called here\n' % fref)
        # anthing else
        return s

    def visit_FuncDef(self, n):
        if (n.decl.name == '__VERIFIER_atomic_begin' or n.decl.name == '__VERIFIER_atomic_end'):
            return ''

        decl = self.visit(n.decl)

        if decl.startswith('__VERIFIER_atomic_cseq_'):  # Converting atomic functions
            decl = decl.replace('__VERIFIER_atomic_cseq_', '', 1)

        self.indent_level = 0
        body = self.visit(n.body)
        if n.param_decls:
            knrdecls = ';\n'.join(self.visit(p) for p in n.param_decls)
            return decl + '\n' + knrdecls + ';\n' + body + '\n'
        else:
            return decl + '\n' + body + '\n'

    def visit_Decl(self, n, no_type=False):
        # no_type is used when a Decl is part of a DeclList, where the type is
        # explicitly only for the first delaration in a list.
        #
        s = n.name if no_type else self._generate_decl(n)

        s = s.replace('__VERIFIER_atomic_cseq_', '', 1)

        if n.bitsize:
            s += ' : ' + self.visit(n.bitsize)
        if n.init:
            s += ' = ' + self._visit_expr(n.init)
        return s

    def visit_ArrayRef(self, n):
        arrref = self._parenthesize_unless_simple(n.name)
        subscript = self.visit(n.subscript)
        if subscript == '__cs_thread_index' and self.__currentGenerateFunct != '':
            subscript = 'THREAD_%s_INDEX' % self.__currentGenerateFunct
        s = arrref + '[' + subscript + ']'
        return s

    def _visit_expr(self, n):
        if isinstance(n, c_ast.InitList):
            return '{' + self.visit(n) + '}'
        elif isinstance(n, c_ast.ExprList):
            return '(' + self.visit(n) + ')'
        else:
            return self.visit(n)

    # -------------------------  NORMAL STMT ---------------------------------

    # -------------------------  LOG FILE FOR COUNTER EXAMPLE  ---------------
    def saveLogFile(self, filename):
        outfile = open(filename, "w")
        outfile.write(self.logoutput)
        outfile.close()

    def logMapLine(self, oldline, currline, node, typ=''):
        line = ''
        if oldline < currline:
            line = '%s-%s' % (oldline, currline)
        elif oldline == currline:
            line = '%s' % currline
        else:
            return

        coord = 'None'
        if node is not None and node.coord:
            coord = str(node.coord).replace(':', '')
        self.logoutput += '%s:%s:%s\n' % (line, coord, typ)

        if typ.startswith('Typedef'):
            # Count backward
            if oldline < currline and coord != 'None':
                diff = currline - oldline + 1
                coord = int(coord)
                for i in range(0, diff):
                    self.logoutput += '%s:%s:%s\n' % (
                        currline - i, coord - i, typ + '_decomposed')
        elif typ.startswith('Decl'):
            if oldline < currline and coord != 'None':
                diff = currline - oldline + 1
                coord = int(coord)
                for i in range(0, diff):
                    self.logoutput += '%s:%s:%s\n' % (
                        oldline + i, coord + i, typ + '_decomposed')
        elif typ == 'FuncDefAtomic' or typ == 'FuncDefPtr':
            if oldline < currline and coord != 'None':
                diff = currline - oldline + 1
                coord = int(coord)
                for i in range(0, diff):
                    self.logoutput += '%s:%s:%s\n' % (
                        oldline + i, coord + i, typ + '_decomposed')
        else:
            if oldline < currline and coord != 'None':
                diff = currline - oldline + 1
                coord = int(coord)
                for i in range(0, diff):
                    self.logoutput += '%s:%s:%s\n' % (oldline + i, coord, typ)

    # -------------------------  处理高优先级函数 --------------------------------- 
    def _generate_Exit_stmt_ISR(self, funcID, currpc, destpc, mutexes=[], typ='', nodes=None):
        # fname = self.__threadNameByID[str(funcID)]
        s = ''
        addIndent = len(self.__pc_stack) * 4
        hasMutex = False if len(mutexes) == 0 else True
        s += self._make_custom_indent(delta=addIndent)
        cond = '(%s == 1 || (%s == 0 && %s%s == %s))' % (
            self.__svar, self.__svar, abs_common.namespace['threadpc'], funcID, currpc)
        if hasMutex:
            condMutex = ''
            for i in range(0, len(mutexes)):
                condMutex += ' && (%s == %s)' % (mutexes[i], funcID)
            s += 'if (' + cond + condMutex + ')\n'
        else:
            s += 'if ' + cond + '\n'
        self.__lineno += 1

        s += self._make_custom_indent(delta=addIndent) + '{\n'
        self.__lineno += 1

        # Record line number
        self.logMapLine(self.__lineno + 1, self.__lineno + 2, nodes, typ=typ)

        s += self._make_custom_indent(delta=addIndent + 2) + '%s%s = %s;\n' % (
            abs_common.namespace['threadpc'], funcID, destpc)
        self.__lineno += 1

        s += self._make_custom_indent(delta=addIndent + 2) + '%s = 2;\n' % self.__svar
        self.__lineno += 1

        s += self._make_custom_indent(delta=addIndent) + '}\n'
        self.__lineno += 1
        return s
    
    def _generate_SingleStmt_ISR(self, funcID, currpc, stmts, mutexes=[], typ='', nodes=None, visible=True):
        """
        直接输出程序的原语句 stmts
        """
        # 直接返回语句 `stmts`，不做任何额外处理
        stmtlines = utils.countline(stmts)  # 计算语句的行数
        self.__lineno += stmtlines  # 更新行号

        # 日志映射，仅用于记录源代码行号到目标代码行号的映射
        if typ.startswith('FuncCall'):
            self.logMapLine(self.__lineno - stmtlines + 1, self.__lineno, nodes, typ=typ)
        elif typ == 'InlinedReturn':
            # 记录 return 和 goto 的日志
            self.logMapLine(self.__lineno - stmtlines + 1, self.__lineno - stmtlines + 1, nodes[0], typ='Assignment')
            self.logMapLine(self.__lineno - stmtlines + 2, self.__lineno, nodes[1], typ='Goto')
        elif typ in ['UnaryOp', 'Assignment', 'EmptyStatement']:
            self.logMapLine(self.__lineno - stmtlines + 1, self.__lineno - stmtlines + 1, nodes, typ=typ)
        elif typ == 'AtomicRegion':
            if len(nodes) > 0:
                lastline = self.__lineno - stmtlines
                nextline = lastline
                for i in range(len(nodes)):
                    node = nodes[i][0]
                    extraline = nodes[i][1]
                    nextline = lastline + extraline
                    self.logMapLine(lastline + 1, nextline, node, typ=node.__class__.__name__)
                    lastline = nextline
        else:
            # 如果 `typ` 是未知类型，抛出异常
            if typ:
                raise ModuleError('This statement is invalid to map line\n')

        # 直接返回原语句
        return stmts

    def generate_Else_ISR(self, fname, id, pc, funcID):
        addIndent = len(self.__pc_stack) * 4
        if len(self.__pc_stack) == 0:
            raise ModuleError("Else statement does not have if")
        if self.__pc_stack[-1][0] != 'Ifelse':
            raise ModuleError("Else statement does not have if again")
        s = self._make_custom_indent(delta=addIndent - 4) + 'else\n'
        midpc, endpc, cond = self.__pc_stack[-1][3], self.__pc_stack[-1][4], self.__pc_stack[-1][5]
        #  if (   (RESUME && pc > Li && pc < Lk)
        # || (EXECUTE))
        # s += 'if ((%s == 0 && %s%s <= %s) || (%s == 1))' % (
        #     self.__svar, abs_common.namespace['threadpc'], funcID, endpc,
        #     self.__svar)
        # self.__lineno += 1
        # No need to record line here
        return s

    def generate_While_ISR(self, fname, id, pc, funcID):
        """
        仅生成并返回 while 循环的原语句，不添加额外处理。
        """
        # 获取 while 循环的节点
        node = self.Parser.abs_functionScope[(fname, id)][2]
        cond = ''
        if node.cond:
            cond = self.visit(node.cond)  # 获取 while 条件部分
        if not cond:
            cond = '1'  # 如果条件为空，默认为 true

        # 与 generate_While 对齐：入栈后 OpenBracket/CloseBracket 才会输出真正的 { }
        self.__pc_stack.append(('While', pc))

        # 生成 while 循环语句
        s = self._make_custom_indent(delta=4)  # 不添加额外缩进
        s += '    while (%s)\n' % cond
        self.__lineno += 1  # 更新行号
        self.logMapLine(self.__lineno, self.__lineno, node, typ='While')  # 记录日志映射
        return s

    def generate_FuncCall_ISR(self, fname, id, pc, funcID):
        s = ''
        fref = self.Parser.abs_functionScope[(fname, id)][1]
        node = self.Parser.abs_functionScope[(fname, id)][2]
        args = self.visit(node.args)
        addIndent = len(self.__pc_stack) * 4  # Indentation
        realpc = pc[0]
        mutexes = self.Parser.abs_functionScope[(fname, id)][5]

        current_dir = os.path.dirname(os.path.abspath(__file__))
        json_file_path = os.path.join(current_dir, 'data.json')

        with open(json_file_path, 'r') as file:
            data = json.load(file)

        __cs_ISRIndex = {}
        __cs_ISRIndex = self.__thread_index.copy()
        # for key in data.keys():
        #     if key == "main_task":
        #         __cs_ISRIndex[key] = 0 
        #     else:
        #         # 获取键的最后一个字符并转为整数
        #         __cs_ISRIndex[key] = int(key[-1])

        '''
                __cs_ISRIndex = {
                    "main_task": 0,
                    "isr_1": 1,
                    "isr_2": 2
                }
        '''

        # 判断是否为特定函数调用
        if fref == 'disable_isr':

            s += self._make_custom_indent(delta=addIndent + 4) + '/*%s(%s);*/\n' % (fref, args)
            if not self.__ignore_masking:
                if args == '-1':  # 如果参数是 -1，禁用除当前函数外的所有线程
                    for i in __cs_ISRIndex.keys():
                        if i != self.__currentFun:  # 排除当前函数
                            # s += self._make_custom_indent(delta=addIndent + 4) + '__cs_disable_isr[%d] = 1;\n' % __cs_ISRIndex[i]
                            s += self._make_custom_indent(delta=addIndent + 4) + '__cs_disable_isr_%d = 1;\n' % __cs_ISRIndex[i]
                            self.__lineno += 1
                    # s += self._make_custom_indent(delta=addIndent + 4) + '__cs_disable_isr[0] = 1;\n'   # 禁用主线程
                else:
                    # 如果参数是线程编号，匹配 __cs_ISRIndex 的值
                    for i, idx in __cs_ISRIndex.items():
                        if str(idx) == args:  # 匹配线程编号
                            # s += self._make_custom_indent(delta=addIndent + 4) + '__cs_disable_isr[%d] = 1;\n' % idx
                            s += self._make_custom_indent(delta=addIndent + 4) + '__cs_disable_isr_%d = 1;\n' % idx
                            self.__lineno += 1
            s = self._generate_SingleStmt(funcID, realpc, s, mutexes=mutexes, typ='FuncCall_disable_isr', nodes=node, visible=True)

        elif fref == 'enable_isr':
            s += self._make_custom_indent(delta=addIndent + 4) + '/*%s(%s);*/\n' % (fref, args)
            if not self.__ignore_masking:
                if args == '-1':  # 如果参数是 -1，启用除当前函数外的所有线程
                    for i in __cs_ISRIndex.keys():
                        if i != self.__currentFun:  # 排除当前函数
                            # s += self._make_custom_indent(delta=addIndent + 4) + '__cs_disable_isr[%d] = 0;\n' % __cs_ISRIndex[i]
                            s += self._make_custom_indent(delta=addIndent + 4) + '__cs_disable_isr_%d = 0;\n' % __cs_ISRIndex[i]
                            self.__lineno += 1
                    # s += self._make_custom_indent(delta=addIndent + 4) + '__cs_disable_isr[0] = 0;\n'  # 启用主线程
                else:
                    # 如果参数是线程编号，匹配 __cs_ISRIndex 的值
                    for i, idx in __cs_ISRIndex.items():
                        if str(idx) == args:  # 匹配线程编号
                            # s += self._make_custom_indent(delta=addIndent + 4) + '__cs_disable_isr[%d] = 0;\n' % idx
                            s += self._make_custom_indent(delta=addIndent + 4) + '__cs_disable_isr_%d = 0;\n' % idx
                            self.__lineno += 1
            s = self._generate_SingleStmt(funcID, realpc, s, mutexes=mutexes, typ='FuncCall_enable_isr', nodes=node, visible=True)  
        # ------------------------------------------------------------------
        # PTHREAD EXPLAIN
        # pthread_create
        # pthread_join
        # pthread_exit
        # ------------------------------------------------------------------
        elif fref == 'pthread_exit':
            raise ModuleError(
                'pthread_exit statement exists in the translation\n')
        # ---------------------------------------------------------------
        # CONDITIONAL VARIABLE EXPLANATION
        # a conditional variable has these values
        # NO_SIGNAL (0): initialized value (or after this thread wake up
        #                       from pthread_cond_signal)
        # DESTROYED (-1): being destroyed
        # SIGNAL (1): being signaled by phread_cond_signal
        # BROADCAST (2): being broadcast by pthread_cond_broadcast
        # ---------------------------------------------------------------
        # __VERIFIER__ family
        elif fref == '__VERIFIER_assume':
            s += self._make_custom_indent(delta=addIndent + 4) + \
                '%s(%s);\n' % (fref, args)
            s = self._generate_SingleStmt_ISR(funcID, realpc, s, mutexes=mutexes,
                                          typ='FuncCall___VERIFIER_assume', nodes=node)

        elif fref == '__VERIFIER_assert':
            error = '__cseq_error();'
            s += self._make_custom_indent(delta=addIndent + 4) + \
                'if (!(%s)) %s\n' % (args, error)
            # s += self._make_custom_indent(delta=addIndent+4) + 'if (!(%s)) %s = 1;\n' % (args, self.__error_var)
            s = self._generate_SingleStmt_ISR(funcID, realpc, s, mutexes=mutexes,
                                          typ='FuncCall___VERIFIER_assert', nodes=node)

        elif fref == '__VERIFIER_error':
            error = '__cseq_error();'
            s += self._make_custom_indent(delta=addIndent + 4) + '%s\n' % error
            # s += self._make_custom_indent(delta=addIndent+4) + '%s = 1;\n' % self.__error_var
            s = self._generate_SingleStmt_ISR(funcID, realpc, s, mutexes=mutexes,
                                          typ='FuncCall___VERIFIER_error', nodes=node)

        elif fref.startswith('__VERIFIER_nondet'):
            s += self._make_custom_indent(delta=addIndent + 4) + \
                '%s(%s);\n' % (fref, args)
            s = self._generate_SingleStmt_ISR(funcID, realpc, s, mutexes=mutexes,
                                          typ='FuncCall_%s' % fref, nodes=node)

        elif fref.startswith('__VERIFIER_atomic'):
            fref = fref.replace('__VERIFIER_atomic_cseq_', '', 1)
            s += self._make_custom_indent(delta=addIndent + 4) + \
                '%s(%s);\n' % (fref, args)
            s = self._generate_SingleStmt_ISR(funcID, realpc, s, mutexes=mutexes,
                                          typ='FuncCall_%s' % fref, nodes=node)

        # malloc and free
        elif fref == 'malloc':
            s += self._make_custom_indent(delta=addIndent + 4) + '%s(%s);\n' % (
                abs_common.namespace['malloc'], args)
            s = self._generate_SingleStmt_ISR(funcID, realpc, s, mutexes=mutexes,
                                          typ='FuncCall_malloc', nodes=node)

        elif fref == 'free':
            s += self._make_custom_indent(delta=addIndent + 4) + \
                '%s(%s);\n' % (fref, args)
            s = self._generate_SingleStmt_ISR(funcID, realpc, s, mutexes=mutexes,
                                          typ='FuncCall_free', nodes=node)

        # __cs__ family
        elif fref == '__cs_exit':
            # This statement is treated as the return statement of thread
            # Assign destpc to the last statement
            destpc = self.Parser.abs_functionMaxPC[self.__currentGenerateFunct]
            s += self._generate_Exit_stmt_ISR(funcID, realpc, destpc, mutexes,
                                         typ='FuncCall___cs_exit', nodes=node)

        elif fref == '__cs_init_scalar':
            s += self._make_custom_indent(delta=addIndent + 4) + \
                '%s(%s);\n' % (fref, args)
            s = self._generate_SingleStmt_ISR(funcID, realpc, s, mutexes=mutexes,
                                          typ='FuncCall___cs_init_scalar', nodes=node)

        # non-defined funccall
        elif fref == 'assume':
            s += self._make_custom_indent(delta=addIndent + 4) + \
                '__VERIFIER_assume(%s);\n' % args
            s = self._generate_SingleStmt(funcID, realpc, s, mutexes=mutexes,
                                          typ='FuncCall_assume', nodes=node)

        elif fref == 'assert':
            # zhangyuan 如果验证后端是CBMC，不修改断言的格式，便于一次性查看多个断言的真假
            if self.__backend == 'cbmc':# or self.__backend == 'uautomizer':
                s += self._make_custom_indent(delta=addIndent + 4) + 'assert(%s);\n' % args
            elif self.__backend == 'uautomizer':
                    error = '__VERIFIER_error();'
                    s += self._make_custom_indent(delta=addIndent + 4) + \
                    'if (!(%s)) %s\n' % (args, error)
            else:
                error = '__cseq_error();'
                s += self._make_custom_indent(delta=addIndent + 4) + \
                    'if (!(%s)) %s\n' % (args, error)
            # s = self._generate_SingleStmt(funcID, realpc, s, mutexes=mutexes,
            #                             typ='FuncCall_assert', nodes=node)


        elif fref.startswith('nondet_uint'):
            s += self._make_custom_indent(delta=addIndent + 4) + \
                '__VERIFIER_nondet_uint();\n'
            s = self._generate_SingleStmt_ISR(funcID, realpc, s, mutexes=mutexes,
                                          typ='FuncCall_%s' % fref, nodes=node)

        elif fref.startswith('nondet'):
            s += self._make_custom_indent(delta=addIndent + 4) + \
                '__VERIFIER_nondet_int();\n'
            s = self._generate_SingleStmt_ISR(funcID, realpc, s, mutexes=mutexes,
                                          typ='FuncCall_%s' % fref, nodes=node)
        # Prevent false analysis
        elif fref == 'strcpy' and self.__backend in ('cpachecker', 'seahorn'):
            raise ModuleError('Unsupported type of function %s\n' % fref)
            sys.exit(1)

        elif fref not in self.Parser.funcBody:
            s += self._make_custom_indent(delta=addIndent + 4) + \
                '%s(%s);\n' % (fref, args)
            # s = self._generate_SingleStmt(funcID, realpc, s, mutexes=mutexes,
            #                               typ='FuncCall_%s' % fref, nodes=node)

        else:
            s += self._make_custom_indent(delta=addIndent + 4) + \
                '%s(%s);\n' % (fref, args)
            # s = self._generate_SingleStmt(funcID, realpc, s, mutexes=mutexes,
            #                               typ='FuncCall_%s' % fref, nodes=node)

            raise ModuleError(
                'Some function call: %s should not be here\n' % fref)
        return s
    
    def generate_If_ISR(self, fname, id, pc, funcID):
        node = self.Parser.abs_functionScope[(fname, id)][2]

        startpc = pc[0]
        midpc = pc[1]
        endpc = pc[2]
        # Put if to stack to know where the other statement goes
        addIndent = len(self.__pc_stack) * 4
        cond = ''
        if node.cond:
            cond = self.visit(node.cond)
        if not cond:
            cond = '1'

        if node.iffalse:
            self.__pc_stack.append(('Ifelse', pc, startpc, midpc, endpc, cond))
        else:
            self.__pc_stack.append(('If', pc))
            endpc = midpc

        # There will be no mutex checking in IF, each stmts inside must check
        # by its own
        # if (s == RESUME  && pc == L)  s = EXECUTE;
        s = self._make_custom_indent(delta=addIndent)

        s += self._make_custom_indent(delta=addIndent)
        # s += 'if ((%s == 0 && %s%s <= %s) || (%s == 1 && (%s)))\n' % (
        #     self.__svar, abs_common.namespace['threadpc'], funcID, midpc,
        #     self.__svar, cond)
        s += 'if (%s)\n' % (cond)
        # Log map line
        self.__lineno += 1
        if node.iffalse:
            self.logMapLine(self.__lineno, self.__lineno, node, typ='IfElse')
        else:
            self.logMapLine(self.__lineno, self.__lineno, node, typ='If')
        return s


    
    def generate_HighestPrioFunction(self, fref, funcID):
        """
        生成高优先级中断函数定义的代码
        根据 self.abs_functionScope 和 self.abs_functionMaxID 生成函数定义。
        对于函数调用类型的语句（FuncCall）进行额外处理，其他语句直接输出原始字符串。
        忽略 `FuncDef` 类型的语句，避免重复输出函数声明。
        """
        output = ''
        self.__currentGenerateFunct = fref

        # 函数声明
        output += self.generate_FuncDef(fref, 0, None, funcID)  # 函数定义起始部分
        output += '{\n'  # 添加函数体的起始大括号
        self.__lineno += 1

        # 遍历函数的每条语句
        for i in range(0, self.Parser.abs_functionMaxID[fref]):  # 通过最大语句编号遍历
            key = (fref, i)  # 获取语句的键
            stmtType = self.Parser.abs_functionScope[key][0]  # 语句类型
            stmtString = self.Parser.abs_functionScope[key][1]  # 语句字符串
            pc = self.Parser.abs_functionScope[key][4]  # 程序计数 (pcS, pcM, pcE)
            self.custom_indent = self.Parser.abs_functionScope[key][3]  # 缩进级别


            # 包装所有语句在条件结构中
            if i == 0:  # 特殊处理第一条语句
                output += self._make_custom_indent(delta=4)
                output += 'if (__cs_simulate == 0 && %s%s == 0) __cs_simulate = 1;\n' % (
                    abs_common.namespace['threadpc'], funcID)
                self.__lineno += 1

                output += self._make_custom_indent(delta=4)
                output += 'if (__cs_simulate == 1){\n'
                self.__lineno += 1

                output += self._make_custom_indent(delta=4)
                output += 'if (__VERIFIER_nondet_bool()) {%s%s = 0; __cs_simulate = 2;} else \n' % (
                    abs_common.namespace['threadpc'], funcID)
                self.__lineno += 1

            # 忽略 `FuncDef` 类型的语句，因为它对应的stmtString是空的
            if stmtType == 'FuncDef':
                continue

            # 对语句类型进行判断
            if stmtType == 'FuncCall':  # 如果是函数调用语句
                # # 如果是最后一条退出语句，则在这条语句前增加括号，与i==0时else后的括号组成一对
                if stmtString == '__cs_exit':
                    output += '        }}\n'
                output += self.generate_FuncCall_ISR(fref, i, pc, funcID)
                self.__lineno += 1
            elif stmtType == 'If':
                output += self._make_custom_indent(delta=4)
                output += self.generate_If_ISR(fref, i, pc, funcID)
            elif stmtType == 'Else':
                output += self.generate_Else_ISR(fref, i, pc, funcID)
            elif stmtType == 'While':
                output += self.generate_While_ISR(fref, i, pc, funcID)
            elif stmtType == 'OpenBracket':  # only {
                output += self.generate_OpenBracket(fref, i, pc, funcID)
            elif stmtType == 'CloseBracket': # only }
                output += self.generate_CloseBracket(fref, i, pc, funcID)
            else:
                if stmtString == 'FuncDef' or stmtString == 'If'  or stmtString == 'Else' or stmtString == 'Block' or stmtString == 'While':
                    continue
                # elif '__end_' in stmtString:
                #     output += self._make_custom_indent(delta=4)
                #     # 为while循环添加右括号}
                #     output += '    }\n'
                output += self._make_custom_indent(delta=8)
                output += stmtString + ';\n'
                self.__lineno += 1

        # output += '}\n'  # 添加函数体的结束大括号
        # self.__lineno += 1
        return output

    # ==================== Switch+goto optimization methods ====================
    
    def _generate_SwitchGoto_FunctionHeader(self, funcID, maxPC):
        """
        生成函数开头的 switch(pc) 分发头
        """
        output = ''
        pc_var = '%s%s' % (abs_common.namespace['threadpc'], funcID)
        
        output += '  switch (%s) {\n' % pc_var
        self.__lineno += 1
        
        # case 0: goto Li_0; (entry point)
        output += '    case 0: goto L%s_0;\n' % funcID
        self.__lineno += 1
        
        # case 1..maxPC-1: goto Li_k;
        for k in range(1, maxPC):
            output += '    case %d: goto L%s_%d;\n' % (k, funcID, k)
            self.__lineno += 1
        
        # case maxPC: goto Li_done;
        output += '    case %d: goto L%s_done;\n' % (maxPC, funcID)
        self.__lineno += 1
        
        # default: goto Li_done;
        output += '    default: goto L%s_done;\n' % funcID
        self.__lineno += 1
        
        output += '  }\n'
        self.__lineno += 1
        
        return output
    
    def _generate_can_preempt_function(self, funcID, fref):
        """
        生成 can_preempt_i() 函数
        对 main task: OR_{j=1..n}(__cs_disable_isr_j == 0)
        对 ISR i: OR_{j: p(j) > p(i)}(__cs_disable_isr_j == 0)
        最高优先级 ISR 返回 false
        """
        output = ''
        
        # 获取当前函数的优先级
        if fref == 'main' or fref == 'main_task':
            currentPriority = self.__threadDic.get('main_task', None)
        else:
            currentPriority = self.__threadDic.get(fref, None)
        
        if currentPriority is None:
            # 如果找不到优先级，默认返回 false（安全）
            return 'static inline _Bool __cs_can_preempt_%s(void) { return 0; }\n' % funcID
        
        HighestPrio = max(self.__threadDic.values())
        
        # 如果是最高优先级，返回 false（不可被抢占）
        if currentPriority == HighestPrio:
            output += 'static inline _Bool __cs_can_preempt_%s(void) { return 0; }\n' % funcID
            self.__lineno += 1
            return output
        
        # 生成抢占条件：OR_{j: p(j) > p(i)}(__cs_disable_isr_j == 0)
        output += 'static inline _Bool __cs_can_preempt_%s(void) {\n' % funcID
        self.__lineno += 1
        
        # 找到所有优先级高于当前函数的线程
        higherPriorityThreads = []
        for threadName, priority in self.__threadDic.items():
            if priority > currentPriority and threadName in self.__thread_index:
                higherPriorityThreads.append((threadName, self.__thread_index[threadName]))
        
        if len(higherPriorityThreads) == 0:
            output += '  return 0;\n'
        else:
            # 生成条件：(__cs_disable_isr_j == 0) || ...
            conditions = []
            for threadName, idx in higherPriorityThreads:
                conditions.append('(__cs_disable_isr_%d == 0)' % idx)
            
            if len(conditions) == 1:
                output += '  return %s;\n' % conditions[0]
            else:
                output += '  return %s;\n' % ' || '.join(conditions)
        
        output += '}\n'
        self.__lineno += 1
        
        return output
    
    def _generate_SwitchGoto_SingleStmt(self, funcID, currpc, nextpc, stmts, mutexes=[], typ='', nodes=None, visible=True):
        """
        生成 switch+goto 模式的单个语句 label 块
        格式：
        Li_k:
          if (can_preempt_i() && __VERIFIER_nondet_bool()) {
            __cs_pc_i = k;
            return;
          }
          /* 原程序语句 */
          __cs_pc_i = k+1;
          goto Li_k+1;
        """
        output = ''
        pc_var = '%s%s' % (abs_common.namespace['threadpc'], funcID)
        
        # Label: Li_k（只生成一次）
        label_key = (funcID, currpc)
        if not hasattr(self, '_generated_labels'):
            self._generated_labels = set()
        if label_key not in self._generated_labels:
            output += 'L%s_%d:\n' % (funcID, currpc)
            self.__lineno += 1
            self._generated_labels.add(label_key)
        
        # 抢占判断（在语句执行之前）
        output += '  if (__cs_can_preempt_%s() && __VERIFIER_nondet_bool()) {\n' % funcID
        self.__lineno += 1
        output += '    %s = %d;\n' % (pc_var, currpc)
        self.__lineno += 1
        output += '    return;\n'
        self.__lineno += 1
        output += '  }\n'
        self.__lineno += 1
        
        # 原程序语句
        if visible and stmts:
            stmtlines = utils.countline(stmts)
            output += stmts
            self.__lineno += stmtlines
            
            # 记录行号映射（如果有节点信息）
            if nodes:
                if typ.startswith('FuncCall'):
                    self.logMapLine(self.__lineno - stmtlines + 1, self.__lineno, nodes, typ=typ)
                elif typ == 'Assignment':
                    self.logMapLine(self.__lineno - stmtlines + 1, self.__lineno - stmtlines + 1, nodes, typ='Assignment')
        
        # 更新 pc 并跳转到下一个 label
        maxPC = self.Parser.abs_functionMaxPC.get(self.__currentGenerateFunct, 0)
        if nextpc >= maxPC:
            # 如果是最后一个语句，跳转到 done
            output += '  %s = %d;\n' % (pc_var, maxPC)
            self.__lineno += 1
            output += '  goto L%s_done;\n' % funcID
            self.__lineno += 1
        else:
            output += '  %s = %d;\n' % (pc_var, nextpc)
            self.__lineno += 1
            output += '  goto L%s_%d;\n' % (funcID, nextpc)
            self.__lineno += 1
        
        return output
    
    def _generate_SwitchGoto_Function(self, fref, funcID):
        """
        生成完整的 switch+goto 模式的函数
        """
        output = ''
        self.__currentGenerateFunct = fref
        self.__currentFun = fref  # 设置当前函数名，用于 disable/enable_isr 处理
        
        maxPC = self.Parser.abs_functionMaxPC.get(fref, 0)
        if maxPC == 0:
            # 如果没有语句，返回空函数
            output += self.generate_FuncDef(fref, 0, None, funcID)
            output += '{\n'
            self.__lineno += 1
            output += '  return;\n'
            self.__lineno += 1
            output += '}\n'
            self.__lineno += 1
            return output
        
        # 生成 can_preempt 函数（在函数定义之前）
        output += self._generate_can_preempt_function(funcID, fref)
        output += '\n'
        
        # 生成函数签名
        output += self.generate_FuncDef(fref, 0, None, funcID)
        output += '{\n'
        self.__lineno += 1
        
        # 生成 switch header
        output += self._generate_SwitchGoto_FunctionHeader(funcID, maxPC)
        output += '\n'
        
        # 初始化已生成 label 的集合（每个函数独立）
        self._generated_labels = set()
        
        # 跟踪当前打开的控制流块（用于正确处理 else 和 CloseBracket）
        self._open_blocks = []  # [(startpc, endpc, type, has_else)]  type: 'If', 'While'
        
        # 构建控制流块的范围映射（用于判断语句是否在块内）
        block_ranges = {}  # {startpc: (endpc, type, has_else)}  type: 'If', 'While'
        for i in range(0, self.Parser.abs_functionMaxID[fref]):
            key = (fref, i)
            stmtType = self.Parser.abs_functionScope[key][0]
            pc = self.Parser.abs_functionScope[key][4]
            if stmtType == 'If':
                node = self.Parser.abs_functionScope[key][2] if len(self.Parser.abs_functionScope[key]) > 2 else None
                startpc = pc[0] if isinstance(pc, tuple) else pc
                endpc = pc[2] if isinstance(pc, tuple) and len(pc) >= 3 else pc[1] if isinstance(pc, tuple) and len(pc) >= 2 else startpc + 1
                has_else = node.iffalse if node and hasattr(node, 'iffalse') else False
                block_ranges[startpc] = (endpc, 'If', has_else)
            elif stmtType == 'While':
                startpc = pc[0] if isinstance(pc, tuple) else pc
                endpc = pc[2] if isinstance(pc, tuple) and len(pc) >= 3 else startpc + 1
                block_ranges[startpc] = (endpc, 'While', False)
        
        # 遍历所有语句，生成 label 块
        for i in range(0, self.Parser.abs_functionMaxID[fref]):
            key = (fref, i)
            stmtType = self.Parser.abs_functionScope[key][0]
            stmtString = self.Parser.abs_functionScope[key][1]
            pc = self.Parser.abs_functionScope[key][4]
            self.custom_indent = self.Parser.abs_functionScope[key][3]
            
            # 跳过 FuncDef（已经在前面生成）
            if stmtType == 'FuncDef':
                continue
            
            currpc = pc[0] if isinstance(pc, tuple) else pc
            # 跳过无效的 PC 值（如 -1）
            if currpc < 0:
                continue
            
            # 默认 nextpc 是 currpc + 1，除非是控制流语句
            nextpc = currpc + 1
            
            # 检查当前语句是否在某个控制流块内（但不是块的起始语句）
            is_inside_block = False
            is_block_start_stmt = False
            # 只有当 stmtType 是 If 或 While 时，currpc == block_start 才表示这是控制流语句本身
            if stmtType in ['If', 'While']:
                for block_start, (block_end, block_type, has_else) in block_ranges.items():
                    if currpc == block_start:
                        is_block_start_stmt = True
                        break
            # 对于其他语句类型，如果 currpc 在块范围内，则视为块内语句
            if not is_block_start_stmt:
                for block_start, (block_end, block_type, has_else) in block_ranges.items():
                    if block_start <= currpc <= block_end:
                        is_inside_block = True
                        break
            
            # 跟踪已生成的 label，避免重复
            if not hasattr(self, '_generated_labels'):
                self._generated_labels = set()
            label_key = (funcID, currpc)
            
            # 处理不同类型的语句
            if stmtType == 'Assignment':
                node = self.Parser.abs_functionScope[key][2]
                stmts = self.visit(node)
                # 如果语句在块内，不生成 label，直接生成语句
                if is_inside_block:
                    output += '  ' + stmts + ';\n'
                    self.__lineno += 1
                else:
                    output += self._generate_SwitchGoto_SingleStmt(
                        funcID, currpc, nextpc, '  ' + stmts + ';\n', 
                        mutexes=self.Parser.abs_functionScope[key][5],
                        typ='Assignment', nodes=node)
            elif stmtType == 'FuncCall':
                # 对于函数调用，生成语句内容
                fref_call = self.Parser.abs_functionScope[key][1]
                node = self.Parser.abs_functionScope[key][2]
                args = self.visit(node.args) if hasattr(node, 'args') and node.args else ''
                
                # 生成函数调用语句
                stmt_content = ''
                if fref_call == 'disable_isr':
                    # 生成 disable_isr 逻辑
                    stmt_content += '  /*disable_isr(%s);*/\n' % args
                    current_dir = os.path.dirname(os.path.abspath(__file__))
                    json_file_path = os.path.join(current_dir, 'data.json')
                    with open(json_file_path, 'r') as file:
                        data = json.load(file)
                    __cs_ISRIndex = self.__thread_index.copy()
                    
                    if not self.__ignore_masking:
                        if args == '-1':
                            for i in __cs_ISRIndex.keys():
                                if i != fref:
                                    stmt_content += '  __cs_disable_isr_%d = 1;\n' % __cs_ISRIndex[i]
                        else:
                            for i, idx in __cs_ISRIndex.items():
                                if str(idx) == args:
                                    stmt_content += '  __cs_disable_isr_%d = 1;\n' % idx
                elif fref_call == 'enable_isr':
                    # 生成 enable_isr 逻辑
                    stmt_content += '  /*enable_isr(%s);*/\n' % args
                    current_dir = os.path.dirname(os.path.abspath(__file__))
                    json_file_path = os.path.join(current_dir, 'data.json')
                    with open(json_file_path, 'r') as file:
                        data = json.load(file)
                    __cs_ISRIndex = self.__thread_index.copy()
                    
                    if not self.__ignore_masking:
                        if args == '-1':
                            for i in __cs_ISRIndex.keys():
                                if i != fref:
                                    stmt_content += '  __cs_disable_isr_%d = 0;\n' % __cs_ISRIndex[i]
                        else:
                            for i, idx in __cs_ISRIndex.items():
                                if str(idx) == args:
                                    stmt_content += '  __cs_disable_isr_%d = 0;\n' % idx
                else:
                    # 普通函数调用
                    stmt_content = '  %s(%s);\n' % (fref_call, args)
                
                # 如果语句在块内，不生成 label，直接生成语句
                if is_inside_block:
                    output += stmt_content
                    self.__lineno += utils.countline(stmt_content)
                else:
                    output += self._generate_SwitchGoto_SingleStmt(
                        funcID, currpc, nextpc, stmt_content,
                        mutexes=self.Parser.abs_functionScope[key][5],
                        typ='FuncCall_' + fref_call if fref_call in ['disable_isr', 'enable_isr'] else 'FuncCall',
                        nodes=node)
            elif stmtType in ['If', 'While', 'Else']:
                # 控制流语句在 switch+goto 模式下需要特殊处理（不包含 __cs_simulate 逻辑）
                if stmtType == 'If':
                    node = self.Parser.abs_functionScope[key][2]
                    startpc = pc[0] if isinstance(pc, tuple) else pc
                    midpc = pc[1] if isinstance(pc, tuple) and len(pc) >= 2 else startpc + 1
                    endpc = pc[2] if isinstance(pc, tuple) and len(pc) >= 3 else midpc
                    
                    # 获取条件表达式
                    cond = ''
                    if node.cond:
                        cond = self.visit(node.cond)
                    if not cond:
                        cond = '1'
                    
                    # 生成 label 和抢占检查（只生成一次）
                    if label_key not in self._generated_labels:
                        output += 'L%s_%d:\n' % (funcID, startpc)
                        self.__lineno += 1
                        self._generated_labels.add(label_key)
                    output += '  if (__cs_can_preempt_%s() && __VERIFIER_nondet_bool()) {\n' % funcID
                    self.__lineno += 1
                    output += '    %s%s = %d;\n' % (abs_common.namespace['threadpc'], funcID, startpc)
                    self.__lineno += 1
                    output += '    return;\n'
                    self.__lineno += 1
                    output += '  }\n'
                    self.__lineno += 1
                    
                    # 生成简化的 if 语句（不包含 __cs_simulate）
                    output += '  if (%s) {\n' % cond
                    self.__lineno += 1
                    if node.iffalse:
                        self.logMapLine(self.__lineno, self.__lineno, node, typ='IfElse')
                        # 记录打开的 if 块（有 else）
                        self._open_blocks.append((startpc, endpc, 'If', True))
                    else:
                        self.logMapLine(self.__lineno, self.__lineno, node, typ='If')
                        # 记录打开的 if 块（无 else）
                        self._open_blocks.append((startpc, endpc, 'If', False))
                    
                    # 计算下一个 PC
                    nextpc = endpc + 1 if endpc > 0 else startpc + 1
                    # 注意：if 语句内部的代码会在后续迭代中生成，这里只生成 if 头部
                    # 不需要在这里跳转，因为后续语句会自然执行
                    
                elif stmtType == 'While':
                    node = self.Parser.abs_functionScope[key][2]
                    startpc = pc[0] if isinstance(pc, tuple) else pc
                    endpc = pc[2] if isinstance(pc, tuple) and len(pc) >= 3 else startpc + 1
                    
                    # 获取条件表达式
                    cond = ''
                    if node.cond:
                        cond = self.visit(node.cond)
                    if not cond:
                        cond = '1'
                    
                    # 生成 label 和抢占检查（只生成一次）
                    if label_key not in self._generated_labels:
                        output += 'L%s_%d:\n' % (funcID, startpc)
                        self.__lineno += 1
                        self._generated_labels.add(label_key)
                    output += '  if (__cs_can_preempt_%s() && __VERIFIER_nondet_bool()) {\n' % funcID
                    self.__lineno += 1
                    output += '    %s%s = %d;\n' % (abs_common.namespace['threadpc'], funcID, startpc)
                    self.__lineno += 1
                    output += '    return;\n'
                    self.__lineno += 1
                    output += '  }\n'
                    self.__lineno += 1
                    
                    # 生成简化的 while 语句（不包含 __cs_simulate）
                    output += '  while (%s) {\n' % cond
                    self.__lineno += 1
                    self.logMapLine(self.__lineno, self.__lineno, node, typ='While')
                    # 记录打开的 while 块
                    self._open_blocks.append((startpc, endpc, 'While', False))
                    
                    # 计算下一个 PC（while 循环结束后）
                    nextpc = endpc + 1 if endpc > 0 else startpc + 1
                    # 注意：while 循环内部的代码会在后续迭代中生成
                    
                elif stmtType == 'Else':
                    # 在 switch+goto 模式下，else 需要先关闭 if 分支，然后开始 else 分支
                    # 检查是否有打开的 if 块需要关闭
                    if len(self._open_blocks) > 0:
                        block_start, block_end, block_type, has_else = self._open_blocks[-1]
                        # 只处理最内层的 if 块（栈顶的块）
                        if block_type == 'If' and has_else:
                            # 检查当前 PC 是否对应这个 if 块的 else
                            # 获取 if 语句的 PC 信息
                            if_key = None
                            for j in range(0, self.Parser.abs_functionMaxID[fref]):
                                check_key = (fref, j)
                                if self.Parser.abs_functionScope[check_key][0] == 'If':
                                    check_pc = self.Parser.abs_functionScope[check_key][4]
                                    check_startpc = check_pc[0] if isinstance(check_pc, tuple) else check_pc
                                    if check_startpc == block_start:
                                        if_key = check_key
                                        break
                            
                            if if_key:
                                if_pc = self.Parser.abs_functionScope[if_key][4]
                                midpc = if_pc[1] if isinstance(if_pc, tuple) and len(if_pc) >= 2 else block_end
                                # 检查当前 PC 是否在 else 分支的范围内
                                if currpc >= midpc and currpc <= block_end:
                                    # 关闭 if 分支，开始 else 分支
                                    output += '  } else {\n'
                                    self.__lineno += 1
                                    # 更新打开的块标记：标记 else 分支已开始（将 has_else 设为 False，表示 else 已处理）
                                    self._open_blocks[-1] = (block_start, block_end, block_type, False)  # 标记 else 已处理
                                else:
                                    # 当前 PC 不在 else 分支范围内，可能是嵌套的 else，跳过
                                    pass
                            else:
                                # 找不到对应的 if 语句，按默认处理
                                output += '  } else {\n'
                                self.__lineno += 1
                                self._open_blocks[-1] = (block_start, block_end, block_type, False)
                        else:
                            # 不是 if 块或没有 else，跳过
                            pass
                    # 注意：else 块内的代码会在后续迭代中生成
                elif stmtType == 'CloseBracket':
                    # 在 switch+goto 模式下，CloseBracket 用于关闭 if/while 块
                    # 检查是否有打开的块需要关闭
                    if len(self._open_blocks) > 0:
                        block_start, block_end, block_type, has_else = self._open_blocks[-1]
                        # 检查当前 PC 是否是块的结束
                        # 对于有 else 的 if 块，CloseBracket 应该关闭 if 分支，但不生成 }（等待 Else 语句生成 } else {）
                        # 对于没有 else 的 if 块或 while 块，CloseBracket 应该关闭整个块
                        if block_type == 'If' and has_else:
                            # 有 else 的 if 块：检查是否是 if 分支的结束（midpc）
                            # 获取 if 语句的 PC 信息
                            if_key = None
                            for j in range(0, self.Parser.abs_functionMaxID[fref]):
                                check_key = (fref, j)
                                if self.Parser.abs_functionScope[check_key][0] == 'If':
                                    check_pc = self.Parser.abs_functionScope[check_key][4]
                                    check_startpc = check_pc[0] if isinstance(check_pc, tuple) else check_pc
                                    if check_startpc == block_start:
                                        if_key = check_key
                                        break
                            
                            if if_key:
                                if_pc = self.Parser.abs_functionScope[if_key][4]
                                midpc = if_pc[1] if isinstance(if_pc, tuple) and len(if_pc) >= 2 else block_end
                                # 如果当前 PC 是 if 分支的结束，不在这里生成 }，等待 Else 语句
                                if currpc == midpc or (currpc > midpc and currpc < block_end):
                                    # 这是 if 分支内的 CloseBracket，不生成 }，等待 Else
                                    pass
                                elif currpc == block_end or currpc >= block_end:
                                    # 这是整个 if-else 块的结束，关闭块
                                    output += '  }\n'
                                    self.__lineno += 1
                                    self._open_blocks.pop()
                                    if nextpc < maxPC:
                                        output += '  %s%s = %d;\n' % (abs_common.namespace['threadpc'], funcID, nextpc)
                                        self.__lineno += 1
                                        output += '  goto L%s_%d;\n' % (funcID, nextpc)
                                        self.__lineno += 1
                            else:
                                # 找不到对应的 if 语句，按无 else 处理
                                if currpc == block_end or currpc >= block_end:
                                    output += '  }\n'
                                    self.__lineno += 1
                                    self._open_blocks.pop()
                                    if nextpc < maxPC:
                                        output += '  %s%s = %d;\n' % (abs_common.namespace['threadpc'], funcID, nextpc)
                                        self.__lineno += 1
                                        output += '  goto L%s_%d;\n' % (funcID, nextpc)
                                        self.__lineno += 1
                        elif currpc == block_end or (block_type == 'If' and not has_else and currpc >= block_end) or (block_type == 'While' and currpc >= block_end):
                            # 关闭块（无 else 的 if 或 while）
                            output += '  }\n'
                            self.__lineno += 1
                            # 移除已关闭的块
                            self._open_blocks.pop()
                            # 如果块结束后还有语句，需要跳转到下一个 PC
                            if nextpc < maxPC:
                                output += '  %s%s = %d;\n' % (abs_common.namespace['threadpc'], funcID, nextpc)
                                self.__lineno += 1
                                output += '  goto L%s_%d;\n' % (funcID, nextpc)
                                self.__lineno += 1
                    continue
            elif stmtType == 'Goto':
                node = self.Parser.abs_functionScope[key][2]
                label = node.name
                labelpc = self.Parser.abs_functionLabels[fref][label]
                # 只生成一次 label
                if label_key not in self._generated_labels:
                    output += 'L%s_%d:\n' % (funcID, currpc)
                    self.__lineno += 1
                    self._generated_labels.add(label_key)
                output += '  if (__cs_can_preempt_%s() && __VERIFIER_nondet_bool()) {\n' % funcID
                self.__lineno += 1
                output += '    %s%s = %d;\n' % (abs_common.namespace['threadpc'], funcID, currpc)
                self.__lineno += 1
                output += '    return;\n'
                self.__lineno += 1
                output += '  }\n'
                self.__lineno += 1
                output += '  goto L%s_%d;\n' % (funcID, labelpc)
                self.__lineno += 1
            elif stmtType == 'Label':
                node = self.Parser.abs_functionScope[key][2]
                # 只生成一次 label
                if label_key not in self._generated_labels:
                    output += 'L%s_%d:\n' % (funcID, currpc)
                    self.__lineno += 1
                    self._generated_labels.add(label_key)
                if nextpc < maxPC:
                    output += '  goto L%s_%d;\n' % (funcID, nextpc)
                    self.__lineno += 1
            elif stmtType == 'OpenBracket':
                # 在 switch+goto 模式下，OpenBracket 通常已经在 if/while 中处理了
                continue
            elif stmtType == 'UnaryOp':
                node = self.Parser.abs_functionScope[key][2]
                stmts = self.visit(node)
                # 如果语句在块内，不生成 label，直接生成语句
                if is_inside_block:
                    output += '  ' + stmts + ';\n'
                    self.__lineno += 1
                else:
                    output += self._generate_SwitchGoto_SingleStmt(
                        funcID, currpc, nextpc, '  ' + stmts + ';\n',
                        mutexes=self.Parser.abs_functionScope[key][5],
                        typ='UnaryOp', nodes=node)
            else:
                if stmtString and stmtString not in ['FuncDef', 'If', 'Else', 'Block', 'While', '']:
                    # 如果语句在块内，不生成 label，直接生成语句
                    if is_inside_block:
                        output += '  ' + stmtString + ';\n'
                        self.__lineno += 1
                    else:
                        output += self._generate_SwitchGoto_SingleStmt(
                            funcID, currpc, nextpc, '  ' + stmtString + ';\n',
                            mutexes=self.Parser.abs_functionScope[key][5],
                            typ=stmtType, nodes=self.Parser.abs_functionScope[key][2] if len(self.Parser.abs_functionScope[key]) > 2 else None)
        
        # 生成 done label
        output += 'L%s_done:\n' % funcID
        self.__lineno += 1
        output += '  return;\n'
        self.__lineno += 1
        
        output += '}\n'
        self.__lineno += 1
        
        return output

