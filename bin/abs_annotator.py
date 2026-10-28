# # -*- coding: utf-8 -*-
# ------------------------------------------------------------------------------
# NAME = abs_annotator.py
# -----------------------------------------------------------------------------
# VERSION = 0.2
# -----------------------------------------------------------------------------
# Description:
#   This module is based on parser.py of Lazy-cseq
#       Provide an convinent structure for translation
#         Structure of input after preprocessing
#           + Global variable declaration
#           + Function prototypes
#           + Thread functions
#           + __VERIFIER_atomic functions
#           + main function
#
#         So the order of collection is
#           + global var declarations (including init) Nodes
#               + collect for global varname
#           + function prototype (collecting for reprinting only)
#           + __VERIFIER_atomic functions (reprinting)
#           + In a thread function
#               - start pc
#               - local var declaration
#                  -->  no pc but put it into sequence
#               - typedef declaration
#                  --> no pc but put it into sequence
#               - assignment statement
#                  --> (pcstart, pcmid, pcend, node)
#               - compound statement
#                   if (cond) {  --> start PC
#                       block;  --> end PC
#                   }
#                   if (cond) {  --> start PC
#                       block;  --> mid PC
#                   } else {
#                       block;  --> end PC
#                   }
#                   while (cond) { --> start PC
#                       block;  --> end PC
#                   }
#                  --> (pcstart, pcmid, pcend, node)
#               - statement with label
#                   treat as normal statement (no problem)
#               - goto statement
#                   go thorough label in this function to find out statement PC
#               - continue statement
#                   to the PC of loop statement
#               - break statement
#                   to the PC after loop statement
#               - return statement
#                   repeat that PC
#               - no return statement
#                   additional PC
#               - funcall to __VERIFIER_atomic_X
#                   treat as one normal statement (exact copy)
#               - funcall to function pointer (limitation)
#                   still treat as normal statement --> need improvement
#               - funcall to malloc and free
#                   treat as normal statement
#               - funcall to __cs_init_scalar
#                   treat as a normal satement
#               - __VERIFIER_ class
#                   specific handling and treat as a normal statement
#               - __VERIFIER_atomic_begin ... __VERIFIER_atomic_end
#                   treat as one statement from
#                       __VERIFIER_atomic_begin --> __VERIFIER_atomic_end
#
#               And finally:
#               - collecting thread name -> for pc_index
#               - collecting program counter (largest onr) -> for pc
#
#           Data structure:
#               Global scope contains:
#                   global vars
#                   __VERIFIER_atomic function
#               Each thread functions:
#                   declaration stmt (no PC)
#                   stmt (with PC)
#
#   Prerequisites:
#       - Only __VERIFIER_atomic and thread functions
#       - No switch, for loop in input
#       - No function call in condition
#       - There should not be assignment or unary operation in condition
#
#   Limitations:
#       - Handling assignment inside
#
#
# TODO:
#       - Fix context switch point (only consider visible statement)
#       - Provide the structure of storing all the values
#           related to a given variable (for identifying concrete var)
#
# Changelog:
#
# -----------------------------------------------------------------------------

from pycparser import c_ast, c_generator, c_parser
import common
import abs_common
import re


