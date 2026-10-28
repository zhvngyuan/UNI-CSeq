#coding=utf-8

"""
insertassertion.py
只负责在输入C程序中插入断言和断言用变量的定义。
结构设计仿 instrumenter.py, 但不包含其余的代码转换逻辑。
"""

from time import gmtime, strftime, localtime
import math, re
import utils
import pycparser.c_ast
import pickle
from modules import module

# _backends = ['cbmc', 'cbmc-ext', 'cbmc-5.10', 'cbmc-svcomp2020', 'esbmc', 'llbmc', 'blitz', 'satabs', '2ls', 'klee', 'cpachecker', 'framac', 'smack', 'ultimate', 'symbiotic']  # add 'cbmc-5.10'

# fmap = {}

# fmap['cbmc', '__VERIFIER_assume'] = '__CPROVER_assume'
# fmap['cbmc', '__VERIFIER_assertext'] = '__CPROVER_assert'
# fmap['cbmc', '__VERIFIER_assert'] = 'assert'
# fmap['cbmc', '__VERIFIER_nondet_int'] = 'nondet_int'
# fmap['cbmc', '__VERIFIER_nondet_uint'] = 'nondet_uint'
# fmap['cbmc', '__VERIFIER_nondet_bool'] = 'nondet_bool'
# fmap['cbmc', '__VERIFIER_nondet_char'] = 'nondet_char'
# fmap['cbmc', '__VERIFIER_nondet_uchar'] = 'nondet_uchar'

# fmap['cbmc-ext', '__VERIFIER_assume'] = '__CPROVER_assume'
# fmap['cbmc-ext', '__VERIFIER_assertext'] = '__CPROVER_assert'
# fmap['cbmc-ext', '__VERIFIER_assert'] = 'assert'
# fmap['cbmc-ext', '__VERIFIER_nondet_int'] = 'nondet_int'
# fmap['cbmc-ext', '__VERIFIER_nondet_uint'] = 'nondet_uint'
# fmap['cbmc-ext', '__VERIFIER_nondet_bool'] = 'nondet_bool'
# fmap['cbmc-ext', '__VERIFIER_nondet_char'] = 'nondet_char'
# fmap['cbmc-ext', '__VERIFIER_nondet_uchar'] = 'nondet_uchar'

# fmap['cbmc-5.10', '__VERIFIER_assume'] = '__CPROVER_assume'
# fmap['cbmc-5.10', '__VERIFIER_assertext'] = '__CPROVER_assert'
# fmap['cbmc-5.10', '__VERIFIER_assert'] = 'assert'
# fmap['cbmc-5.10', '__VERIFIER_nondet_int'] = 'nondet_int'
# fmap['cbmc-5.10', '__VERIFIER_nondet_uint'] = 'nondet_uint'
# fmap['cbmc-5.10', '__VERIFIER_nondet_bool'] = 'nondet_bool'
# fmap['cbmc-5.10', '__VERIFIER_nondet_char'] = 'nondet_char'
# fmap['cbmc-5.10', '__VERIFIER_nondet_uchar'] = 'nondet_uchar'

# fmap['cbmc-svcomp2020', '__VERIFIER_assume'] = '__CPROVER_assume'
# fmap['cbmc-svcomp2020', '__VERIFIER_assertext'] = '__CPROVER_assert'
# fmap['cbmc-svcomp2020', '__VERIFIER_assert'] = 'assert'
# fmap['cbmc-svcomp2020', '__VERIFIER_nondet_int'] = 'nondet_int'
# fmap['cbmc-svcomp2020', '__VERIFIER_nondet_uint'] = 'nondet_uint'
# fmap['cbmc-svcomp2020', '__VERIFIER_nondet_bool'] = 'nondet_bool'
# fmap['cbmc-svcomp2020', '__VERIFIER_nondet_char'] = 'nondet_char'
# fmap['cbmc-svcomp2020', '__VERIFIER_nondet_uchar'] = 'nondet_uchar'

# fmap['esbmc', '__VERIFIER_assume'] = '__ESBMC_assume'
# fmap['esbmc', '__VERIFIER_assertext'] = '__ESBMC_assert'
# fmap['esbmc', '__VERIFIER_assert'] = 'assert'
# fmap['esbmc', '__VERIFIER_nondet_int'] = '__VERIFIER_nondet_int'
# fmap['esbmc', '__VERIFIER_nondet_uint'] = '__VERIFIER_nondet_uint'
# fmap['esbmc', '__VERIFIER_nondet_bool'] = '__VERIFIER_nondet_bool'
# fmap['esbmc', '__VERIFIER_nondet_char'] = '__VERIFIER_nondet_char'
# fmap['esbmc', '__VERIFIER_nondet_uchar'] = '__VERIFIER_nondet_uchar'

# fmap['llbmc', '__VERIFIER_assume'] = '__llbmc_assume'
# fmap['llbmc', '__VERIFIER_assertext'] = '__llbmc_assert'
# fmap['llbmc', '__VERIFIER_assert'] = '__llbmc_assert'
# fmap['llbmc', '__VERIFIER_nondet_int'] = 'nondet_int'
# fmap['llbmc', '__VERIFIER_nondet_uint'] = 'nondet_int'
# fmap['llbmc', '__VERIFIER_nondet_bool'] = 'nondet_bool'
# fmap['llbmc', '__VERIFIER_nondet_char'] = 'nondet_char'
# fmap['llbmc', '__VERIFIER_nondet_uchar'] = 'nondet_uchar'

# fmap['blitz', '__VERIFIER_assume'] = '__CPROVER_assume'
# fmap['blitz', '__VERIFIER_assertext'] = 'assert'
# fmap['blitz', '__VERIFIER_assert'] = 'assert'
# fmap['blitz', '__VERIFIER_nondet_int'] = 'nondet_int'
# fmap['blitz', '__VERIFIER_nondet_uint'] = 'nondet_uint'
# fmap['blitz', '__VERIFIER_nondet_bool'] = 'nondet_bool'
# fmap['blitz', '__VERIFIER_nondet_char'] = 'nondet_char'
# fmap['blitz', '__VERIFIER_nondet_uchar'] = 'nondet_uchar'

# fmap['satabs', '__VERIFIER_assume'] = '__CPROVER_assume'
# fmap['satabs', '__VERIFIER_assertext'] = 'assert'
# fmap['satabs', '__VERIFIER_assert'] = 'assert'
# fmap['satabs', '__VERIFIER_nondet_int'] = 'nondet_int'
# fmap['satabs', '__VERIFIER_nondet_uint'] = 'nondet_uint'
# fmap['satabs', '__VERIFIER_nondet_bool'] = 'nondet_bool'
# fmap['satabs', '__VERIFIER_nondet_char'] = 'nondet_char'
# fmap['satabs', '__VERIFIER_nondet_uchar'] = 'nondet_uchar'

# # fmap['2ls', '__VERIFIER_assume'] = '__CPROVER_assume'
# # fmap['2ls', '__VERIFIER_assertext'] = 'assert'
# # fmap['2ls', '__VERIFIER_assert'] = 'assert'
# # fmap['2ls', '__VERIFIER_nondet_int'] = 'nondet_int'
# # fmap['2ls', '__VERIFIER_nondet_uint'] = 'nondet_uint'

# fmap['klee', '__VERIFIER_assume'] = 'KLEE_assume'
# fmap['klee', '__VERIFIER_assertext'] = 'KLEE_assert'
# fmap['klee', '__VERIFIER_assert'] = 'KLEE_assert'
# fmap['klee', '__VERIFIER_nondet_int'] = 'KLEE_nondet_int'
# fmap['klee', '__VERIFIER_nondet_uint'] = 'KLEE_nondet_uint'
# fmap['klee', '__VERIFIER_nondet_bool'] = 'KLEE_nondet_bool'
# fmap['klee', '__VERIFIER_nondet_char'] = 'KLEE_nondet_char'
# fmap['klee', '__VERIFIER_nondet_uchar'] = 'KLEE_nondet_uchar'