class ABS_Annotator(c_generator.CGenerator):
    __output = ''
    __stack = []

    __abs_parsing_thread_func = False           # parsing thread function
    __abs_parsing_atomic_region = []
    __abs_atomic_region_stack = []                     # Append ID of that __VERIFIER_atomic_begin
    __abs_statement_level = 0
    __abs_current_id = 0                        # ID of each statement
    __abs_current_pc = 0                        # pc of each statement (visible statement)
    __abs_parsing_pending_stack = []                  # Stack to store pending parsing on current node
    __abs_inlined_return_str = ''
    __abs_inlined_return_stack = []
    __abs_assignment_id = -1
    __abs_assignment_pc = -1
    __abs_mutex_stack = []

    __globalMemoryAccessed = False

    def reset(self):
        # ------------------------------------------
        # ANNOTATOR TRUC Table START
        # ------------------------------------------
        # Storing all statements of global scope
        # Containing :  - typedef stmt
        #               - global variable (with init)
        #               - function prototypes
        #               - __VERIFIER_atomic function
        self.abs_globalScope = []

        # Storing all functions along with their statement
        # Structure : Note that stmt_id =/= pcstart
        # (function_name, stmt_id) ->
        #       [0]   : stmt type (name)
        #       [1]   : stmt in string
        #       [2]   : ast node of statement (can be multiple nodes)
        #       [3]   : indentation level
        #       [4]   : (pcS, pcM (for ifelse), pcE)
        #       [5]   : list of mutexes associated
        #       [6]   : visibility
        self.abs_functionScope = {}

        # (function_name) -> ('pc', label)
        self.abs_functionLabels = {}  # Storing label and pc matching for each function
        self.abs_functionMaxID = {}  # Storing max id of each function
        self.abs_functionMaxPC = {}  # Storing max pc of each function

        self.abs_threadID = {}  # Storing thread function with their id
        self.abs_threadID_stack = []  # Storing non-main thread function with their id

        self.abs_thread_id = 1
        self.abs_threadNameToF = {}  # Storing thread name with their id
        self.abs_fhasreturn = {}     # function has return stmt

        # For inlining purpose
        self.abs_atomicLikeFunc = {}

        self.abs_varValues = {}  # Storing values of a variable following pairwise (func, varname)
        self.abs_skip_typedef = False  # Skip typedef
        self.abs_symbols = {}

        # For thread local variable
        self.abs_hasThreadLocal = False

        # ------------------------------------------
        # ANNOTATOR Table END
        # ------------------------------------------

        # # # # NEW PARSING TABLE START # # #
        self.symbols = []  # _all_ the symbols (function names, variables, struct names, .... )
        self.blocks = {}
        self.__symbolsstack = []
        self.__symbolscount = 0
        # # # # NEW PARSING TABLE END # # #
        self.currentFunct = ''  # name of the function which definition is being parsed ('' = none)
        self.funcName = ['']  # all functions names (consider '' to be a special function to model global scope)
        self.threadName = []  # all threads names (i.e. functions used as argument to pthread_create())
        # all functions whose id are used in anything else than just function calls (e.g. they are used as pointer-to-functions..)
        self.funcReferenced = []
        self.funcCallCnt = {}  # number of function calls for each function name
        self.threadCallCnt = {}  # number of times a function is used to generate a thread (by calling pthread_create())
        self.lastStmt = ''  # last statement generated
        self.lastFuncStmt = {}  # last statement for each function
        self.funcBlock = {}  # the entire function definition (= declaration+body) for each function
        self.funcBlockIn = {}  # input parameters for each function
        self.funcBlockOut = {}  # return value for each function
        self.funcBody = {}  # function body-only
        self.funcDecl = {}  # function declarations, only for functions declared and defined in different statements, or not defined at all.
        self.funcASTNode = {}  # the AST node for the function definitions, by function
        self.funcIsVoid = {}
        self.funcLabels = {}  # set of labels defined in a given function, by function
        self.currentVarAssign = ''  # name of the current variable used as lvalue in an assignment statement
        self.currentStruct = ''  # note! this
        self.structName = []
        self.mainParametersDecl = ''  # parameters of the main() function to be transferred to thread 0.

        """ The following are indexed either using
            (struct, variable)  for struct fields, or
            (function, variable) local variables and function parameters, or
            ('', variable) for global variables.
            See _generate_decl(self, n) below for details.
        """
        self.varNames = {}  # names of all the variables (global, local, parameters) + variables in structs
        self.varNames[''] = []  # initialisation for global var names ('' is the global scope)
        self.varType = {}  # int, char, ....
        self.varTypeUnExpanded = {}  # same as .varType, but with unexpanded typedefs
        self.varArity = {}  # 0 for scalar, k for k-dimensional arrays
        self.varSize = {}  # [] for scalar, [n1,...,k] for k-dimensional arrays
        self.varKind = {}  # g, l, p, s
        self.varMallocd = {}  # used only for pointers
        self.varID = {}  # unique IDs for variables, as they are found while parsing, starting with 0
        self.varCount = 0  #
        self.extraGlovalVarCount = 0  # Count global variables introduced in the above data structures, but not from original input.
        self.varInitExpr = {}  # set when a declared variable has an init expression
        self.varPtrToFunct = {}

        # Handling of typedefs.
        # We put in the first variable below the last part of a typedef statement,
        # and in the second variable its correspondent expansion.
        #
        # Anonymous typedefs are no exception, as they are assigned an internal name to be used as described.
        #
        self.typedefs = []  # contains last the part of a typedef stmt,
        # e.g. typedef struct struct_name {.... } last_part;
        self.typedefExpansion = {}  # e.g. typedefs['field'] = struct { int a; int b; ... }
        # from the original typedef statement
        # Statements start with indentation of self.indent_level spaces, using
        # the _make_indent method
        #
        self.indent_level = 0  # to keep track of the depth of the block {}
        self.INDENT_SPACING = ' '  # ....

        # = True while parsing the subtree for a function declaration
        self.parsingFuncDecl = False

        # = True while parsing the subtree for a struct (or union) declaration
        self.parsingStruct = False

        self.parsingUnion = False

        # set to True while parsing void functions
        self.parsingVoidFunction = False

        # set to True while parsing typedef blocks
        self.parsingTypedef = False

        # coords for each node in the AST
        # (when the input is loaded from a string rather than a file,
        #  the coords only contain the line number)
        self.currentInputCoord = ''
        self.currentInputLineNumber = -1
        self.currentOutputLineNumber = -1
        self.nodecoords = {}
        self.lines = []

    # =====================================================================================


    def get_thread_index(self):
        """
        Build a mapping: function_name -> thread_index, where main is always 0,
        and all other functions (isr_xxx) are 1, 2, ... (order can be sorted or abs_threadID)
        Note: If sorting is applied, the suffixes of the functions in the detected program need to be different numbers, and these numbers correspond one-to-one with the interrupt mask numbers (disable_isr(n)).
        """

        mapping = {}
        # 先保证 main=0
        if 'main' in self.abs_threadID:
            mapping['main'] = 0

        # 提取所有非 main 的名字
        isr_names = [name for name in self.abs_threadID if name != 'main']
        # 按 isr_数字排序
        def isr_key(name):
            m = re.search(r'isr_(\d+)$', name)
            return int(m.group(1)) if m else float('inf')  # 非 isr_ 结尾排最后

        isr_names_sorted = sorted(isr_names, key=isr_key)
        cnt = 1
        for name in isr_names_sorted:
            mapping[name] = cnt
            cnt += 1
        return mapping

    def visit_Decl(self, n, no_type=False):
        # Decl happen when
        #   actual declaration: type decl, array decl, function decl, decl list, pointer decl,
        #   struct or union

        if n.name is not None:
            self.__symbolsstack.append(n.name)
            self.symbols.append((self.__symbolscount, n.name))
            self.__symbolscount += 1

            self.abs_symbols[n.name] = True

        # no_type is used when a Decl is part of a DeclList, where the type is
        # explicitly only for the first delaration in a list.
        s = n.name if no_type else self._generate_decl(n)
        if n.bitsize:
            s += ' : ' + self.visit(n.bitsize)
        self.__abs_parsing_pending_stack.append('Init')
        if n.init:
            if isinstance(n.init, c_ast.InitList):
                s += ' = {' + self.visit(n.init) + '}'
            elif isinstance(n.init, c_ast.ExprList):
                s += ' = (' + self.visit(n.init) + ')'
            else:
                s += ' = ' + self.visit(n.init)
        if (len(self.__abs_parsing_pending_stack) > 0 and
                self.__abs_parsing_pending_stack[-1] == 'Init'):
            self.__abs_parsing_pending_stack.pop()

        if 'FuncDecl' in str(n.type) and self.currentFunct == '':
            self.funcDecl[n.name] = s

        if n.name is not None and len(self.__symbolsstack) > 0:
            self.__symbolsstack.pop()

        # Build annotator node
        if (self.currentFunct == '' and
                not self.parsingStruct and
                not self.parsingUnion and
                not self.parsingTypedef and
                not self.parsingFuncDecl):
            # In global scope so add it in
            s = s.replace('pthread_t', common.changeID['pthread_t'], 1)
            s = s.replace('pthread_mutex_t', common.changeID['pthread_mutex_t'], 1)
            s = s.replace('pthread_cond_t', common.changeID['pthread_cond_t'], 1)
            # print 'Collecting Decl %s and %s' % (n.name, s)
            self._add_global_node(n.__class__.__name__,
                                  string=s, node=n, indent=self.indent_level)
        elif (not self.currentFunct.startswith('__VERIFIER_atomic') and
                not self.parsingStruct and
                not self.parsingUnion and
                not self.parsingTypedef and
                not self.parsingFuncDecl):
            # In function scope
            s = s.replace('pthread_t', common.changeID['pthread_t'], 1)
            s = s.replace('pthread_mutex_t', common.changeID['pthread_mutex_t'], 1)
            s = s.replace('pthread_cond_t', common.changeID['pthread_cond_t'], 1)
            self._add_normal_node('Decl',
                                  string=s, node=n, indent=self.indent_level,
                                  pcS=-1, pcM=-1, pcE=-1)
            self.__abs_current_id += 1

        # Thread local variable collection
        if (n.name is not None and n.name.startswith(abs_common.namespace['threadlocal'])):
            self.abs_hasThreadLocal = True

        return s

    def visit_Typedef(self, n):
        s = ''
        if n.storage:
            s += ' '.join(n.storage) + ' '
        self.parsingTypedef = True
        typestring = self._generate_type(n.type)
        self.parsingTypedef = False
        if typestring.startswith("struct "):
            leftPart = typestring[:typestring.find('{')]
            if leftPart.endswith(' '):
                leftPart = leftPart[:-1]
            if leftPart.endswith('\n'):
                leftPart = leftPart[:-1]
            if leftPart.endswith(' '):
                leftPart = leftPart[:-1]

            rightPart = typestring[typestring.rfind('} ') + 2:]
            self.typedefs.append(rightPart)
            self.typedefExpansion[rightPart] = leftPart
        s += typestring

        # ABS collecting
        if n.name == '_____STARTSTRIPPINGFROMHERE_____':
            self.abs_skip_typedef = True
        # Build annotator
        if (self.currentFunct == '' and
                not self.abs_skip_typedef and
                not self.parsingTypedef):
            # In global scope so add it in
            # s = s.replace('pthread_t', common.changeID['pthread_t'], 1)
            # s = s.replace('pthread_mutex_t', common.changeID['pthread_mutex_t'], 1)
            # s = s.replace('pthread_cond_t', common.changeID['pthread_cond_t'], 1)
            # print 'Collecting typedef %s' % n.name
            self._add_global_node(n.__class__.__name__,
                                  string=s, node=n, indent=self.indent_level)
        elif (not self.currentFunct.startswith('__VERIFIER_atomic') and
              not self.parsingTypedef):
            # s = s.replace('pthread_t', common.changeID['pthread_t'], 1)
            # s = s.replace('pthread_mutex_t', common.changeID['pthread_mutex_t'], 1)
            # s = s.replace('pthread_cond_t', common.changeID['pthread_cond_t'], 1)
            self._add_normal_node('Typedef',
                                  string=s, node=n, indent=self.indent_level,
                                  pcS=-1, pcM=-1, pcE=-1)
            self.__abs_current_id += 1

        # ABS collecting
        if n.name == '_____STOPSTRIPPINGFROMHERE_____':
            self.abs_skip_typedef = False

        if n.name == '__fsid_t':
            self.abs_symbols[n.name] = True

        return s

    def visit_Struct(self, n):
        if n.name not in self.structName:
            self.currentStruct = n.name
            self.structName.append(n.name)
            self.varNames[self.currentStruct] = []
        oldParsingStruct = self.parsingStruct
        self.parsingStruct = True
        s = self._generate_struct_union(n, 'struct')
        self.parsingStruct = oldParsingStruct

        return s

    def visit_Union(self, n):
        oldParsingStruct = self.parsingStruct
        self.parsingStruct = True
        oldParsingUnion = self.parsingUnion
        self.parsingUnion = True
        s = self._generate_struct_union(n, 'union')
        self.parsingStruct = oldParsingStruct
        self.parsingUnion = oldParsingUnion

        return s



    def visit_FuncDef(self, n):

        if n.decl.name not in self.funcCallCnt:
            self.funcCallCnt[n.decl.name] = 0

        self.currentFunct = n.decl.name

        # ABS collecting thread ID (for pc)
        if n.decl.name == 'main':
            self.abs_threadID[n.decl.name] = self.abs_thread_id
            self.abs_thread_id += 1

        # if "isr" in fref.lower() or "interrupt" in fref.lower():    # add by zy
        if ("isr" in n.decl.name.lower() or "interrupt" in n.decl.name.lower()) and "disable" not in n.decl.name.lower() and "enable" not in n.decl.name.lower():
            self.abs_threadID[n.decl.name] = self.abs_thread_id
            self.abs_threadID_stack.append(n.decl.name) # store all ISR names
            self.abs_thread_id += 1
 

        # ABS If this function is an __VERIFIER_atomic
        if self.currentFunct.startswith('__VERIFIER_atomic'):
            self._add_global_node(n.__class__.__name__, string=None, node=n, indent=self.indent_level)
            self.__abs_parsing_thread_func = False
        else:
            self.__abs_parsing_thread_func = True

        if n.decl.name not in self.funcName:
            self.funcName.append(n.decl.name)
            self.varNames[self.currentFunct] = []
            self.funcLabels[self.currentFunct] = []

        self.funcASTNode[n.decl.name] = n

        # Function declaration
        self.__abs_parsing_pending_stack.append('FuncDecl')
        decl = self.visit(n.decl)
        self.__abs_parsing_pending_stack.pop()

        if decl.startswith("void") and not decl.startswith("void *"):
            self.parsingVoidFunction = True
            self.funcIsVoid[self.currentFunct] = True
        else:
            self.parsingVoidFunction = False
            self.funcIsVoid[self.currentFunct] = False

        # ABS prepare before collecting
        if self.__abs_parsing_thread_func:
            self.__abs_atomic_region_stack = []
            self.__abs_current_id = 0
            self.__abs_current_pc = 0
            self.__abs_parsing_pending_stack = []
            self.abs_functionLabels[self.currentFunct] = {}
            # Add this function decl to collected data
            self._add_normal_node('FuncDef',
                                  string=decl, node=n, indent=self.indent_level,
                                  pcS=-1, pcM=-1, pcE=-1, customID=-1)
            self.__abs_current_id += 1

        # ABS parsing pending
        self.__abs_parsing_pending_stack.append(n.__class__.__name__)

        # Function body
        body = self.visit(n.body)
        funcBlock = decl + '\n' + body + '\n'

        # ABS Collecting id
        self.abs_functionMaxID[self.currentFunct] = self.__abs_current_id
        # visible pc of each statement in thread
        self.abs_functionMaxPC[self.currentFunct] = self.__abs_current_pc - 1

        # Store all the function block
        self.funcBlock[self.currentFunct] = funcBlock
        self.funcBody[self.currentFunct] = body

        # Store the return type of the function
        returnType = decl[:decl.find(self.currentFunct + '(')]
        returnType = returnType[:-1] if returnType.endswith(' ') else returnType
        self.funcBlockOut[self.currentFunct] = returnType

        # Store the function input parameter list
        self.funcBlockIn[self.currentFunct] = decl[decl.find(self.currentFunct + '(') + len(
            self.currentFunct) + 1:decl.rfind(')')]
        self.lastFuncStmt[self.currentFunct] = self.lastStmt
        self.currentFunct = ''
        self.__abs_parsing_pending_stack.pop()
        return funcBlock

    def visit_FuncCall(self, n):
        fref = self._parenthesize_unless_simple(n.name)
        self.__abs_parsing_pending_stack.append('FuncCall')
        args = self.visit(n.args)
        self.__abs_parsing_pending_stack.pop()

        # When a thread is created, extract its function name
        # based on the 3rd parameter in the pthread_create() call:
        # pthread_create(&id, NULL, fname, &arg);
        #                            ^^^

        if (fref == 'pthread_create' or
                    fref == common.changeID['pthread_create']):
            fName = self.visit(n.args.exprs[2])
            fName = fName[1:] if fName.startswith('&') else fName
            threadName = args[:args.find(',')]
            threadName = threadName.replace('&', '')
            if fName not in self.threadCallCnt:
                self.threadName.append(fName)
                self.threadCallCnt[fName] = 1
            else:
                self.threadCallCnt[fName] += 1
            # ABS collecting thread id
            self.abs_threadID[fName] = self.abs_thread_id
            self.abs_threadID_stack.append(fName)
            self.abs_threadNameToF[threadName] = fName
            self.abs_thread_id += 1

        # Counts function calls
        if fref not in self.funcCallCnt:
            self.funcCallCnt[fref] = 0
        else:
            self.funcCallCnt[fref] += 1

        s = fref + '(' + args + ')'

        retType = ''
        if fref in self.funcBlockOut:
            retType = self.funcBlockOut[fref]

            # ABS If this is a call to __VERIFIER_atomic_begin
        if (self.currentFunct != '' and fref == '__VERIFIER_atomic_begin'):
            self.__abs_parsing_atomic_region.append(self.__abs_statement_level)
            self.__abs_atomic_region_stack.append([])  # Initialize for this atomic to collect
            # pc and id won't be increased
        # ABS If this is a call to __VERIFIER_atomic_end
        elif (self.currentFunct != '' and fref == '__VERIFIER_atomic_end'):
            self.__abs_parsing_atomic_region.pop()
            # All stack of node will be insert to this id
            self._add_normal_node('AtomicRegion',
                                  string=None, node=self.__abs_atomic_region_stack[-1],
                                  indent=self.indent_level,
                                  pcS=self.__abs_current_pc, pcM=-1, pcE=-1,
                                  customID=-1, mutexes=self.__abs_mutex_stack,
                                  visible=True)
            self.__abs_current_id += 1
            self.__abs_current_pc += 1
        # If this is a call to normal function (atomic, __VERIFIER__ class, nondet, POSIX thread)
        elif self.currentFunct != '':
            # TODO: this needs proper implementation since these functions
            # can be called by a non-atomic region
            # ABS remember function in Atomic region (begin --> end)
            if (len(self.__abs_parsing_atomic_region) > 0 and
                    not fref.startswith('__VERIFIER_atomic')):
                self.abs_atomicLikeFunc[fref] = True

            # ABS If this is a function called in __VERIFIER_atomic function
            if (self.currentFunct.startswith('__VERIFIER_atomic') and
                    not fref.startswith('__VERIFIER_') and
                    not fref.startswith('pthread_') and
                    not fref.startswith('nondet') and
                    fref != 'malloc' and
                    fref != 'free' and
                    fref != 'assume' and
                    fref != 'assert' and
                    fref != '__cs_init_scalar' and
                    fref != '__cs_exit'):
                self.abs_atomicLikeFunc[fref] = True

            # This call is to void function
            if ((retType != '' and retType.startswith("void") and not retType.startswith("void *")) or
                    (len(self.__abs_parsing_pending_stack) > 0 and
                        (self.__abs_parsing_pending_stack[-1] != 'Assignment' and
                            self.__abs_parsing_pending_stack[-1] != 'IfCond' and
                            self.__abs_parsing_pending_stack[-1] != 'WhileCond' and
                            self.__abs_parsing_pending_stack[-1] != 'Init'))):
                # Collecting this node
                if len(self.__abs_parsing_atomic_region) > 0:                               # This belong to a atomic region
                    if self.__abs_parsing_atomic_region[-1] == self.__abs_statement_level:  # This belong to a atomic region
                        self.__abs_atomic_region_stack[-1].append(n)
                else:
                    # consider any function call as visible statemen
                    self._add_normal_node('FuncCall',
                                          string=fref, node=n, indent=self.indent_level,
                                          pcS=self.__abs_current_pc, pcM=-1, pcE=-1,
                                          customID=-1, mutexes=self.__abs_mutex_stack,
                                          visible=True)
                    self.__abs_current_id += 1
                    self.__abs_current_pc += 1
                    # ABS pthread family here
                    if fref == 'pthread_cond_wait':
                        self.__abs_current_pc += 1

            # Mutexes stuff here
            if fref == 'pthread_mutex_lock':
                mutex_name = args
                if mutex_name.startswith('&'):
                    mutex_name = mutex_name.replace('&', '', 1)
                else:
                    mutex_name = '*' + mutex_name
                self.__abs_mutex_stack.append(mutex_name)
            elif fref == 'pthread_mutex_unlock':
                if len(self.__abs_mutex_stack) > 0:
                    self.__abs_mutex_stack.pop()

        return s

    def visit_Compound(self, n):
        compoundName = ''
        key = (self.currentFunct, self.__abs_current_id - 1)
        if key in self.abs_functionScope:
            compoundName = self.abs_functionScope[key][0]
        if compoundName not in ('FuncDef', 'While', 'If', 'Else'):
            compoundName = 'Block'              # custom block

        # Not in atomic function
        if self.__abs_parsing_thread_func:
            if (len(self.__abs_parsing_atomic_region) > 0 and compoundName == 'Block'):
                # This belong to an atomic region
                if self.__abs_parsing_atomic_region[-1] == self.__abs_statement_level:
                    # This belong to a atomic region
                    self.__abs_atomic_region_stack[-1].append(n)

        s = self._make_indent() + '{\n'
        # ABS collect data
        if (self.__abs_parsing_thread_func and
                len(self.__abs_parsing_atomic_region) == 0):
            # Determine kind of parent of this compound stmt
            self._add_normal_node('OpenBracket',
                                  string=compoundName, node=None, indent=self.indent_level,
                                  pcS=self.__abs_current_pc - 1, pcM=-1, pcE=-1)
            self.__abs_current_id += 1

        self.indent_level += 2
        self.__abs_statement_level += 1  # increasing level of the statement
        if n.block_items:
            for stmt in n.block_items:
                newStmt = self._getCurrentCoords(stmt) + self._generate_stmt(stmt)
                s += newStmt
                self.lastStmt = newStmt
        self.__abs_statement_level -= 1  # increasing level of the statement
        self.indent_level -= 2
        s += self._make_indent() + '}\n'

        # ABS collect data
        if (self.__abs_parsing_thread_func and
                len(self.__abs_parsing_atomic_region) == 0):
            self._add_normal_node('CloseBracket',
                                  string=compoundName, node=None, indent=self.indent_level,
                                  pcS=self.__abs_current_pc - 1, pcM=-1, pcE=-1)
            self.__abs_current_id += 1
        return s

    def visit_Label(self, n):
        # ABS If this is inside atomic
        if self.__abs_parsing_thread_func:
            self.abs_functionLabels[self.currentFunct][n.name] = self.__abs_current_pc
            if len(self.__abs_parsing_atomic_region) > 0:
                if self.__abs_parsing_atomic_region[-1] == self.__abs_statement_level:  # This belong to a atomic region
                    self.__abs_atomic_region_stack[-1].append(n)
            else:
                s = n.name + ':\n'
                self._add_normal_node('Label',
                                      string=s, node=n, indent=self.indent_level,
                                      pcS=self.__abs_current_pc - 1, pcM=-1, pcE=-1)
                self.__abs_current_id += 1

        self.funcLabels[self.currentFunct].append(n.name)

        if type(n.stmt) == c_ast.EmptyStatement:
            n.stmt.coord = n.coord

        return n.name + ':\n' + self._generate_stmt(n.stmt)

    def visit_UnaryOp(self, n):
        oldGlobalMemoryAccessed = self.__globalMemoryAccessed
        self.__globalMemoryAccessed = False
        operand = self._parenthesize_unless_simple(n.expr)
        globalAccess = self.__globalMemoryAccessed
        self.__globalMemoryAccessed = oldGlobalMemoryAccessed
        s = ''
        if n.op == 'p++':
            s = '%s++' % operand
        elif n.op == 'p--':
            s = '%s--' % operand
        elif n.op == 'sizeof':
            s = 'sizeof(%s)' % self.visit(n.expr)
        else:
            s = '%s%s' % (n.op, operand)

        if (n.op == '++' or n.op == 'p++' or n.op == '--' or n.op == 'p--'):
            if self.currentFunct != '' and self.__abs_parsing_thread_func:
                if (len(self.__abs_parsing_pending_stack) > 0 and
                        self.__abs_parsing_pending_stack[-1] != 'Assignment' and
                        self.__abs_parsing_pending_stack[-1] != 'FuncCall'):
                    if len(self.__abs_parsing_atomic_region) > 0:
                        if self.__abs_parsing_atomic_region[-1] == self.__abs_statement_level:  # This belong to a atomic region
                            self.__abs_atomic_region_stack[-1].append(n)
                    else:
                        if globalAccess or self.__abs_current_pc == 0:   # visible statement or the first stmt
                            self._add_normal_node('UnaryOp',
                                                  string=s, node=n, indent=self.indent_level,
                                                  pcS=self.__abs_current_pc, pcM=-1, pcE=-1,
                                                  customID=-1, mutexes=self.__abs_mutex_stack,
                                                  visible=True)
                            self.__abs_current_pc += 1
                        else:
                            self._add_normal_node('UnaryOp',
                                                  string=s, node=n, indent=self.indent_level,
                                                  pcS=self.__abs_current_pc - 1, pcM=-1, pcE=-1,
                                                  customID=-1, mutexes=self.__abs_mutex_stack)
                        # Anyway, increase the id
                        self.__abs_current_id += 1
        return s

    def visit_EmptyStatement(self, n):
        # ABS collect this node
        if self.currentFunct != '' and self.__abs_parsing_thread_func:
            if len(self.__abs_parsing_atomic_region) > 0:
                if self.__abs_parsing_atomic_region[-1] == self.__abs_statement_level:  # This belong to a atomic region
                    self.__abs_atomic_region_stack[-1].append(n)
            else:
                self._add_normal_node('EmptyStatement',
                                      string=';', node=n, indent=self.indent_level,
                                      pcS=self.__abs_current_pc - 1, pcM=-1, pcE=-1,
                                      customID=-1, mutexes=self.__abs_mutex_stack)
                self.__abs_current_id += 1
        return ';'

    def visit_Return(self, n):
        if self.currentFunct != '':
            self.abs_fhasreturn[self.currentFunct] = True

        s = 'return'
        if n.expr:
            s += ' ' + self.visit(n.expr)
        return s + ';'

    def visit_If(self, n):
        current_id = -1
        startPC = self.__abs_current_pc
        belongAtomic = False
        # ABS collect this node
        if self.currentFunct != '' and self.__abs_parsing_thread_func:
            if len(self.__abs_parsing_atomic_region) > 0:
                if self.__abs_parsing_atomic_region[-1] == self.__abs_statement_level:  # This belong to a atomic region
                    self.__abs_atomic_region_stack[-1].append(n)
                belongAtomic = True
            else:
                current_id = self.__abs_current_id
                # ABS add first to hold for this place
                self._add_normal_node('If',
                                      string=None, node=None, indent=self.indent_level,
                                      pcS=startPC, pcM=-1, pcE=-1,
                                      customID=-1, mutexes=[],
                                      visible=True)
                self.__abs_current_id += 1
                self.__abs_current_pc += 1

        s = 'if ('
        if n.cond:
            self.__abs_parsing_pending_stack.append('IfCond')
            s += self.visit(n.cond)
            self.__abs_parsing_pending_stack.pop()
        s += ')\n'
        self.__abs_parsing_pending_stack.append('IfTrue')
        self.__abs_statement_level += 1
        s += self._generate_stmt(n.iftrue, add_indent=True)
        self.__abs_statement_level -= 1
        self.__abs_parsing_pending_stack.pop()
        # pc
        midPC = self.__abs_current_pc - 1
        endPC = -1
        if n.iffalse:  # else
            s += self._make_indent() + 'else\n'
            self.__abs_parsing_pending_stack.append('IfFalse')

            if not belongAtomic:
                self._add_normal_node('Else',
                                      string='else', node=None, indent=self.indent_level,
                                      pcS=midPC, pcM=-1, pcE=-1)
                self.__abs_current_id += 1

            self.__abs_statement_level += 1
            s += self._generate_stmt(n.iffalse, add_indent=True)
            self.__abs_statement_level -= 1
            self.__abs_parsing_pending_stack.pop()
            endPC = self.__abs_current_pc - 1

        if not belongAtomic:
            self._add_normal_node('If',
                                  string=None, node=n, indent=self.indent_level,
                                  pcS=startPC, pcM=midPC, pcE=endPC,
                                  customID=current_id, mutexes=self.__abs_mutex_stack)
        return s

    def visit_While(self, n):
        current_id = -1
        startPC = self.__abs_current_pc
        belongAtomic = False

        # ABS collect this node
        if self.currentFunct != '' and self.__abs_parsing_thread_func:
            if len(self.__abs_parsing_atomic_region) > 0:
                if self.__abs_parsing_atomic_region[-1] == self.__abs_statement_level:  # This belong to a atomic region
                    self.__abs_atomic_region_stack[-1].append(n)
                belongAtomic = True
            else:
                current_id = self.__abs_current_id
                self._add_normal_node('While',
                                      string=None, node=None, indent=self.indent_level,
                                      pcS=startPC, pcM=-1, pcE=-1,
                                      customID=-1, mutexes=[],
                                      visible=True)
                self.__abs_current_id += 1
                self.__abs_current_pc += 1

        self.__abs_parsing_pending_stack.append(n.__class__.__name__)
        s = 'while ('
        if n.cond:
            self.__abs_parsing_pending_stack.append('WhileCond')
            s += self.visit(n.cond)
            self.__abs_parsing_pending_stack.pop()
        s += ')\n'
        self.__abs_statement_level += 1
        s += self._generate_stmt(n.stmt, add_indent=True)
        self.__abs_statement_level -= 1
        self.__abs_parsing_pending_stack.pop()
        endPC = self.__abs_current_pc - 1

        if not belongAtomic:
            self._add_normal_node('While',
                                  string=None, node=n, indent=self.indent_level,
                                  pcS=startPC, pcM=-1, pcE=endPC,
                                  customID=current_id, mutexes=self.__abs_mutex_stack)

        return s

    def visit_Break(self, n):
        if self.currentFunct != '' and self.__abs_parsing_thread_func:
            if len(self.__abs_parsing_atomic_region) > 0:
                if self.__abs_parsing_atomic_region[-1] == self.__abs_statement_level:  # This belong to a atomic region
                    self.__abs_atomic_region_stack[-1].append(n)
            else:
                self._add_normal_node('Break',
                                      string='break;', node=n, indent=self.indent_level,
                                      pcS=self.__abs_current_pc - 1, pcM=-1, pcE=-1,
                                      customID=-1, mutexes=self.__abs_mutex_stack)
                self.__abs_current_id += 1
        return 'break;'

    def visit_Continue(self, n):
        if self.currentFunct != '' and self.__abs_parsing_thread_func:
            if len(self.__abs_parsing_atomic_region) > 0:
                if self.__abs_parsing_atomic_region[-1] == self.__abs_statement_level:  # This belong to a atomic region
                    self.__abs_atomic_region_stack[-1].append(n)
            else:
                self._add_normal_node('Continue',
                                      string='continue;', node=n, indent=self.indent_level,
                                      pcS=self.__abs_current_pc - 1, pcM=-1, pcE=-1,
                                      customID=-1, mutexes=self.__abs_mutex_stack)
                self.__abs_current_id += 1
        return 'continue;'

    def visit_Assignment(self, n):
        self.__abs_parsing_pending_stack.append(n.__class__.__name__)
        oldGlobalMemoryAccessed = self.__globalMemoryAccessed
        self.__globalMemoryAccessed = False
        rvalue = self._parenthesize_if(
            n.rvalue,
            lambda n: isinstance(n, c_ast.Assignment))
        self.__abs_parsing_pending_stack.pop()
        lvalue = self.visit(n.lvalue)
        globalAccess = self.__globalMemoryAccessed
        self.__globalMemoryAccessed = oldGlobalMemoryAccessed
        s = '%s %s %s' % (lvalue, n.op, rvalue)

        # Ad hoc for init scalar
        if rvalue.startswith('__cs_init_scalar'):
            globalAccess = False

        if type(n.rvalue) == c_ast.FuncCall:
            nop = 'assignCall'
        else:
            nop = n.op
        if lvalue not in self.abs_varValues:
            self.abs_varValues[lvalue] = []
        self.abs_varValues[lvalue].append((nop, rvalue))

        # ABS Mind for the return of inlined function
        if lvalue.startswith('__retval__'):  # Possibility
            self.__abs_inlined_return_str = lvalue.replace('__retval__', '', 1)
            self.__abs_inlined_return_stack.append([])
            self.__abs_inlined_return_stack[-1].append(n)
            self.__abs_assignment_id = self.__abs_current_id
            self.__abs_assignment_pc = self.__abs_current_pc

        # ABS collect this node
        if self.currentFunct != '' and self.__abs_parsing_thread_func:
            if len(self.__abs_parsing_atomic_region) > 0:
                if self.__abs_parsing_atomic_region[-1] == self.__abs_statement_level:  # This belong to a atomic region
                    self.__abs_atomic_region_stack[-1].append(n)
            else:
                if globalAccess or self.__abs_current_pc == 0:
                    self._add_normal_node('Assignment',
                                          string=s, node=n, indent=self.indent_level,
                                          pcS=self.__abs_current_pc, pcM=-1, pcE=-1,
                                          customID=-1, mutexes=self.__abs_mutex_stack,
                                          visible=True)
                    self.__abs_current_pc += 1
                else:
                    self._add_normal_node('Assignment',
                                          string=s, node=n, indent=self.indent_level,
                                          pcS=self.__abs_current_pc - 1, pcM=-1, pcE=-1,
                                          customID=-1, mutexes=self.__abs_mutex_stack)
                # Anyway, increase the id
                self.__abs_current_id += 1
        return s

    def visit_Goto(self, n):
        s = 'goto ' + n.name + ';'
        # ABS collect this node
        if self.currentFunct != '' and self.__abs_parsing_thread_func:      # Parsing thread function
            if len(self.__abs_parsing_atomic_region) > 0:
                if self.__abs_parsing_atomic_region[-1] == self.__abs_statement_level:  # This belong to a atomic region
                    self.__abs_atomic_region_stack[-1].append(n)
            else:
                '''  OLD '''
                # if (n.name.startswith('__exit__') and
                #         self.__abs_inlined_return_str != '' and
                #         self.__abs_assignment_id != -1 and
                #         self.__abs_assignment_pc != -1 and
                #         self.__abs_inlined_return_str == n.name.replace('__exit__', '', 1)):
                #     self.__abs_inlined_return_stack[-1].append(n)
                #     self._add_normal_node('InlinedReturn',
                #                           string=None, node=self.__abs_inlined_return_stack[-1], indent=self.indent_level,
                #                           pcS=self.__abs_assignment_pc, pcM=-1, pcE=-10,
                #                           customID=self.__abs_assignment_id, mutexes=self.__`abs_mutex_stack)
                #     # Reset
                #     self.__abs_inlined_return_str = ''
                #     self.__abs_inlined_return_stack.pop()
                #     self.__abs_assignment_id = -1
                #     self.__abs_assignment_pc = -1
                # else:
                #     self._add_normal_node('Goto',
                #                           string=s, node=n, indent=self.indent_level,
                #                           pcS=self.__abs_current_pc, pcM=-1, pcE=-1,
                #                           customID=-1, mutexes=self.__abs_mutex_stack)
                #     self.__abs_current_id += 1
                #     self.__abs_current_pc += 1
                #     # Reset
                #     self.__abs_inlined_return_str = ''
                #     self.__abs_assignment_id = -1
                #     self.__abs_assignment_pc = -1
                '''  NEW '''
                if self.__abs_current_pc == 0:
                    self._add_normal_node('GotoSpecial',
                                          string=s, node=n, indent=self.indent_level,
                                          pcS=self.__abs_current_pc, pcM=-1, pcE=-1,
                                          customID=-1, mutexes=self.__abs_mutex_stack)
                    self.__abs_current_pc += 1
                else:
                    self._add_normal_node('Goto',
                                          string=s, node=n, indent=self.indent_level,
                                          pcS=self.__abs_current_pc - 1, pcM=-1, pcE=-1,
                                          customID=-1, mutexes=self.__abs_mutex_stack)

                self.__abs_current_id += 1
        return s

    def visit_ID(self, n):
        # Detecting pointer-to-function references
        # (i.e.: when a function name is used for anything else than a function call)
        #
        if n.name in self.funcName:
            prev = str(self.__stack[len(self.__stack) - 2])
            if 'FuncCall' not in self.__stack:
                self.funcReferenced.append(n.name)

        if ((self.__isGlobal(self.currentFunct, n.name) or self.__isPointer(self.currentFunct, n.name)) and
                not n.name.startswith('__cs_thread_local_')):
            self.__globalMemoryAccessed = True

        return n.name

    # ------------------------------------------------------------------

    def _add_global_node(self, name, string=None, node=None, indent=0):
        ''' Add global declaration (whatever outside thread functions)
        '''
        nodeList = []
        nodeList.append(name)
        nodeList.append(string)
        nodeList.append(node)
        nodeList.append(indent)
        self.abs_globalScope.append(tuple(nodeList))

    def _add_normal_node(self, name,
                         string=None, node=None, indent=0,
                         pcS=-1, pcM=-1, pcE=-1,
                         customID=-1, mutexes=[],
                         visible=False):
        ''' Add local artifact (whatever inside thread functions)
        '''
        nodeList = []
        nodeList.append(name)
        nodeList.append(string)
        nodeList.append(node)
        nodeList.append(indent)
        nodeList.append((pcS, pcM, pcE))
        nodeList.append(tuple(mutexes))
        nodeList.append(visible)
        if customID == -1:     # When this statement follow what exactly in the id order
            self.abs_functionScope[(self.currentFunct, self.__abs_current_id)] = tuple(nodeList)
        else:                  # when this statement require to override the current id
            self.abs_functionScope[(self.currentFunct, customID)] = tuple(nodeList)

    def _generate_decl(self, n):
        """ Generation from a Decl node.
        """
        s = ''
        # use flags to keep track through recursive calls of what is being parsed (START)
        if 'FuncDecl' in str(n.type):
            oldParsingFuncDecl = self.parsingFuncDecl
            self.parsingFuncDecl = True

        if 'Struct' in str(n.type):
            self.parsingStruct = True

        if n.funcspec:
            s = ' '.join(n.funcspec) + ' '
        if n.storage:
            s += ' '.join(n.storage) + ' '

        s += self._generate_type(n.type)

        # use flags to keep track through recursive calls of what is being parsed (END)
        if 'FuncDecl' in str(n.type):
            self.parsingFuncDecl = oldParsingFuncDecl

        if 'Struct' in str(n.type):
            self.parsingStruct = False

        """ Handling of struct declarations.
        """
        if 'Struct' in str(n.type):
            1
            # new structure declaration
            if self.parsingStruct:
                # new field in a structure
                1
        """ Handling of variable declarations.
            Each variable has the following info associated with it:
                name, type, kind, arity, size
            name
                varName[''] = list of global variables
                varName['x'] = list local variables in function or struct 'x'
                              (incl. input params for functions)
            type
                the type as declared in the original code (e.g. 'unsigned int', 'char *', ...)
            kind
                'g'  for global variables
                'l'  for local variables
                'p'  for function input parameters
                'f'  for struct fields
            arity
                0  for scalar variables
                k  for for k-dimensional arrays
            size
                [] for scalar variables
                [size1, ..., sizek] for k-dimensional arrays
        """
        # Whatever is not a function or a struct here, is a variable declaration
        # TODO: see what else should be excluded to only have var declarations after the if
        #
        if 'FuncDecl' not in str(n.type) and 'Struct' not in str(n.type) and 'Union' not in str(n.type):
            # Variable name (for variables) or field name (for structs fields).
            #
            # At this point,
            # any variable declaration can occur (a) in the global scope,
            # or (b) in a function or (c) in a struct.
            #
            # Each of those will have a name, apart from the global scope,
            # for which name we use the empty string. We call it Context.
            #
            # For example,
            #   if a variable V is declared in a function F, its Context is F.
            #   if a variable V is declared in a struct S, its Context is S.
            #   if a variable V is declared globally, its Context is ''.
            #
            # We use the context to index the arrays:
            # (1) to index the array name
            # (2) to index the arrays type, kind, arity, size,
            # in this case with the tuple (context, variable)
            #
            if not self.parsingStruct:
                variableContext = self.currentFunct
            else:
                variableContext = self.currentStruct

            if (n.name not in self.varNames[variableContext] and  # avoid duplicates
                    self.__stack.count('ParamList') <= 1):  # do not consider nested declarations
                # (example: int f1(int (f2(int a, int b)))
                self.varNames[variableContext].append(n.name)
                # Associate each new variable with a unique IDs
                self.varID[variableContext, n.name] = self.varCount

                if n.init:
                    self.varInitExpr[variableContext, n.name] = True
                else:
                    self.varInitExpr[variableContext, n.name] = False

                self.varCount += 1
            # Variable or field type
            if s.count('[') > 0:
                s2 = s[:s.find('[')]
            else:
                s2 = s
            if n.name:
                if s2.endswith(n.name):
                    s2 = s2[:-len(n.name)]
                else:
                    s2 = s2.replace(n.name, '')
            if s2.endswith(' '):
                s2 = s2[:-1]
            # Typedef expansion:
            # when some type of variable is found for which there is an entry in the list of typedefs,
            # expands directly in the symbol table the corresponding string.
            #
            self.varTypeUnExpanded[variableContext, n.name] = s2

            for x in self.typedefs:
                if s2 == x:
                    s2 = self.typedefExpansion[x]
                if s2.startswith(x + ' '):
                    s2 = s2.replace(x + ' ', self.typedefExpansion[x] + ' ', 1)
                s2 = s2.replace(' ' + x + ' ', ' ' + self.typedefExpansion[x] + ' ')
            s2 = s2.replace('\n', '')
            s2 = s2.replace('\t', ' ')
            self.varType[variableContext, n.name] = s2.rstrip()

            # Variable kind
            if self.parsingFuncDecl:  # parameter (from a function declaration)
                self.varKind[variableContext, n.name] = 'p'
                if variableContext == 'main':
                    varDecl = s
                    varDecl = varDecl.replace(' ' + n.name, ' __CS_main_arg_' + n.name)
                    varDecl = varDecl.replace(' *' + n.name, ' *__CS_main_arg_' + n.name)
                    varDecl = varDecl.replace(' *__CS_main_arg_' + n.name + '[]', ' **__CS_main_arg_' + n.name)
                    self.mainParametersDecl += '\t' + varDecl + ';\n'  # TODO
            elif self.parsingStruct:  # field in a struct (this are not really variables,
                # but we handle them using the same data structures)
                self.varKind[variableContext, n.name] = 'f'
            elif self.indent_level < 1:  # global variable
                self.varKind[variableContext, n.name] = 'g'
            else:  # local variable
                self.varKind[variableContext, n.name] = 'l'

            # Variable arity (scalars have arity 0)
            self.varArity[variableContext, n.name] = int(s.count('['))  # TODO this needs to be properly calculated

            # Variable size(s) (for scalars that is an empty array)
            self.varSize[variableContext, n.name] = []
            tmp_s = s
            i = self.varArity[variableContext, n.name]

            while i > 0:
                tmp = tmp_s[tmp_s.find("[") + 1:tmp_s.find("]")]
                if tmp == '':
                    ithSize = -1  # Unbounded array. This is equivalent to declare a pointer. TODO
                # elif not tmp.isdigit(): ithSize = -2    # Array size given by a complex
                # expression. This is like dynamically allocated blocks. TODO
                elif not tmp.isdigit():
                    ithSize = tmp  # Array size given by a complex expression. This is like dynamically allocated blocks. TODO
                else:
                    ithSize = int(tmp)  # Array size given by a constant expression

                self.varSize[variableContext, n.name].append(ithSize)
                tmp_s = tmp_s[tmp_s.find("]") + 1:]
                i = i - 1

            # This is used later on to see if a pointer is ever associated with a malloc()
            self.varMallocd[variableContext, n.name] = False
        return s

    def _generate_type(self, n, modifiers=[]):
        """ Recursive generation from a type node. n is the type node.
            modifiers collects the PtrDecl, ArrayDecl and FuncDecl modifiers
            encountered on the way down to a TypeDecl, to allow proper
            generation from it.
        """
        typ = type(n)
        retstr = ''

        if typ == c_ast.TypeDecl:
            s = ''
            if n.quals:
                s += ' '.join(n.quals) + ' '
            s += self.visit(n.type)
            nstr = n.declname if n.declname else ''
            # Resolve modifiers.
            # Wrap in parens to distinguish pointer to array and pointer to
            # function syntax.
            #
            for i, modifier in enumerate(modifiers):
                if isinstance(modifier, c_ast.ArrayDecl):
                    if (i != 0 and isinstance(modifiers[i - 1], c_ast.PtrDecl)):  # array-of-pointers
                        nstr = '(' + nstr + ')'
                    nstr += '[' + self.visit(modifier.dim) + ']'
                elif isinstance(modifier, c_ast.FuncDecl):
                    if (i != 0 and isinstance(modifiers[i - 1], c_ast.PtrDecl)):  # pointer-to-function
                        nstr = '(' + nstr + ')'
                        if not self.parsingTypedef:
                            if not self.parsingStruct:
                                variableContext = self.currentFunct
                            else:
                                variableContext = self.currentStruct
                            self.varPtrToFunct[variableContext, self.__symbolsstack[-1]] = True

                    nstr += '(' + self.visit(modifier.args) + ')'

                elif isinstance(modifier, c_ast.PtrDecl):  # pointer
                    if modifier.quals:
                        nstr = '* %s %s' % (' '.join(modifier.quals), nstr)
                    else:
                        nstr = '*' + nstr
            if nstr:
                s += ' ' + nstr

            retstr = s

            # When generating nested parameter declarations,
            # strip the names of the parameters (e.g. names of parameters in a pointer to function).
            #
            if self.__stack.count('ParamList') > 1 and n.declname:
                retstr = retstr[:retstr.rfind(str(n.declname)) - 1]
                if retstr[-1] == ' ':
                    retstr = retstr[:-1]

        elif typ == c_ast.Decl:
            retstr = self._generate_decl(n.type)
        elif typ == c_ast.Typename:
            retstr = self._generate_type(n.type)
        elif typ == c_ast.IdentifierType:
            retstr = ' '.join(n.names) + ' '
        elif typ in (c_ast.ArrayDecl, c_ast.PtrDecl, c_ast.FuncDecl):
            retstr = self._generate_type(n.type, modifiers + [n])
        else:
            retstr = self.visit(n)

        return retstr

    def _make_indent(self, delta=0):
        return (self.indent_level + delta) * self.INDENT_SPACING

    def _getCurrentCoords(self, item):
        # return '/*cseq:coords '+ str(item.coord) +' */\n'
        return ''

    def visit(self, node):
        method = 'visit_' + node.__class__.__name__
        # Extracts node coords where possible.
        if hasattr(node, 'coord'):
            self.nodecoords[node] = str(node.coord)
        else:
            self.nodecoords[node] = ''

        # This is to update the current coord (= filename+line number) of the input file being parsed,
        # considering that:
        #
        # - on the same line of input, there may be more AST nodes (shouldn't enter duplicates)
        # - compound statement and empty statements have line number 0 (shouldn't update the current line)
        # - the same line of input may correspond to many lines of output
        #
        lineCoords = ''
        if not isinstance(node, c_ast.FileAST) and str(node) != 'None' and self.indent_level == 0:
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
        self.__stack.append(node.__class__.__name__)
        retval = lineCoords + getattr(self, method, self.generic_visit)(node)
        self.__stack.pop()
        return retval

    def loadfromstring(self, string):
        self.ast = c_parser.CParser().parse(string)
        self.__output = self.visit(self.ast)

    def show(self):
        print self.__output

    def save(self, filename):
        outfile = open(filename, "w")
        outfile.write(self.__output)
        outfile.close()

    def string(self):
        return (self.visit(self.ast))

    # Checks whether variable  v  from function  f  is a pointer.
    #
    def __isPointer(self, f, v):
        if v in self.varNames[f] and self.varType[f, v].endswith('*'):
            return True
        elif v in self.varNames[''] and self.varType['', v].endswith('*'):
            return True
        else:
            return False

    # Checks whether variable  v  from function  f  is global.
    #
    def __isGlobal(self, f, v):
        if (v in self.varNames[''] and v not in self.varNames[f]):
            return True
        else:
            return False

    def printsymbols(self):
        print "list of functions:"
        for f in self.funcName:
            s = "   %s" % f
            if f in self.funcReferenced:
                s += '   referenced'
            print s,

            if f != '':
                print "  call count %s" % self.funcCallCnt[f]
            else:
                print ''
        print '\n'

        print "list of thread functions:\n"

        for f in self.threadName:
            print "   %s  call count %s" % (f, self.threadCallCnt[f])

        print '\n'

        print "parameters for main():\n" + self.mainParametersDecl

        # List of all variables
        print "Variables:"
        for f in self.funcName:
            if not f == '':
                print "   " + f
            else:
                print "   (global)"

            for v in self.varNames[f]:
                # detailed var description
                s = "       "
                s += "id " + str(self.varID[f, v]) + "  "
                s += "var '" + str(v) + "'   "
                s += "type '" + self.varType[f, v] + "'   "
                s += "kind '" + self.varKind[f, v] + "'   "
                s += "arity '" + str(self.varArity[f, v]) + "'   "
                s += "size '" + str(self.varSize[f, v]) + "'   "
                s += "mallocd '" + str(self.varMallocd[f, v]) + "'   "
                if (f, v) in self.varPtrToFunct:
                    s += "ptr-to-f '" + str(self.varPtrToFunct[f, v]) + "'"

                print s

        print '\n'

        # List of all fields
        print "Fields:"
        for f in self.structName:
            if not f == '':
                print "   " + str(f)
            else:
                print "   (global)"

            for v in self.varNames[f]:
                # detailed var description
                s = "       "
                s += "id " + str(self.varID[f, v]) + "  "
                s += "var '" + v + "'   "
                s += "type '" + self.varType[f, v] + "'   "
                s += "kind '" + self.varKind[f, v] + "'   "
                s += "arity '" + str(self.varArity[f, v]) + "'   "
                s += "size '" + str(self.varSize[f, v]) + "'   "
                s += "mallocd '" + str(self.varMallocd[f, v]) + "'"

                print s

        print '\n'

        print "Typedefs:"
        for x in self.typedefs:
            print x + " -> " + self.typedefExpansion[x]

        print '\n'

        print "Pointer variables:"
        for f in self.funcName:
            if not f == '':
                print "   " + f
            else:
                print "   (global)"

            for v in self.varNames[f]:
                if self.varType[f, v].endswith('*'):
                    s = "       "
                    s += "var '" + v + "'   "
                    s += "type '" + self.varType[f, v] + "'   "
                    s += "kind '" + self.varKind[f, v] + "'   "
                    s += "arity '" + str(self.varArity[f, v]) + "'   "
                    s += "size '" + str(self.varSize[f, v]) + "'   "

                    print s

        print '\n'

        '''
        print "Function blocks:"
        for f in self.funcName:
            if f != '':
                print "function '%s' ----------------------------------:" % f
                print self.funcBlock[f] + '\n'
                print self.funcBlockIn[f] +'\n'
                print self.funcBlockOut[f] +'\n'

        print "Last statement, by function:"
        for f in self.funcName:
            if f != '':
                print "function: %s   stmt: %s" % (f, self.lastFuncStmt[f])

        print '\n'
        '''

        print "All symbols (new symbol table - work in progress):"
        for s in self.symbols:
            # print "   %s    [%s]" % (s, self.symbolshierarchy[s, blockstack])
            print "   %s  " % str(s)