# fmap['cpachecker', '__VERIFIER_assume'] = '__VERIFIER_assume'
# fmap['cpachecker', '__VERIFIER_assertext'] = '__VERIFIER_assert'
# fmap['cpachecker', '__VERIFIER_assert'] = '__VERIFIER_assert'
# fmap['cpachecker', '__VERIFIER_nondet_int'] = '__VERIFIER_nondet_int'
# fmap['cpachecker', '__VERIFIER_nondet_uint'] = '__VERIFIER_nondet_uint'
# fmap['cpachecker', '__VERIFIER_nondet_bool'] = '__VERIFIER_nondet_bool'
# fmap['cpachecker', '__VERIFIER_nondet_char'] = '__VERIFIER_nondet_char'
# fmap['cpachecker', '__VERIFIER_nondet_uchar'] = '__VERIFIER_nondet_uchar'

# fmap['framac', '__VERIFIER_assume'] = '__FRAMAC_assume'
# fmap['framac', '__VERIFIER_assertext'] = '__FRAMAC_assert'
# fmap['framac', '__VERIFIER_assert'] = '__FRAMAC_assert'
# fmap['framac', '__VERIFIER_nondet_int'] = '__VERIFIER_nondet_int'
# fmap['framac', '__VERIFIER_nondet_uint'] = '__VERIFIER_nondet_uint'
# fmap['framac', '__VERIFIER_nondet_bool'] = '__VERIFIER_nondet_bool'
# fmap['framac', '__VERIFIER_nondet_char'] = '__VERIFIER_nondet_char'
# fmap['framac', '__VERIFIER_nondet_uchar'] = '__VERIFIER_nondet_uchar'

# fmap['smack', '__VERIFIER_assume'] = '__VERIFIER_assume'
# fmap['smack', '__VERIFIER_assertext'] = 'assert'
# fmap['smack', '__VERIFIER_assert'] = 'assert'
# fmap['smack', '__VERIFIER_nondet_int'] = '__VERIFIER_nondet_int'
# fmap['smack', '__VERIFIER_nondet_uint'] = '__VERIFIER_nondet_uint'
# fmap['smack', '__VERIFIER_nondet_bool'] = '__VERIFIER_nondet_bool'
# fmap['smack', '__VERIFIER_nondet_char'] = '__VERIFIER_nondet_char'
# fmap['smack', '__VERIFIER_nondet_uchar'] = '__VERIFIER_nondet_uchar'

# fmap['ultimate', '__VERIFIER_assume'] = '__VERIFIER_assume'
# fmap['ultimate', '__VERIFIER_assertext'] = '__VERIFIER_assert'
# fmap['ultimate', '__VERIFIER_assert'] = '__VERIFIER_assert'
# fmap['ultimate', '__VERIFIER_nondet_int'] = '__VERIFIER_nondet_int'
# fmap['ultimate', '__VERIFIER_nondet_uint'] = '__VERIFIER_nondet_uint'
# fmap['ultimate', '__VERIFIER_nondet_bool'] = '__VERIFIER_nondet_bool'
# fmap['ultimate', '__VERIFIER_nondet_char'] = '__VERIFIER_nondet_char'
# fmap['ultimate', '__VERIFIER_nondet_uchar'] = '__VERIFIER_nondet_uchar'

# fmap['symbiotic', '__VERIFIER_assume'] = '__VERIFIER_assume'
# fmap['symbiotic', '__VERIFIER_assertext'] = '__VERIFIER_assert'
# fmap['symbiotic', '__VERIFIER_assert'] = '__VERIFIER_assert'
# fmap['symbiotic', '__VERIFIER_nondet_int'] = '__VERIFIER_nondet_int'
# fmap['symbiotic', '__VERIFIER_nondet_uint'] = '__VERIFIER_nondet_uint'
# fmap['symbiotic', '__VERIFIER_nondet_bool'] = '__VERIFIER_nondet_bool'
# fmap['symbiotic', '__VERIFIER_nondet_char'] = '__VERIFIER_nondet_char'
# fmap['symbiotic', '__VERIFIER_nondet_uchar'] = '__VERIFIER_nondet_uchar'


# _maxrightindent = 25   # max columns right for non-raw lines
# _rawlinemarker = '__CSEQ_removeindent'


# # Map thread-specific types (e.g., pthread_mutex_t -> cspthread_mutex_t)
# # to avoid parsing clashes.
# #
# typemap = {}
# typemap['pthread_barrier_t'] = 'cspthread_barrier_t'
# typemap['pthread_cond_t'] = 'cspthread_cond_t'
# typemap['pthread_mutex_t'] = 'cspthread_mutex_t'
# typemap['pthread_t'] = 'cspthread_t'
# typemap['pthread_key_t'] = 'cspthread_key_t'
# typemap['pthread_mutexattr_t'] = 'cspthread_mutexattr_t'
# typemap['pthread_condattr_t'] = 'cspthread_condattr_t'
# typemap['pthread_barrierattr_t'] = 'cspthread_barrierattr_t'

class randomThreadInfo(): # 表示随机线程的信息 在处理单变量访问序时使用

	def __init__(self,index = None, prio = None):
		self.index = index
		self.prio = prio


class insertassertion(module.Translator):
	__visitingstruct = False
	__structstack = []			   # stack of struct name
	__wellnested = False

	__avoid_type = []
	emptystructs = []


	def init(self):           
                self.inputparam('mode', '断言插入模式, 如rww/wwr/rwr/wrw', '', None, True)
                self.inputparam('var_type', '目标变量类型', '', None, True)
                self.inputparam('variable', '目标变量名', '', None, True)
                self.inputparam('variable_list', '相关变量列表', '', [], True)
                self.inputparam('is_pointer', '是否指针类型', '', False, True)
                self.inputparam('random_func', '线程信息字典', '', {}, True)
                self.inputparam('assert_number', '断言数', '', 1, True)
		
        def loadfromstring(self, codestr, env):
                self.env = env
                mode = self.getinputparam('mode')
                var_type = self.getinputparam('var_type')
                variable = self.getinputparam('variable')
                variable_list = self.getinputparam('variable_list')
                is_pointer = self.getinputparam('is_pointer')
                random_func = self.getinputparam('random_func')
                assert_number = self.getinputparam('assert_number')

                insert_code = self._generate_assertion_code(
                mode, var_type, variable, variable_list, is_pointer, random_func, assert_number
                )

                # 这里选择插入到文件头，你也可以根据实际需求插入到 main 函数体或者变量声明区
                self.output = insert_code + "\n" + codestr

        def _generate_assertion_code(self, mode, var_type, variable, variable_list, is_pointer, random_func, assert_number):
                # 仿 instrumenter.py 的插入变量、断言逻辑，做简化
                code = ""
                indent = ' ' * 4
                max_index = 0
                for func in random_func:
                max_index = max(max_index, getattr(random_func[func], 'index', 0))
                if not max_index:
                max_index = 1

                if mode == 'rww':
                if is_pointer:
                        for tmp_var in variable_list:
                        flag = '*' if tmp_var == variable else ''
                        for i in range(max_index):
                                code += '{}{} {}rww_r_tmp{}_{};\n'.format(indent, var_type.rstrip()[0:-1], flag, tmp_var, i+1)
                        for i in range(max_index):
                                code += '{}int rww_r_tmp{}_{}_num;\n'.format(indent, tmp_var, i+1)
                        for i in range(assert_number):
                                code += '{}{} rww_w{}_{};\n'.format(indent, var_type.rstrip()[0:-1], flag, tmp_var, i+1)
                else:
                        for i in range(max_index):
                        code += '{}{} rww_r_tmp{};\n'.format(indent, var_type.strip(), i+1)
                        for i in range(max_index):
                        code += '{}int rww_r_tmp{}_num;\n'.format(indent, i+1)
                        for i in range(assert_number):
                        code += '{}{} rww_w{};\n'.format(indent, var_type.strip(), i+1)
                # 示例插入断言
                code += '{}assert({}); // auto-inserted assertion\n'.format(indent, variable)
                # 其它模式可类似扩展

                return code

        def visit(self,n):
		out = super(self.__class__, self).visit(n)

		if isinstance(n,pycparser.c_ast.IdentifierType) or isinstance(n,pycparser.c_ast.Typename):
			if out in typemap: out = typemap[out]

		return out


	def visit_Decl(self,n,no_type=False):
		# Map pthread-specific types.
		#
		#print("declaration [%s] fspec:[%s] nstor:[%s] type:[%s]" % (s,(' '.join(n.funcspec) + ' '),(' '.join(n.storage) + ' '), self._generate_type(n.type)))
		#print("stack: %s\n" % (self.stack))
		checkforinit = False

		if type(n.type) == pycparser.c_ast.TypeDecl:
			if type(n.type.type) == pycparser.c_ast.IdentifierType:
				if n.type.type.names[0] in typemap:
					#print("type:[%s] typedecl:[%s]" % (self.visit(n.type.type),n.type.type.names[0]))
					n.type.type.names[0] = typemap[n.type.type.names[0]]
					#self.warn("---> [%s]." % (n.type.type.names[0]))
					if n.init:
						checkforinit = True
						#self.warn("---> [%s]" % (self.visit(n.init)))

		# no_type is used when a Decl is part of a DeclList, where the type is
		# explicitly only for the first delaration in a list.
		#
		s = n.name if no_type else self._generate_decl(n)

		if n.name == '__VERIFIER_assert' and self.backend == 'smack':
			s2 = s.replace('__VERIFIER_assert','__renamed__VERIFIER_assert',1)
			#print("REPLACING %s->%s" % (s,s2))
			s = s2


		# In case  x  has a custom bitwidth (passed by a previous module), convert
		# 'int x'  to  'bitvectors[k] x' or
		# 'unsigned int x'  to  'unsigned bitvectors[k] x'.
		ninitextra = ''
		prefix = ''

		if self.backend in ('cbmc','cbmc-ext','cbmc-5.10'):  # new add
			if s.startswith('static '):
				s = s[7:]	# remove static
				prefix = 'static '

			if s.startswith("_Bool "):
				pass
			elif self.bitwidths is not None:
				if self.__visitingstruct and len(self.__structstack) > 0:
					if (self.__structstack[-1], n.name) in self.bitwidths:
						if s.startswith("unsigned int "):
							s = s.replace("unsigned int ","unsigned __CPROVER_bitvector[%s] " % self.bitwidths[self.__structstack[-1],n.name],1)
						elif s.startswith("int "):
							s = s.replace("int ","__CPROVER_bitvector[%s] " % self.bitwidths[self.__structstack[-1],n.name],1)
						else:
							temp = s.split()   # split the declaration
							for i, item in enumerate(temp):
								if item.lstrip('*') == n.name and i > 0 and temp[i-1] not in self.__avoid_type and temp[i-1] in ('long', 'short', 'char',):   # temp[i-1] is the type
									temp[i-1] = '__CPROVER_bitvector[%s]' % self.bitwidths[self.__structstack[-1],n.name]
									break
							s = " ".join(temp)
				else:
					currentFunct = self.currentFunct if self.currentFunct != 'main_thread' else 'main'
					if s.startswith("unsigned int ") and (currentFunct,n.name) in self.bitwidths:
						s = s.replace("unsigned int ","unsigned __CPROVER_bitvector[%s] " % self.bitwidths[currentFunct,n.name],1)
						ninitextra = '(unsigned __CPROVER_bitvector[%s])' % self.bitwidths[currentFunct,n.name]
					elif s.startswith("int ") and (currentFunct, n.name) in self.bitwidths:
						numbit = self.bitwidths[currentFunct, n.name]
						s = s.replace("int ","C __CPROVER_bitvector[%s] " % numbit,1)
						ninitextra = '(__CPROVER_bitvector[%s])' % numbit
					elif (currentFunct, n.name) in self.bitwidths:
						numbit = self.bitwidths[currentFunct, n.name]
						temp = s.split()
						for i, item in enumerate(temp):
							if item.lstrip('*') == n.name and i > 0 and temp[i-1] not in self.__avoid_type and temp[i-1] in ('long', 'short', 'char',):
								temp[i-1] = '__CPROVER_bitvector[%s]' % numbit
								break
						s = " ".join(temp)
			if prefix != '':
				s = prefix + s

		# Experimental: ESBMC with bitvectors
		if self.backend in ('esbmc'):
			currentFunct = self.currentFunct if self.currentFunct != 'main_thread' else 'main'

			if currentFunct == 'main':
				if n.name:
					if n.name.startswith('__cs_tmp_t'):
						#print ("---> %s <---" % n.name)
						norobin = True if self.getinputparam('norobin') is not None else False

						if not norobin:
							s = s.replace("unsigned int ","unsigned _ExtInt(%s) " % self.bitwidths[self.currentFunct,n.name],1)

		if n.bitsize: s += ' : ' + self.visit(n.bitsize)

		pthread_init_dict = {
			#'pthread_mutex_t' : 'PTHREAD_MUTEX_INITIALIZER',
			#'pthread_cond_t'  : 'PTHREAD_COND_INITIALIZER',
			#'pthread_rwlock_t' : 'PTHREAD_RWLOCK_INITIALIZER'
			'pthread_mutex_t' : '0',
			'pthread_cond_t'  : '0',
			'pthread_rwlock_t' : '0'
		}

		# Default initialisation for pthread_xyz types
		if n.init:
			if isinstance(n.init, pycparser.c_ast.InitList):
				if checkforinit:
					s += ' = -1' # e.g., pthread_mutex_t t = .... -> cspthread_mutex_t t = -1;
				else:
					s += ' = {' + self.visit(n.init) + '}'

			elif isinstance(n.init, pycparser.c_ast.ExprList):
				s += ' = (' + self.visit(n.init) + ')'
			else:
				#s += ' = ' + self.visit(n.init)
				s += ' = ' + ninitextra + '(' + self.visit(n.init) + ')'

		'''
		# default init to 0 for local scalar variables ?????
		elif not n.init and self.blockid != '0' and not self.__visitingstruct:
			print ("STRUCTS [[[%s]]]" % self.Parser.type)


			if (self.blockid,n.name) not in self.Parser.struct:
				self.debug("uninitialised local variable [%s] block: [%s]"% (n.name,self.blockid))
				print (self.Parser.type)

			s += '= 0'
		'''


		return s


	def _generate_struct_union(self, n, name):
		""" Generates code for structs and unions. name should be either
			'struct' or union.
		"""
		s = name + ' ' + (n.name or '')
		# There should be no anonymous struct, handling in workarounds module
		self.__visitingstruct = True
		if n.name:
			self.__structstack.append(n.name)
		if n.decls:
			s += '\n'
			s += self._make_indent()
			self.indent_level += 2
			s += '{\n'
			for decl in n.decls:
				s += self._generate_stmt(decl)
			self.indent_level -= 2
			s += self._make_indent() + '}'
		self.__visitingstruct = False
		if n.name:
			self.__structstack.pop()
		return s


	def visit_Struct(self, n):
		out = super(self.__class__, self).visit_Struct(n)

		# empty structure has no fields
		if n.decls is None and self.stack[-2] == 'Decl' and self.stack[-3] != 'Struct' and n.name in self.emptystructs:
			out += '{ char dummy; }'
			self.emptystructs.remove(n.name)

		return out


	def visit_Typedef(self, n):
		s = ''
		if n.storage: s += ' '.join(n.storage) + ' '
		s += self._generate_type(n.type)

		return s


	''' converts function calls '''
	def visit_FuncCall(self,n):
		fref = self._parenthesize_unless_simple(n.name)

		if fref == 'pthread_create': fref = 'pthread_create_2'  # 'pthread_create_2'

		# Transformation 3.
		if fref == '__CSEQ_rawline':
			return self.visit(n.args)[1:-1]+_rawlinemarker

		sync_dict = {
			'pthread_mutex_destroy' : True,
			'pthread_mutex_lock' : True,
			'pthread_mutex_unlock' : True,
			'pthread_cond_wait_1' : True,
			'pthread_cond_wait_2' : True,
			'pthread_barrier_init' : True,
			'pthread_barrier_wait_1' : True,
			'pthread_barrier_wait_2' : True
		}

		# Apparently CBMC can happen to have a very different behaviour
		# depending on whether or not (in functions that are never invoked!?)
		# some assertions are transformed into assumptions...
		#
		if self.__wellnested:
			if (self.Parser.funcCallCnt['pthread_mutex_lock'] <= 1 and
				self.Parser.funcCallCnt['pthread_cond_wait_1'] <= 1 and
				self.Parser.funcCallCnt['pthread_cond_wait_2'] <= 1 and
				self.Parser.funcCallCnt['pthread_barrier_wait_1'] <= 1):
				self.__wellnested = False
				self.warn("disabling assumptions on locks well-nestedness")
				#self.log("- - - - - - -> has locks? %s %s <- - - - - - - -" % (cntoveralloccurrences,cntexplicitcalls))

		if (fref == '__VERIFIER_assertext' and
				self.__wellnested and
				self.backend != 'framac' and
				self.currentFunct in sync_dict):
			return fmap[self.backend, '__VERIFIER_assume'] + '(' + self.visit(n.args.exprs[0]) + ')'

		args = self.visit(n.args)

		if (fref == '__VERIFIER_assertext' and self.backend not in ('cbmc', 'esbmc')):
			args = self.visit(n.args.exprs[0])   # Only get the first expression

		if (self.backend, fref) in fmap:
			fref = fmap[self.backend, fref]

		if (fref == '__VERIFIER_error' and self.backend == 'framac'):
			return '__FRAMAC_assert(0)'

		return fref + '(' + args + ')'

	
	# def _generateheader(self):
	# 	masterhash_framework = '0000'
	# 	masterhash_modulechain = '0000'

	# 	h  = '/***\n'
	# 	h += ' ***  generated by CSeq [ %s / %s ] %s\n' % (masterhash_framework,masterhash_modulechain,strftime("%Y-%m-%d %H:%M:%S",localtime()))
	# 	h += ' ***\n'

	# 	# details of each core/ component
	# 	for i,filename in enumerate(sorted(utils.listfiles('core','*.py'))):
	# 		file = utils.printFile(filename)
	# 		lines = file.splitlines()
	# 		maxlines = len(lines)

	# 		for j,l in enumerate(lines):
	# 			if l.startswith('Changes:'):
	# 				date = utils.validatedate(lines[j+1].split()[0],'%Y.%m.%d')
	# 				if date.startswith(' '):
	# 					self.warn('unable to extract date from changelog in module %s' % filename)

	# 				h += ' ***                      %s %s %s\n' % (utils.shortfilehash(filename),date,filename[:-3])

	# 	# details for each module in the chain
	# 	h += ' ***\n'
	# 	h += ' ***  params:\n'
	# 	h += ' ***    ' +' '.join(opt[0]+' '+opt[1] for opt in self.env.opts) + '\n'

	# 	h += ' ***\n'
	# 	h += ' ***  mode:\n'
	# 	if self.mode != '':
	# 		h += ' ***    %s\n' %self.mode
	# 		h += ' ***    %s\n' %self.type
	# 		h += ' ***    %s\n' %self.variable

	# 	h += ' ***\n'
	# 	h += ' ***  use loop abstraction:\n'
	# 	h += ' ***    %s\n' %self.loopAbsFlag

	# 	h += ' ***\n'
	# 	h += ' ***  modules:\n'

	# 	for m in self.env.modules:
	# 		params = '(' + ' '.join(p.id for p in m.inputparamdefs) + ')'
	# 		hash = utils.shortfilehash('modules/%s.py' % m.name())
	# 		h += ' ***    %s %s%s %s\n' %(hash,m.name(),'',params) # m.VERSION

	# 	h += ' ***\n'
	# 	h += ' ***/\n'

	# 	return h

