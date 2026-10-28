#coding=utf-8
#------------------------------------------------------------------------------
# pycparser: c_generator.py
#
# C code generator from pycparser AST nodes.
#
# Eli Bendersky [http://eli.thegreenplace.net]
# License: BSD
#------------------------------------------------------------------------------
from ctypes import pointer
from operator import truediv
from . import c_ast
import pycparserext.ext_c_parser

class CGenerator(object):
	""" Uses the same visitor pattern as c_ast.NodeVisitor, but modified to
		return a value from each visit method, using string accumulation in
		generic_visit.
	"""
	def __init__(self):
		# Statements start with indentation of self.indent_level spaces, using
		# the _make_indent method
		#
		self.indent_level = 0

	def _make_indent(self):
		return ' ' * self.indent_level

	def visit(self, node):
		
		'''
		if self.name()=="instrumenter" and type(node) in (c_ast.If,):
			print("C_generator.func_visit:visit IF")
		'''

		method = 'visit_' + node.__class__.__name__
		'''
		if self.name()=="preinstrumenter":
			print(method)
		'''
		return getattr(self, method, self.generic_visit)(node)  #

	def generic_visit(self, node):
		#~ print('generic:', type(node))
		if node is None:
			return ''
		else:
			return ''.join(self.visit(c) for c_name, c in node.children())

	def visit_Constant(self, n):
		return n.value

	def visit_ID(self, n):
		return n.name
	
	def visit_Pragma(self, n):
		ret = '#pragma'
		if n.string:
			ret += ' ' + n.string
		return ret

	def visit_ArrayRef(self, n):
		arrref = self._parenthesize_unless_simple(n.name)
		return arrref + '[' + self.visit(n.subscript) + ']'

	def visit_StructRef(self, n):
		sref = self._parenthesize_unless_simple(n.name)
		return sref + n.type + self.visit(n.field)

	def visit_FuncCall(self, n):
		fref = self._parenthesize_unless_simple(n.name)
		return fref + '(' + self.visit(n.args) + ')'

	def visit_UnaryOp(self, n):
		operand = self._parenthesize_unless_simple(n.expr)
		if n.op == 'p++':
			return '%s++' % operand
		elif n.op == 'p--':
			return '%s--' % operand
		elif n.op == 'sizeof':
			# Always parenthesize the argument of sizeof since it can be
			# a name.
			return 'sizeof(%s)' % self.visit(n.expr)
		else:
			return '%s%s' % (n.op, operand)

	def visit_BinaryOp(self, n):
		lval_str = self._parenthesize_if(n.left,
							lambda d: not self._is_simple_node(d))
		rval_str = self._parenthesize_if(n.right,
							lambda d: not self._is_simple_node(d))
		return '%s %s %s' % (lval_str, n.op, rval_str)

	def visit_Assignment(self, n):
		rval_str = self._parenthesize_if(
							n.rvalue,
							lambda n: isinstance(n, c_ast.Assignment))
		return '%s %s %s' % (self.visit(n.lvalue), n.op, rval_str)

	def visit_IdentifierType(self, n):
		return ' '.join(n.names)

	def _visit_expr(self, n):
		if isinstance(n, c_ast.InitList):
			return '{' + self.visit(n) + '}'
		elif isinstance(n, c_ast.ExprList):
			return '(' + self.visit(n) + ')'
		else:
			return self.visit(n)

	def visit_Decl(self, n, no_type=False):
		# no_type is used when a Decl is part of a DeclList, where the type is
		# explicitly only for the first declaration in a list.
		#
		s = n.name if no_type else self._generate_decl(n)
		if n.bitsize: s += ' : ' + self.visit(n.bitsize)
		if n.init:
			s += ' = ' + self._visit_expr(n.init)

		# print('c_generator.visit_Decl: '+ s)
		return s

	def visit_DeclList(self, n):
		s = self.visit(n.decls[0])
		if len(n.decls) > 1:
			s += ', ' + ', '.join(self.visit_Decl(decl, no_type=True)
									for decl in n.decls[1:])
		return s

	def visit_Typedef(self, n):
		s = ''
		if n.storage: s += ' '.join(n.storage) + ' '
		s += self._generate_type(n.type)
		return s

	def visit_Cast(self, n):
		s = '(' + self._generate_type(n.to_type) + ')'
		return s + ' ' + self._parenthesize_unless_simple(n.expr)

	def visit_ExprList(self, n):
		visited_subexprs = []
		for expr in n.exprs:
			visited_subexprs.append(self._visit_expr(expr))
		return ', '.join(visited_subexprs)

	def visit_InitList(self, n):
		visited_subexprs = []
		for expr in n.exprs:
			visited_subexprs.append(self._visit_expr(expr))
		return ', '.join(visited_subexprs)

	def visit_Enum(self, n):
		s = 'enum'
		if n.name: s += ' ' + n.name
		if n.values:
			s += ' {'
			for i, enumerator in enumerate(n.values.enumerators):
				s += enumerator.name
				if enumerator.value:
					s += ' = ' + self.visit(enumerator.value)
				if i != len(n.values.enumerators) - 1:
					s += ', '
			s += '}'
		return s

	def visit_FuncDef(self, n):  # add

		decl = self.visit(n.decl)
		self.currentFun = n.decl.name # 用来暂存当前访问的函数名


		if self.name() == "instrumenter":  # 处理单变量访问序  访问每个函数时初始化编号和赋值语句
			
			self.subscript = '' # 检测数组时 存储可能的读写的下标

			if n.decl.name in self.randomFunc:
							
				self.curThreadNum = str(self.randomFunc[n.decl.name].index)

				if not self.variable_is_pointer():

					if self.mode == 'rww':
						
						# self.curThreadNum = str(self.randomFunc[n.decl.name].index)

						variable_tmp = self.variable if self.index == '' else self.variable + '[' + self.index + ']' 

						self.addStatement_list = [self.mode, '_', 'r_tmp', str(self.curThreadNum), ' = ', variable_tmp, '; //add\n']
						self.addStatement = ''.join(self.addStatement_list)
						self.pre_addStatement = '' # 用来存储上一个addStatement 碰到连续读写时用
					elif self.mode == 'wwr':
						
						#self.curThreadNum = str(self.randomFunc[n.decl.name].index)

						variable_tmp = self.variable if self.index == '' else self.variable + '[' + self.index + ']' 

						self.addStatement_list = [self.mode, '_', 'w_tmp', str(self.curThreadNum), ' = ', variable_tmp, '; //add\n']
						self.addStatement = ''.join(self.addStatement_list)
						self.pre_addStatement = '' # 用来存储上一个addStatement 碰到连续读写时用

						# print(self.addStatement)
					elif self.mode == 'rwr':
						
						# self.curThreadNum = str(self.randomFunc[n.decl.name].index)

						variable_tmp = self.variable if self.index == '' else self.variable + '[' + self.index + ']' 

						self.addStatement_list = [self.mode, '_', 'r', str(self.assertNumber), ' = ', variable_tmp, '; //add\n']
						self.addStatement = ''.join(self.addStatement_list)
										
					elif self.mode == 'wrw':
					
						# self.curThreadNum = str(self.randomFunc[n.decl.name].index)
						
						curThreadPrio = self.randomFunc[n.decl.name].prio

						self.lowPrioThreadNums = []
						for func in self.randomFunc:
							if self.randomFunc[func].prio < curThreadPrio:
								self.lowPrioThreadNums.append(str(self.randomFunc[func].index))

				# add by wuyf
				# 把addStatement改成dict类型：addStatement = {variable1:'xxxxxxx', variable2:'xxxxxxx'}, addStatement_dict = {varaible1:['xxx','xxx','xxx']......}
				else:
					self.addStatement_dict = {}
					self.addStatement = {}
					self.pre_addStatement = {}

					if self.mode == 'rww':

						for variable in self.variable_list:
							# self.curThreadNum = str(self.randomFunc[n.decl.name].index)

							variable_tmp = variable if self.index == '' else variable + '[' + self.index + ']' 

							self.addStatement_dict[variable] = [self.mode, '_', 'r_tmp', variable, '_', str(self.curThreadNum), ' = ', variable_tmp, '; //add\n']
							self.addStatement[variable] = ''.join(self.addStatement_dict[variable])
							self.pre_addStatement[variable] = '' # 用来存储上一个addStatement 碰到连续读写时用
					elif self.mode == 'wwr':
						
						for variable in self.variable_list:
							#self.curThreadNum = str(self.randomFunc[n.decl.name].index)

							variable_tmp = variable if self.index == '' else variable + '[' + self.index + ']' 

							self.addStatement_dict[variable] = [self.mode, '_', 'w_tmp', variable, '_', str(self.curThreadNum), ' = ', variable_tmp, '; //add\n']
							self.addStatement[variable] = ''.join(self.addStatement_dict[variable])
							# print(''.join(self.addStatement_dict[variable]))
							self.pre_addStatement[variable] = '' # 用来存储上一个addStatement 碰到连续读写时用

						# print(self.addStatement)
					elif self.mode == 'rwr':
						
						for variable in self.variable_list:
							# self.curThreadNum = str(self.randomFunc[n.decl.name].index)

							variable_tmp = variable if self.index == '' else variable + '[' + self.index + ']' 

							self.addStatement_dict[variable] = [self.mode, '_', 'r', variable, '_', str(self.assertNumber), ' = ', variable_tmp, '; //add\n']
							self.addStatement[variable] = ''.join(self.addStatement_dict[variable])
										
					elif self.mode == 'wrw':
					
						# self.curThreadNum = str(self.randomFunc[n.decl.name].index)
						
						curThreadPrio = self.randomFunc[n.decl.name].prio

						self.lowPrioThreadNums = []
						for func in self.randomFunc:
							if self.randomFunc[func].prio < curThreadPrio:
								self.lowPrioThreadNums.append(str(self.randomFunc[func].index))
				


		if self.name()=="instrumenter" and n.decl.name == 'main_thread': # and self.mode not in ['rww', 'wwr', 'rwr', 'wrw']
			# 若只检测单变量访问序 则用visit_compound 同visit_compound的第一个判断
			# print("c_generator.func_visit_FuncDef:get in main_thread")
			self.indent_level = 0

			body = self.visit_mainThreadBody(n.body)  # 

		elif self.name()=="instrumenter" and n.decl.name == 'main_task_0': 
			# 若只检测单变量访问序 则用visit_compound 同visit_compound的第一个判断
			self.indent_level = 0

			body = self.visit_mainTaskBody(n.body)


		else:
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
			elif isinstance(ext, c_ast.Pragma):
				s += self.visit(ext) + '\n'
			else:
				s += self.visit(ext) + ';\n'
		return s

	def find_pointer(self, stmt):	# add by wuyf 查找所有指向变量的指针
		if not self.variable_is_pointer():
			if type(stmt)  == c_ast.Assignment :
				if type(stmt.rvalue) == c_ast.UnaryOp:
					#  x = & variable 
					if type(stmt.rvalue.expr) == c_ast.ID:
						if stmt.rvalue.op == '&' and stmt.rvalue.expr.name == self.variable:
							if stmt.lvalue.name not in self.pointer_list[self.variable]:		
								self.pointer_list[self.variable].append(stmt.lvalue.name)
								return True

				for t in self.pointer_list[self.variable]:
					# int* y
					# y = x
					if type(stmt.rvalue) == c_ast.ID:
						if stmt.rvalue.name == t:
							if stmt.lvalue.name not in self.pointer_list[self.variable]:
								self.pointer_list[self.variable].append(stmt.lvalue.name)
								return True					
			return False
		else:
			if self.variable_list:
				for variable in self.variable_list:
					if type(stmt)  == c_ast.Assignment and variable != self.variable:  # 指针本身除外
						if type(stmt.rvalue) == c_ast.UnaryOp:
							#  x = & variable 
							if type(stmt.rvalue.expr) == c_ast.ID:
								if stmt.rvalue.op == '&' and stmt.rvalue.expr.name == variable:
									if stmt.lvalue.name not in self.pointer_list[variable]:		
										self.pointer_list[variable].append(stmt.lvalue.name)
										return True

						for t in self.pointer_list[variable]:
							# int* y
							# y = x
							if type(stmt.rvalue) == c_ast.ID:
								if stmt.rvalue.name == t:
									if stmt.lvalue.name not in self.pointer_list[variable]:
										self.pointer_list[variable].append(stmt.lvalue.name)
										return True					
			return False
	
	def pointer_wr(self, stmt):		# add by wuyf 判断该语句中是否存在指针的读写
		
		if type(stmt)  == c_ast.Assignment:
				if type(stmt.rvalue) == c_ast.UnaryOp and stmt.rvalue.op == '*':
					if type(stmt.rvalue.expr) == c_ast.ID:
						#  = *pointer				
						return stmt.rvalue.expr.name

				if type(stmt.lvalue) == c_ast.UnaryOp and stmt.lvalue.op == '*':
					if type(stmt.lvalue.expr) == c_ast.ID:
						# *pointer = 
						return stmt.lvalue.expr.name
		
		return None
	
	def find_read(self, stmt, variable):  # 查找关于变量的读	

			# variable = self.variable

			if type(stmt)  == c_ast.TernaryOp:
				if type(stmt.iftrue) == c_ast.ID:
					if stmt.iftrue.name == variable:
						# m == 1 ? globalVar : 1
						return True
				if type(stmt.iffalse) == c_ast.ID:
					if stmt.iffalse.name == variable:
						# m == 1 ? 1 : globalVar
						return True	
				if type(stmt.iftrue) == c_ast.BinaryOp:
					if type(stmt.iftrue.left) == c_ast.ID:
						if stmt.iftrue.left.name == variable:
							# m == 1 ? globalVar+1 : 1
							return True
				if type(stmt.iffalse) == c_ast.BinaryOp:
					if type(stmt.iffalse.left) == c_ast.ID:
						if stmt.iffalse.left.name == variable:
							# m == 1 ? 1 : globalVar+1
							return True	

			if type(stmt)  == c_ast.If:
				if type(stmt.cond) == c_ast.UnaryOp:
					if type(stmt.cond.expr) == c_ast.BinaryOp :
						if type(stmt.cond.expr.left) == c_ast.ID:
							if stmt.cond.expr.left.name == variable:
								# if(variable > )
								return True
						if type(stmt.cond.expr.right) == c_ast.ID:
							if stmt.cond.expr.right.name == variable:
								# if( > variable)
								return True
						
						if type(stmt.cond.expr.left) == c_ast.BinaryOp:						
							if type(stmt.cond.expr.left.left) == c_ast.ID:
								if stmt.cond.expr.left.left.name == variable:
									# if(variable > x) && ()
									return True
							if type(stmt.cond.expr.left.right) == c_ast.ID:							
								if stmt.rvalue.left.right.name == variable:
									# if(x > variable) && ()								
									return True	
						if type(stmt.cond.expr.right) == c_ast.BinaryOp:
							if type(stmt.cond.expr.right.left) == c_ast.ID:
								if stmt.cond.expr.right.left.name == variable:
									# if() && (variable > x)
									return True
							if type(stmt.cond.expr.right.right) == c_ast.ID:
								if stmt.cond.expr.right.right.name == variable:
									# if() && (x > variable)
									return True
			'''
			if type(stmt)  == c_ast.UnaryOp :
				if type(stmt.expr) == c_ast.ID:
					if stmt.expr.name == variable:
						# variable++ 好像不认为是读
						return True
			'''
			if type(stmt)  == c_ast.Assignment :

				# add by wuyf
				if type(stmt.rvalue) == c_ast.UnaryOp:
					for t in self.pointer_list[variable]:
						if stmt.rvalue.op == '*' and stmt.rvalue.expr.name == t:
							#  = *pointer
							return True

					'''
					= variable++ 是否需要拆分
					'''					
					if stmt.rvalue.op in ['p++', 'p--', '*']:
						if type(stmt.rvalue.expr) == c_ast.ID:
							if stmt.rvalue.expr.name == variable:
								# = variable++
								# = *variable
								return True

				if type(stmt.rvalue) == c_ast.ID:
					if stmt.rvalue.name == variable and self.index == '': # a是数组时 p = a不算对某个单元读 
						# = variable						
						return True
				
				if type(stmt.lvalue) == c_ast.UnaryOp:
					if stmt.lvalue.op in ['*']:
						if type(stmt.lvalue.expr) == c_ast.ID:
							if stmt.lvalue.expr.name == variable:
								# *variable =
								return True

				if type(stmt.lvalue) == c_ast.ArrayRef and type(stmt.lvalue.subscript) == c_ast.ID:
					if stmt.lvalue.subscript.name == variable:
						# a[variable] =  
						return True

				if type(stmt.rvalue) == c_ast.ArrayRef :

					if type(stmt.rvalue.name) == c_ast.ID and type(stmt.rvalue.subscript) == c_ast.ID: #可能的读
						if stmt.rvalue.name.name == variable:
							# = variable[i]
							self.subscript = stmt.rvalue.subscript.name
							return True

					if type(stmt.rvalue.name) == c_ast.ID and type(stmt.rvalue.subscript) == c_ast.BinaryOp: #可能的读
						if stmt.rvalue.name.name == variable:
							# = variable[x+y]
							self.subscript = '(' + self.visit(stmt.rvalue.subscript) + ')'
							return True

					if type(stmt.rvalue.name) == c_ast.ID and type(stmt.rvalue.subscript) == c_ast.Constant:
						if stmt.rvalue.name.name == variable and str(stmt.rvalue.subscript.value) == self.index:
							# = variable[index]
							return True
					if type(stmt.rvalue.subscript) == c_ast.ID:
						if stmt.rvalue.subscript.name == variable:
							# = a[variable]
							return True

				if type(stmt.rvalue) == c_ast.StructRef:
					# 可能是 union.field  struct.field 两种 
					# 若variable是 union 或struct名 则只需要 union 或struct相同  
					# 若variable是 union.field 则只需要 union相同
					# 若variable是 struct.field 则需要 struct field相同

					if type(stmt.rvalue.name) == c_ast.ID:
						if stmt.rvalue.name.name == variable: # 只要结构体名相同就算读
							# 结构体 如 = variable.field
							return True
					
				

				if type(stmt.rvalue)  == c_ast.TernaryOp:
					if type(stmt.rvalue.iftrue) == c_ast.ID:
						if stmt.rvalue.iftrue.name == variable:
							# =m == 1 ? globalVar : 1
							return True
					if type(stmt.rvalue.iffalse) == c_ast.ID:
						if stmt.rvalue.iffalse.name == variable:
							# =m == 1 ? 1 : globalVar
							return True	
					if type(stmt.rvalue.iftrue) == c_ast.BinaryOp:
						if type(stmt.rvalue.iftrue.left) == c_ast.ID:
							if stmt.rvalue.iftrue.left.name == variable:
								# =m == 1 ? globalVar+1 : 1
								return True
					if type(stmt.rvalue.iffalse) == c_ast.BinaryOp:
						if type(stmt.rvalue.iffalse.left) == c_ast.ID:
							if stmt.rvalue.iffalse.left.name == variable:
								# =m == 1 ? 1 : globalVar+1
								return True	

				if type(stmt.rvalue)  == c_ast.BinaryOp:
					if type(stmt.rvalue.left) == c_ast.ArrayRef :
						if type(stmt.rvalue.left.name) == c_ast.ID and type(stmt.rvalue.left.subscript) == c_ast.ID: #可能的读
							if stmt.rvalue.left.name.name == variable:
								# = variable[i] * y
								self.subscript = stmt.rvalue.left.subscript.name
								return True
						if type(stmt.rvalue.left.name) == c_ast.ID and type(stmt.rvalue.left.subscript) == c_ast.Constant:
							if stmt.rvalue.left.name.name == variable and str(stmt.rvalue.left.subscript.value) == self.index:
								# = variable[index] * y
								return True
					if type(stmt.rvalue.right) == c_ast.ArrayRef :
						if type(stmt.rvalue.right.name) == c_ast.ID and type(stmt.rvalue.right.subscript) == c_ast.ID: #可能的读
							if stmt.rvalue.right.name.name == variable:
								# = y * variable[i] 
								self.subscript = stmt.rvalue.right.subscript.name
								return True
						if type(stmt.rvalue.right.name) == c_ast.ID and type(stmt.rvalue.right.subscript) == c_ast.Constant:
							if stmt.rvalue.right.name.name == variable and str(stmt.rvalue.right.subscript.value) == self.index:
								# = y * variable[index] 
								return True

					if type(stmt.rvalue.left) == c_ast.ID:
						if stmt.rvalue.left.name == variable:
							# = variable >= 12
							return True

					if type(stmt.rvalue.right) == c_ast.ID:
						if stmt.rvalue.right.name == variable:
							# = 12 <= variable 
							return True

					if type(stmt.rvalue.left) == c_ast.BinaryOp:						
						if type(stmt.rvalue.left.left) == c_ast.ID:
							if stmt.rvalue.left.left.name == variable:
								# =(variable > x) && ()
								return True
						if type(stmt.rvalue.left.right) == c_ast.ID:							
							if stmt.rvalue.left.right.name == variable:
								# =(x > variable) && ()								
								return True	
					if type(stmt.rvalue.right) == c_ast.BinaryOp:
						if type(stmt.rvalue.right.left) == c_ast.ID:
							if stmt.rvalue.right.left.name == variable:
								# =() && (variable > x)
								return True
						if type(stmt.rvalue.right.right) == c_ast.ID:
							if stmt.rvalue.right.right.name == variable:
								# =() && (x > variable)
								return True


			return False

	def find_write(self, stmt, variable):  # 查找关于变量的写

		# variable = self.variable

		'''
		variable++ 是否需要拆分
		'''
		if type(stmt)  == c_ast.UnaryOp :
			if type(stmt.expr) == c_ast.ID:
				if stmt.expr.name == variable:
					# variable++
					return True

		if type(stmt)  == c_ast.Assignment :

			# add by wuyf
			if type(stmt.lvalue) == c_ast.UnaryOp:
				for t in self.pointer_list[variable]:
					if stmt.lvalue.op == '*' and stmt.lvalue.expr.name == t:
						# *pointer =
						return True

			if type(stmt.lvalue) == c_ast.ID:
				if stmt.lvalue.name == variable and self.index == '': # a b是数组时 a = b不算对某个单元写 
					# variable = 					
					return True
			'''
			= variable++ 是否需要拆分
			'''
			if type(stmt.rvalue)  == c_ast.UnaryOp :
				if stmt.rvalue.op in ['p++', 'p--']:
					if type(stmt.rvalue.expr) == c_ast.ID:
						if stmt.rvalue.expr.name == variable:
							# = variable++
							return True

			if type(stmt.lvalue) == c_ast.ArrayRef:
			    # print(stmt.lvalue.name.name)
				# print(self.variable)

				if type(stmt.lvalue.name) == c_ast.ID and type(stmt.lvalue.subscript) == c_ast.ID: #可能的写
					if stmt.lvalue.name.name == variable:
						# variable[i] =
						self.subscript = stmt.lvalue.subscript.name
						return True
				if type(stmt.lvalue.name) == c_ast.ID and type(stmt.lvalue.subscript) == c_ast.Constant:
					# print(stmt.lvalue.name.name)
					# print(stmt.lvalue.subscript)

					if stmt.lvalue.name.name == variable and str(stmt.lvalue.subscript.value) == self.index: 
						# variable[index] =						
						return True

			if type(stmt.lvalue) == c_ast.StructRef:
				if type(stmt.lvalue.name) == c_ast.ID:
					if stmt.lvalue.name.name == variable: # 只要结构体名相同就算写
						# 结构体 如 variable.field = 
						return True

				

		return False


	def variable_is_pointer(self):	# 判断单变量访问序的变量类型是否为指针
		if self.name() == "instrumenter" or self.name() == "lazyseq":
			if self.mode in ['rww', 'wwr', 'rwr', 'wrw']:
				if self.type.rstrip()[-1] == '*': 
					return True 
				else: 
					return False

	def find_variable(self, stmt):	# 查找语句中是否存在指针指向新变量（用于lazyseq模块）
		if self.name() == "lazyseq":
			if self.variable_is_pointer():
				if type(stmt)  == c_ast.Assignment :
					if type(stmt.rvalue) == c_ast.UnaryOp and type(stmt.lvalue) == c_ast.ID:
						#  variable = & a1
						if type(stmt.rvalue.expr) == c_ast.ID:
							if stmt.rvalue.op == '&' and stmt.lvalue.name == self.variable:
								if stmt.rvalue.expr.name not in self.variable_list:		
									self.variable_list.append(stmt.rvalue.expr.name)
		# 有多种为指针赋值的可能性 例如 variable(指针) = 某指针（无法处理)


	# add by wuyf 处理带检测变量为指针的情况
	def deal_with_svp_pointer(self, stmt):
		s = ''

		self.find_pointer(stmt)
		pointer_wr = self.pointer_wr(stmt)

		# 处理单变量访问序
		if self.currentFun in self.randomFunc and self.randomFunc[self.currentFun].prio == self.highestPrio and self.mode != 'wrw':
			# 若是 最高优先级的中断 则不需要进行读写检测 wrw模式除外
			return ''.join(self._generate_stmt(stmt))	 


		cnt = 0
		for variable in self.variable_list:
			cnt +=1

			if self.mode == 'rww':                

				if self.find_read(stmt, variable) == True:  # R
					s += ''.join(self._generate_stmt(stmt)) if cnt == 1 else ''

					# add by wuyf
					if pointer_wr and pointer_wr in self.pointer_list[variable]:	# 
						s += '\n' + ' ' * 18 + 'if(%s == __cs_variable_address_list[%s]) {'% (pointer_wr, self.variable_list.index(variable))


					if self.addStatement[variable].find('rww_r_tmp') != -1:
						
						if self.subscript != '':
							s += '\n'
							s += ' ' * 20 + 'if(' + self.subscript + ' == ' + self.index + '){  //add\n'
							s += ' ' * 20 + '	 rww_r_tmp' + variable + '_' + str(self.curThreadNum) + '_num++; \n'
							s += ' ' * 20 + '	 ' + self.addStatement[variable]
							s += ' ' * 20 + '}\n\n'
							self.subscript = ''
						else:
							s += '\n'
							s += ' ' * 20 + 'rww_r_tmp' + variable + '_' + str(self.curThreadNum) + '_num++; //add\n'
							s += ' ' * 20 + self.addStatement[variable]
							s += '\n'  

						self.pre_addStatement[variable] = self.addStatement[variable]
						self.addStatement_dict[variable][2] = 'w' 
						self.addStatement_dict[variable][5] = str(self.assertNumber)
						self.addStatement[variable] = ''.join(self.addStatement_dict[variable])
						
					elif self.addStatement[variable].find('rww_w') != -1:

						if self.subscript != '':
							s += '\n'
							s += ' ' * 20 + 'if(' + self.subscript + ' == ' + self.index + '){  //add\n'
							s += ' ' * 20 + ' 	 rww_r_tmp' + variable + '_' + str(self.curThreadNum) + '_num++; \n'
							s += ' ' * 20 + '	 ' + self.pre_addStatement[variable]
							s += ' ' * 20 + '}\n\n'
							self.subscript = ''
						else:
							s += '\n'
							s += ' ' * 20 + 'rww_r_tmp' + variable + '_' + str(self.curThreadNum) + '_num++; //add\n'
							s += ' ' * 20 + self.pre_addStatement[variable]
							s += '\n'
					

					# add by wuyf
					if pointer_wr and pointer_wr in self.pointer_list[variable]:	#
						s += '\n' + ' ' * 18 + '}\n'

				elif self.find_write(stmt, variable) == True: # W
					# s += ''.join(self._generate_stmt(stmt))  # rww的w不能先输出语句
					
					# add by wuyf
					if pointer_wr and pointer_wr in self.pointer_list[variable]:	#
						s += '\n' + ' ' * 18 + 'if(%s == __cs_variable_address_list[%s]) {'% (pointer_wr, self.variable_list.index(variable))

					if self.addStatement[variable].find('rww_r_tmp') != -1 and self.assertNumber != 1: # 防止函数一开始先检测w
						
						if self.subscript != '':
							s += '\n'
							s += ' ' * 20 + 'if(' + self.subscript + ' == ' + self.index + '){  //add\n'
							s += ' ' * 20 + '	 ' + self.pre_addStatement[variable]
							s += ' ' * 20 + '	 if(rww_r_tmp' + variable + '_' + str(self.curThreadNum) + '_num != 0){\n' 
							s += ' ' * 20 + '	 	 assert(rww_' + variable + '_' + str(self.assertNumber-1) + '==rww_r_tmp' + variable + '_' + str(self.curThreadNum) + ');\n'
							s += ' ' * 20 + '	 	 rww_r_tmp' + variable + '_' + str(self.curThreadNum) + '_num = 0;\n'
							s += ' ' * 20 + '	 }\n'	
							s += ' ' * 20 + '}\n\n'
							self.subscript = ''
						else:		
							s += '\n'						
							s += ' ' * 20 + self.pre_addStatement[variable]
							s += ' ' * 20 + 'if(rww_r_tmp' + variable + '_' + str(self.curThreadNum) + '_num != 0){\n' # 约束反例 必须是有rww_r_tmp的赋值
							s += ' ' * 20 + '	 assert(rww_w' + variable + '_' + str(self.assertNumber-1) + '==rww_r_tmp' + variable + '_' + str(self.curThreadNum) + ');\n'
							s += ' ' * 20 + '	 rww_r_tmp' + variable + '_' + str(self.curThreadNum) + '_num = 0;\n' # 去除后续的多余反例
							s += ' ' * 20 + '}\n\n'				
							
					elif self.addStatement[variable].find('rww_w') != -1: 

						if self.subscript != '':
							s += '\n'
							s += ' ' * 20 + 'if(' + self.subscript + ' == ' + self.index + '){  //add\n'
							s += ' ' * 20 + '	 ' +self.addStatement[variable]
							s += ' ' * 20 + '	 if(rww_r_tmp' + variable + '_' + str(self.curThreadNum) + '_num != 0){\n'
							s += ' ' * 20 + '	 	 assert(rww_w' + variable + '_' + str(self.assertNumber) + '==rww_r_tmp' + variable + '_' + str(self.curThreadNum) + ');\n'
							s += ' ' * 20 + '	 	 rww_r_tmp' + variable + '_' + str(self.curThreadNum) + '_num = 0;\n'
							s += ' ' * 20 + '	 }\n'	
							s += ' ' * 20 + '}\n\n'
							self.subscript = ''
						else:	
							s += '\n'			
							s += ' ' * 20 + self.addStatement[variable] 
							s += ' ' * 20 + 'if(rww_r_tmp' + variable + '_' + str(self.curThreadNum) + '_num != 0){\n' # 约束反例 必须是有wwr_W_tmp的赋值
							s += ' ' * 20 + '	 assert(rww_w' + variable + '_' + str(self.assertNumber) + '==rww_r_tmp' + variable + '_' + str(self.curThreadNum) + ');\n'
							s += ' ' * 20 + '	 rww_r_tmp' + variable + '_' + str(self.curThreadNum) + '_num = 0;\n'
							s += ' ' * 20 + '}\n\n'		

						self.assertNumber += 1

						self.pre_addStatement[variable] = self.addStatement[variable]
						self.addStatement_dict[variable][5] = str(self.curThreadNum) 
						self.addStatement_dict[variable][2] = 'r_tmp'
						self.addStatement[variable] = ''.join(self.addStatement_dict[variable])

					# add by wuyf
					if pointer_wr and pointer_wr in self.pointer_list[variable]:	#
						s += '\n' + ' ' * 18 + '}\n'

					s += ''.join(self._generate_stmt(stmt)) if cnt == 1 else ''

				else:
					s += ''.join(self._generate_stmt(stmt)) if cnt == 1 else ''

			elif self.mode == 'wwr':
				
				if self.find_write(stmt, variable) == True:  # W
					s += ''.join(self._generate_stmt(stmt)) if cnt == 1 else ''

					# add by wuyf
					if pointer_wr and pointer_wr in self.pointer_list[variable]:	#
						s += '\n' + ' ' * 18 + 'if(%s == __cs_variable_address_list[%s]) {'% (pointer_wr, self.variable_list.index(variable))


					if self.addStatement[variable].find('wwr_w_tmp') != -1:
						
						if self.subscript != '':
							s += '\n'
							s += ' ' * 20 + 'if(' + self.subscript + ' == ' + self.index + '){  //add\n'
							s += ' ' * 20 + '	 wwr_w_tmp' + variable + '_' + str(self.curThreadNum) + '_num++; \n'
							s += ' ' * 20 + '	 ' + self.addStatement[variable]   
							s += ' ' * 20 + '}\n\n'
							self.subscript = ''
						else:
							s += '\n'
							s += ' ' * 20 + 'wwr_w_tmp' + variable + '_' + str(self.curThreadNum) + '_num++; //add\n'
							s += ' ' * 20 + self.addStatement[variable]  
							s += '\n'  

						self.pre_addStatement[variable] = self.addStatement[variable]
						self.addStatement_dict[variable][2] = 'r' 
						self.addStatement_dict[variable][5] = str(self.assertNumber)
						self.addStatement[variable] = ''.join(self.addStatement_dict[variable])
												
					elif self.addStatement[variable].find('wwr_r') != -1:

						if self.subscript != '':
							s += '\n'
							s += ' ' * 20 + 'if(' + self.subscript + ' == ' + self.index + '){  //add\n'
							s += ' ' * 20 + ' 	 wwr_w_tmp' + variable + '_' + str(self.curThreadNum) + '_num++; \n'
							s += ' ' * 20 + '	 ' + self.pre_addStatement[variable]  
							s += ' ' * 20 + '}\n\n'
							self.subscript = ''
						else:
							s += '\n'
							s += ' ' * 20 + 'wwr_w_tmp' + variable + '_' + str(self.curThreadNum) + '_num++; //add\n'
							s += ' ' * 20 + self.pre_addStatement[variable]   
							s += '\n'
					
					# add by wuyf
					if pointer_wr and pointer_wr in self.pointer_list[variable]:	#
						s += '\n' + ' ' * 18 + '}\n'
				
				elif self.find_read(stmt, variable) == True: # R
					s += ''.join(self._generate_stmt(stmt)) if cnt == 1 else ''  # 先输出读 方便反例查看

					# add by wuyf
					if pointer_wr and pointer_wr in self.pointer_list[variable]:	#
						s += '\n' + ' ' * 18 + 'if(%s == __cs_variable_address_list[%s]) {'% (pointer_wr, self.variable_list.index(variable))

					if self.addStatement[variable].find('wwr_w_tmp') != -1 and self.assertNumber != 1: # 防止函数一开始先检测r
						
						if self.subscript != '':
							s += '\n'
							s += ' ' * 20 + 'if(' + self.subscript + ' == ' + self.index + '){  //add\n'
							s += ' ' * 20 + '	 ' + self.pre_addStatement[variable]
							s += ' ' * 20 + '	 if(wwr_w_tmp' + variable + '_' + str(self.curThreadNum) + '_num != 0){\n' 
							s += ' ' * 20 + '	 	 assert(wwr_r' + variable + '_' + str(self.assertNumber-1) + '==wwr_w_tmp' + variable + '_' + str(self.curThreadNum) + ');\n'
							s += ' ' * 20 + '	 	 wwr_w_tmp' + variable + '_' + str(self.curThreadNum) + '_num = 0;\n' # 去除后续的多余反例
							s += ' ' * 20 + '	 }\n'									
							s += ' ' * 20 + '}\n\n'
							self.subscript = ''
						else:		
							s += '\n'						
							s += ' ' * 20 + self.pre_addStatement[variable]
							s += ' ' * 20 + 'if(wwr_w_tmp' + variable + '_' + str(self.curThreadNum) + '_num != 0){\n' # 约束反例 必须是有wwr_W_tmp的赋值
							s += ' ' * 20 + '	 assert(wwr_r' + variable + '_' + str(self.assertNumber-1) + '==wwr_w_tmp' + variable + '_' + str(self.curThreadNum) + ');\n'
							s += ' ' * 20 + '	 wwr_w_tmp' + variable + '_' + str(self.curThreadNum) + '_num = 0;\n' # 去除后续的多余反例
							s += ' ' * 20 + '}\n\n'	
										
							
					elif self.addStatement[variable].find('wwr_r') != -1: 

						if self.subscript != '':
							s += '\n'
							s += ' ' * 20 + 'if(' + self.subscript + ' == ' + self.index + '){  //add\n'
							s += ' ' * 20 + '	 ' +self.addStatement[variable] 
							s += ' ' * 20 + '	 if(wwr_w_tmp' + variable + '_' + str(self.curThreadNum) + '_num != 0){\n'
							s += ' ' * 20 + '	 	 assert(wwr_r' + variable + '_' + str(self.assertNumber) + '==wwr_w_tmp' + variable + '_' + str(self.curThreadNum) + ');\n'
							s += ' ' * 20 + '		 wwr_w_tmp' + variable + '_' + str(self.curThreadNum) + '_num = 0;\n' # 去除后续的多余反例
							s += ' ' * 20 + '	 }\n'	
							s += ' ' * 20 + '}\n\n'
							self.subscript = ''
						else:	
							s += '\n'			
							s += ' ' * 20 + self.addStatement[variable] 
							s += ' ' * 20 + 'if(wwr_w_tmp' + variable + '_' + str(self.curThreadNum) + '_num != 0){\n' # 约束反例 必须是有wwr_W_tmp的赋值
							s += ' ' * 20 + '	 assert(wwr_r' + variable + '_' + str(self.assertNumber) + '==wwr_w_tmp' + variable + '_' + str(self.curThreadNum) + ');\n'
							s += ' ' * 20 + '	 wwr_w_tmp' + variable + '_' + str(self.curThreadNum) + '_num = 0;\n' # 去除后续的多余反例
							s += ' ' * 20 + '}\n\n'		

						self.assertNumber += 1

						self.pre_addStatement[variable] = self.addStatement[variable]
						self.addStatement_dict[variable][5] = str(self.curThreadNum) 
						self.addStatement_dict[variable][2] = 'w_tmp'
						self.addStatement[variable] = ''.join(self.addStatement_dict[variable])

					# add by wuyf
					if pointer_wr and pointer_wr in self.pointer_list[variable]:	#
						s += '\n' + ' ' * 18 + '}\n'

				else:
					s += ''.join(self._generate_stmt(stmt)) if cnt == 1 else ''
	
			elif self.mode == 'rwr':
				# 搜索r

				if self.find_write(stmt, variable) == True and self.assertNumber != 1:
					s += ''.join(self._generate_stmt(stmt)) if cnt == 1 else ''

					# add by wuyf
					if pointer_wr and pointer_wr in self.pointer_list[variable]:	#
						s += '\n' + ' ' * 18 + 'if(%s == __cs_variable_address_list[%s]) {'% (pointer_wr, self.variable_list.index(variable))

					if self.subscript != '':
						s += '\n'
						s += ' ' * 20 + 'if(' + self.subscript + ' == ' + self.index + '){  //add\n'
						s += ' ' * 20 + '	 rwr_tmp' + variable + '_' + str(self.curThreadNum) + '_num = 0; //add\n\n'
						s += ' ' * 20 + '}\n\n'
						self.subscript = ''
					else:
						s += '\n' 
						s += ' ' * 20 + 'rwr_tmp' + variable + '_' + str(self.curThreadNum) + '_num = 0; //add\n\n'
					
					# add by wuyf
					if pointer_wr and pointer_wr in self.pointer_list[variable]:	#
						s += '\n' + ' ' * 18 + '}\n'
				
				elif self.find_read(stmt, variable) == True:
					s += ''.join(self._generate_stmt(stmt)) if cnt == 1 else ''

					# add by wuyf
					if pointer_wr and pointer_wr in self.pointer_list[variable]:	#
						s += '\n' + ' ' * 18 + 'if(%s == __cs_variable_address_list[%s]) {'% (pointer_wr, self.variable_list.index(variable))

					if self.subscript != '':
						s += '\n'
						s += ' ' * 20 + 'if(' + self.subscript + ' == ' + self.index + '){  //add\n'
						s += ' ' * 20 + '	 ' + self.addStatement[variable]
						s += ' ' * 20 + '	 if(rwr_tmp' + variable + '_' + str(self.curThreadNum) + '_num != 0){  //add\n'
						s += ' ' * 20 + '	 	 assert(rwr_r' + variable + '_' + str(self.assertNumber) + ' == rwr_tmp' + variable + '_' + str(self.curThreadNum) + ');\n'
						s += ' ' * 20 + '	 }\n'
						s += ' ' * 20 + '	 rwr_tmp' + variable + '_' + str(self.curThreadNum) + '_num++;\n'
						s += ' ' * 20 + '	 rwr_tmp' + variable + '_' + str(self.curThreadNum) + ' = rwr_r' + variable + '_' + str(self.assertNumber) + '; \n'
						s += ' ' * 20 + '}\n\n'
						self.subscript = ''

					else:
						s += '\n' 
						s += ' ' * 20 + self.addStatement[variable]
						s += ' ' * 20 + 'if(rwr_tmp' + variable + '_' + str(self.curThreadNum) + '_num != 0){  //add\n'
						s += ' ' * 20 + '	 assert(rwr_r' + variable + '_' + str(self.assertNumber) + ' == rwr_tmp' + variable + '_' + str(self.curThreadNum) + ');\n'
						s += ' ' * 20 + '}\n'
						s += ' ' * 20 + 'rwr_tmp' + variable + '_' + str(self.curThreadNum) + '_num++;\n'
						s += ' ' * 20 + 'rwr_tmp' + variable + '_' + str(self.curThreadNum) + ' = rwr_r' + variable + '_' + str(self.assertNumber) + '; \n\n'

					self.assertNumber += 1
						
					self.addStatement_dict[variable][5] = str(self.assertNumber)  
					self.addStatement[variable] = ''.join(self.addStatement_dict[variable])

					# add by wuyf
					if pointer_wr and pointer_wr in self.pointer_list[variable]:	#
						s += '\n' + ' ' * 18 + '}\n'

				else:
					s += ''.join(self._generate_stmt(stmt)) if cnt == 1 else ''


				'''
				if self.find_read(stmt) == True:
					s += ' ' * 10 + self.addStatement 
					if self.firstInFunc == False :   # 由于序号问题 所断言内容不一定是 str(self.assertNumber - 1)
						s += ' ' * 10 + 'assert(rwr_r' + str(self.assertNumber) + '==rwr_r' + str(self.assertNumber - 1) + '); //add \n'
					
					self.firstInFunc = False

					self.assertNumber += 1 
					self.assertNumberUsed = False
					self.addStatement_list[3] = str(self.assertNumber) 
					self.addStatement = ''.join(self.addStatement_list)

				s += ''.join(self._generate_stmt(stmt)) 
				'''
			# add 在wrw模式下 需要对高优先级线程里的r识别
			elif self.mode == 'wrw':

				if self.find_read(stmt, variable) == True and self.currentFun != 'main_task_0':
					s += ''.join(self._generate_stmt(stmt)) if cnt == 1 else ''

					# add by wuyf
					if pointer_wr and pointer_wr in self.pointer_list[variable]:	#
						s += '\n' + ' ' * 18 + 'if(%s == __cs_variable_address_list[%s]) {'% (pointer_wr, self.variable_list.index(variable))

					if self.subscript != '':
						s += '\n'
						s += ' ' * 20 + 'if(' + self.subscript + ' == ' + self.index + '){  //add\n'
						# s += ' ' * 20 + '	 wrw_a_' + self.curThreadNum + '_num = 0; //add\n'
						for lowPrioThreadNum in self.lowPrioThreadNums:
							s += ' ' * 20 + '	 wrw_a_' + variable + '_' + lowPrioThreadNum + ' = 1; //add\n'
						s += ' ' * 20 + '}\n\n'
						self.subscript = ''
					else:
						s += '\n' 
						# s += ' ' * 20 + 'wrw_a_' + self.curThreadNum + '_num = 0; //add\n' # wrw模式忽略w之间的r
						for lowPrioThreadNum in self.lowPrioThreadNums:
							s += ' ' * 20 + 'wrw_a_' + variable + '_' + lowPrioThreadNum + ' = 1; //add\n'
						s += '\n' 

					# add by wuyf
					if pointer_wr and pointer_wr in self.pointer_list[variable]:	#
						s += '\n' + ' ' * 18 + '}\n'

				elif self.find_write(stmt, variable) == True and self.randomFunc[self.currentFun].prio != self.highestPrio:
					s += ''.join(self._generate_stmt(stmt)) if cnt == 1 else ''

					# add by wuyf
					if pointer_wr and pointer_wr in self.pointer_list[variable]:	#
						s += '\n' + ' ' * 18 + 'if(%s == __cs_variable_address_list[%s]) {'% (pointer_wr, self.variable_list.index(variable))

					if self.subscript != '':
						s += '\n'
						s += ' ' * 20 + 'if(' + self.subscript + ' == ' + self.index + '){  //add\n'
						s += ' ' * 20 + '	 if(wrw_a_' + variable + '_' + self.curThreadNum + '_num != 0){  //add\n'
						s += ' ' * 20 + '	 	 assert(wrw_a_' + variable + '_' + self.curThreadNum + ' == 0);\n'
						s += ' ' * 20 + '	 }\n'
						s += ' ' * 20 + '	 wrw_a_' + variable + '_' + self.curThreadNum + '_num++;\n'
						s += ' ' * 20 + '	 wrw_a_' + variable + '_' + self.curThreadNum + ' = 0; \n\n'
						s += ' ' * 20 + '}\n\n'
						self.subscript = ''

					else:
						s += '\n' 
						s += ' ' * 20 + 'if(wrw_a_' + variable + '_' + self.curThreadNum + '_num != 0){  //add\n'
						s += ' ' * 20 + '	 assert(wrw_a_' + variable + '_' + self.curThreadNum + ' == 0);\n'
						s += ' ' * 20 + '}\n'
						s += ' ' * 20 + 'wrw_a_' + variable + '_' + self.curThreadNum + '_num++;\n'
						s += ' ' * 20 + 'wrw_a_' + variable + '_' + self.curThreadNum + ' = 0; \n\n'						

					# add by wuyf
					if pointer_wr and pointer_wr in self.pointer_list[variable]:	#
						s += '\n' + ' ' * 18 + '}\n'

				else:
					s += ''.join(self._generate_stmt(stmt)) if cnt == 1 else ''
			else:
				s += ''.join(self._generate_stmt(stmt)) if cnt == 1 else ''

		return s
	# add by wuyf 处理带检测变量为指针的情况


	def deal_with_svp(self, stmt):
		
		s = ''
		

		self.find_pointer(stmt)
		pointer_wr = self.pointer_wr(stmt)
		variable = self.variable

		# 处理单变量访问序
		if self.currentFun in self.randomFunc and self.randomFunc[self.currentFun].prio == self.highestPrio and self.mode != 'wrw':
			# 若是 最高优先级的中断 则不需要进行读写检测 wrw模式除外
			return ''.join(self._generate_stmt(stmt))	 
			
			
		if self.mode == 'rww':                

			if self.find_read(stmt, variable) == True:  # R
				s += ''.join(self._generate_stmt(stmt)) 

				# add by wuyf
				if pointer_wr and pointer_wr in self.pointer_list[variable]:
					s += '\n' + ' ' * 18 + 'if(%s == __cs_variable_address) {'% pointer_wr

				
				if self.addStatement.find('rww_r_tmp') != -1:
					
					if self.subscript != '':
						s += '\n'
						s += ' ' * 20 + 'if(' + self.subscript + ' == ' + self.index + '){  //add\n'
						s += ' ' * 20 + '	 rww_r_tmp' + str(self.curThreadNum) + '_num++; \n'
						s += ' ' * 20 + '	 ' + self.addStatement    
						s += ' ' * 20 + '}\n\n'
						# self.subscript = ''
					else:
						s += '\n'
						s += ' ' * 20 + 'rww_r_tmp' + str(self.curThreadNum) + '_num++; //add\n'
						s += ' ' * 20 + self.addStatement  
						s += '\n'  

					self.pre_addStatement = self.addStatement
					self.addStatement_list[2] = 'w' 
					self.addStatement_list[3] = str(self.assertNumber)
					self.addStatement = ''.join(self.addStatement_list)
					
				elif self.addStatement.find('rww_w') != -1:

					if self.subscript != '':
						s += '\n'
						s += ' ' * 20 + 'if(' + self.subscript + ' == ' + self.index + '){  //add\n'
						s += ' ' * 20 + ' 	 rww_r_tmp' + str(self.curThreadNum) + '_num++; \n'
						s += ' ' * 20 + '	 ' + self.pre_addStatement  
						s += ' ' * 20 + '}\n\n'
						# self.subscript = ''
					else:
						s += '\n'
						s += ' ' * 20 + 'rww_r_tmp' + str(self.curThreadNum) + '_num++; //add\n'
						s += ' ' * 20 + self.pre_addStatement   
						s += '\n'

				# add by wuyf
				if pointer_wr and pointer_wr in self.pointer_list[variable]:
					s += '\n' + ' ' * 18 + '}\n'

			elif self.find_write(stmt,variable) == True: # W
				# s += ''.join(self._generate_stmt(stmt))  # rww的w不能先输出语句
				
				# add by wuyf
				if pointer_wr and pointer_wr in self.pointer_list[variable]:
					s += '\n' + ' ' * 18 + 'if(%s == __cs_variable_address) {'% pointer_wr

				if self.addStatement.find('rww_r_tmp') != -1 and self.assertNumber != 1: # 防止函数一开始先检测w
					
					if self.subscript != '':
						s += '\n'
						s += ' ' * 20 + 'if(' + self.subscript + ' == ' + self.index + '){  //add\n'
						s += ' ' * 20 + '	 ' + self.pre_addStatement 
						s += ' ' * 20 + '	 if(rww_r_tmp' + str(self.curThreadNum) + '_num != 0){\n' 
						s += ' ' * 20 + '	 	 assert(rww_w' + str(self.assertNumber-1) + '==rww_r_tmp' + str(self.curThreadNum) + ');\n'
						s += ' ' * 20 + '	 	 rww_r_tmp' + str(self.curThreadNum) + '_num = 0;\n'
						s += ' ' * 20 + '	 }\n'	
						s += ' ' * 20 + '}\n\n'
						# self.subscript = ''
					else:		
						s += '\n'						
						s += ' ' * 20 + self.pre_addStatement
						s += ' ' * 20 + 'if(rww_r_tmp' + str(self.curThreadNum) + '_num != 0){\n' # 约束反例 必须是有rww_r_tmp的赋值
						s += ' ' * 20 + '	 assert(rww_w' + str(self.assertNumber-1) + '==rww_r_tmp' + str(self.curThreadNum) + ');\n'
						s += ' ' * 20 + '	 rww_r_tmp' + str(self.curThreadNum) + '_num = 0;\n' # 去除后续的多余反例
						s += ' ' * 20 + '}\n\n'				
						
				elif self.addStatement.find('rww_w') != -1: 

					if self.subscript != '':
						s += '\n'
						s += ' ' * 20 + 'if(' + self.subscript + ' == ' + self.index + '){  //add\n'
						s += ' ' * 20 + '	 ' +self.addStatement 
						s += ' ' * 20 + '	 if(rww_r_tmp' + str(self.curThreadNum) + '_num != 0){\n'
						s += ' ' * 20 + '	 	 assert(rww_w' + str(self.assertNumber) + '==rww_r_tmp' + str(self.curThreadNum) + ');\n'
						s += ' ' * 20 + '	 	 rww_r_tmp' + str(self.curThreadNum) + '_num = 0;\n'
						s += ' ' * 20 + '	 }\n'	
						s += ' ' * 20 + '}\n\n'
						# self.subscript = ''
					else:	
						s += '\n'			
						s += ' ' * 20 + self.addStatement 
						s += ' ' * 20 + 'if(rww_r_tmp' + str(self.curThreadNum) + '_num != 0){\n' # 约束反例 必须是有wwr_W_tmp的赋值
						s += ' ' * 20 + '	 assert(rww_w' + str(self.assertNumber) + '==rww_r_tmp' + str(self.curThreadNum) + ');\n'
						s += ' ' * 20 + '	 rww_r_tmp' + str(self.curThreadNum) + '_num = 0;\n'
						s += ' ' * 20 + '}\n\n'		

					self.assertNumber += 1

					self.pre_addStatement = self.addStatement
					self.addStatement_list[3] = str(self.curThreadNum) 
					self.addStatement_list[2] = 'r_tmp' 
					self.addStatement = ''.join(self.addStatement_list)

				# add by wuyf
				if pointer_wr and pointer_wr in self.pointer_list[variable]:
					s += '\n' + ' ' * 18 + '}\n'

				s += ''.join(self._generate_stmt(stmt))

			else:
				s += ''.join(self._generate_stmt(stmt)) 

			self.subscript = ''

		elif self.mode == 'wwr':
			
			if self.find_write(stmt, variable) == True:  # W
				s += ''.join(self._generate_stmt(stmt)) 

				# add by wuyf
				if pointer_wr and pointer_wr in self.pointer_list[variable]:
					s += '\n' + ' ' * 18 + 'if(%s == __cs_variable_address) {'% pointer_wr

				
				if self.addStatement.find('wwr_w_tmp') != -1:
					
					if self.subscript != '':
						s += '\n'
						s += ' ' * 20 + 'if(' + self.subscript + ' == ' + self.index + '){  //add\n'
						s += ' ' * 20 + '	 wwr_w_tmp' + str(self.curThreadNum) + '_num++; \n'
						s += ' ' * 20 + '	 ' + self.addStatement    
						s += ' ' * 20 + '}\n\n'
						# self.subscript = ''
					else:
						s += '\n'
						s += ' ' * 20 + 'wwr_w_tmp' + str(self.curThreadNum) + '_num++; //add\n'
						s += ' ' * 20 + self.addStatement  
						s += '\n'  

					self.pre_addStatement = self.addStatement
					self.addStatement_list[2] = 'r' 
					self.addStatement_list[3] = str(self.assertNumber)
					self.addStatement = ''.join(self.addStatement_list)
											
				elif self.addStatement.find('wwr_r') != -1:

					if self.subscript != '':
						s += '\n'
						s += ' ' * 20 + 'if(' + self.subscript + ' == ' + self.index + '){  //add\n'
						s += ' ' * 20 + ' 	 wwr_w_tmp' + str(self.curThreadNum) + '_num++; \n'
						s += ' ' * 20 + '	 ' + self.pre_addStatement  
						s += ' ' * 20 + '}\n\n'
						# self.subscript = ''
					else:
						s += '\n'
						s += ' ' * 20 + 'wwr_w_tmp' + str(self.curThreadNum) + '_num++; //add\n'
						s += ' ' * 20 + self.pre_addStatement   
						s += '\n'
				
				# add by wuyf
				if pointer_wr and pointer_wr in self.pointer_list[variable]:
					s += '\n' + ' ' * 18 + '}\n'
			
			elif self.find_read(stmt, variable) == True: # R
				s += ''.join(self._generate_stmt(stmt))  # 先输出读 方便反例查看

				# add by wuyf
				if pointer_wr and pointer_wr in self.pointer_list[variable]:
					s += '\n' + ' ' * 18 + 'if(%s == __cs_variable_address) {'% pointer_wr

				if self.addStatement.find('wwr_w_tmp') != -1 and self.assertNumber != 1: # 防止函数一开始先检测r
					
					if self.subscript != '':
						s += '\n'
						s += ' ' * 20 + 'if(' + self.subscript + ' == ' + self.index + '){  //add\n'
						s += ' ' * 20 + '	 ' + self.pre_addStatement 
						s += ' ' * 20 + '	 if(wwr_w_tmp' + str(self.curThreadNum) + '_num != 0){\n' 
						s += ' ' * 20 + '	 	 assert(wwr_r' + str(self.assertNumber-1) + '==wwr_w_tmp' + str(self.curThreadNum) + ');\n'
						s += ' ' * 20 + '	 	 wwr_w_tmp' + str(self.curThreadNum) + '_num = 0;\n' # 去除后续的多余反例
						s += ' ' * 20 + '	 }\n'									
						s += ' ' * 20 + '}\n\n'
						# self.subscript = ''
					else:		
						s += '\n'						
						s += ' ' * 20 + self.pre_addStatement
						s += ' ' * 20 + 'if(wwr_w_tmp' + str(self.curThreadNum) + '_num != 0){\n' # 约束反例 必须是有wwr_W_tmp的赋值
						s += ' ' * 20 + '	 assert(wwr_r' + str(self.assertNumber-1) + '==wwr_w_tmp' + str(self.curThreadNum) + ');\n'
						s += ' ' * 20 + '	 wwr_w_tmp' + str(self.curThreadNum) + '_num = 0;\n' # 去除后续的多余反例
						s += ' ' * 20 + '}\n\n'	
									
						
				elif self.addStatement.find('wwr_r') != -1: 

					if self.subscript != '':
						s += '\n'
						s += ' ' * 20 + 'if(' + self.subscript + ' == ' + self.index + '){  //add\n'
						s += ' ' * 20 + '	 ' +self.addStatement 
						s += ' ' * 20 + '	 if(wwr_w_tmp' + str(self.curThreadNum) + '_num != 0){\n'
						s += ' ' * 20 + '	 	 assert(wwr_r' + str(self.assertNumber) + '==wwr_w_tmp' + str(self.curThreadNum) + ');\n'
						s += ' ' * 20 + '		 wwr_w_tmp' + str(self.curThreadNum) + '_num = 0;\n' # 去除后续的多余反例
						s += ' ' * 20 + '	 }\n'	
						s += ' ' * 20 + '}\n\n'
						# self.subscript = ''
					else:	
						s += '\n'			
						s += ' ' * 20 + self.addStatement 
						s += ' ' * 20 + 'if(wwr_w_tmp' + str(self.curThreadNum) + '_num != 0){\n' # 约束反例 必须是有wwr_W_tmp的赋值
						s += ' ' * 20 + '	 assert(wwr_r' + str(self.assertNumber) + '==wwr_w_tmp' + str(self.curThreadNum) + ');\n'
						s += ' ' * 20 + '	 wwr_w_tmp' + str(self.curThreadNum) + '_num = 0;\n' # 去除后续的多余反例
						s += ' ' * 20 + '}\n\n'		

					self.assertNumber += 1

					self.pre_addStatement = self.addStatement
					self.addStatement_list[3] = str(self.curThreadNum) 
					self.addStatement_list[2] = 'w_tmp' 
					self.addStatement = ''.join(self.addStatement_list)

				# add by wuyf
				if pointer_wr and pointer_wr in self.pointer_list[variable]:
					s += '\n' + ' ' * 18 + '}\n'

			else:
				s += ''.join(self._generate_stmt(stmt)) 
   			
   			self.subscript = ''

		elif self.mode == 'rwr':
			# 搜索r

			if self.find_write(stmt, variable) == True and self.assertNumber != 1:
				s += ''.join(self._generate_stmt(stmt)) 

				# add by wuyf
				if pointer_wr and pointer_wr in self.pointer_list[variable]:
					s += '\n' + ' ' * 18 + 'if(%s == __cs_variable_address) {'% pointer_wr

				if self.subscript != '':
					s += '\n'
					s += ' ' * 20 + 'if(' + self.subscript + ' == ' + self.index + '){  //add\n'
					s += ' ' * 20 + '	 rwr_tmp' + str(self.curThreadNum) + '_num = 0; //add\n\n'
					s += ' ' * 20 + '}\n\n'
					#  self.subscript = ''
				else:
					s += '\n' 
					s += ' ' * 20 + 'rwr_tmp' + str(self.curThreadNum) + '_num = 0; //add\n\n'
				
				# add by wuyf
				if pointer_wr and pointer_wr in self.pointer_list[variable]:
					s += '\n' + ' ' * 18 + '}\n'
			
			elif self.find_read(stmt, variable) == True:
				s += ''.join(self._generate_stmt(stmt)) 

				# add by wuyf
				if pointer_wr and pointer_wr in self.pointer_list[variable]:
					s += '\n' + ' ' * 18 + 'if(%s == __cs_variable_address) {'% pointer_wr

				if self.subscript != '':
					s += '\n'
					s += ' ' * 20 + 'if(' + self.subscript + ' == ' + self.index + '){  //add\n'
					s += ' ' * 20 + '	 ' + self.addStatement
					s += ' ' * 20 + '	 if(rwr_tmp' + str(self.curThreadNum) + '_num != 0){  //add\n'
					s += ' ' * 20 + '	 	 assert(rwr_r' + str(self.assertNumber) + ' == rwr_tmp' + str(self.curThreadNum) + ');\n'
					s += ' ' * 20 + '	 }\n'
					s += ' ' * 20 + '	 rwr_tmp' + str(self.curThreadNum) + '_num++;\n'
					s += ' ' * 20 + '	 rwr_tmp' + str(self.curThreadNum) + ' = rwr_r' + str(self.assertNumber) + '; \n'
					s += ' ' * 20 + '}\n\n'
					# self.subscript = ''

				else:
					s += '\n' 
					s += ' ' * 20 + self.addStatement
					s += ' ' * 20 + 'if(rwr_tmp' + str(self.curThreadNum) + '_num != 0){  //add\n'
					s += ' ' * 20 + '	 assert(rwr_r' + str(self.assertNumber) + ' == rwr_tmp' + str(self.curThreadNum) + ');\n'
					s += ' ' * 20 + '}\n'
					s += ' ' * 20 + 'rwr_tmp' + str(self.curThreadNum) + '_num++;\n'
					s += ' ' * 20 + 'rwr_tmp' + str(self.curThreadNum) + ' = rwr_r' + str(self.assertNumber) + '; \n\n'

				self.assertNumber += 1
					
				self.addStatement_list[3] = str(self.assertNumber)  
				self.addStatement = ''.join(self.addStatement_list)

				# add by wuyf
				if pointer_wr and pointer_wr in self.pointer_list[variable]:
					s += '\n' + ' ' * 18 + '}\n'

			else:
				s += ''.join(self._generate_stmt(stmt)) 

			self.subscript = ''

			'''
			if self.find_read(stmt) == True:
				s += ' ' * 10 + self.addStatement 
				if self.firstInFunc == False :   # 由于序号问题 所断言内容不一定是 str(self.assertNumber - 1)
					s += ' ' * 10 + 'assert(rwr_r' + str(self.assertNumber) + '==rwr_r' + str(self.assertNumber - 1) + '); //add \n'
				
				self.firstInFunc = False

				self.assertNumber += 1 
				self.assertNumberUsed = False
				self.addStatement_list[3] = str(self.assertNumber) 
				self.addStatement = ''.join(self.addStatement_list)

			s += ''.join(self._generate_stmt(stmt)) 
			'''
		# add 在wrw模式下 需要对高优先级线程里的r识别
		elif self.mode == 'wrw':
			

			if self.find_read(stmt, variable) == True and self.currentFun != 'main_task_0':
				s += ''.join(self._generate_stmt(stmt))

				# add by wuyf
				if pointer_wr and pointer_wr in self.pointer_list[variable]:
					s += '\n' + ' ' * 18 + 'if(%s == __cs_variable_address) {'% pointer_wr

				if self.subscript != '':
					s += '\n'
					s += ' ' * 20 + 'if(' + self.subscript + ' == ' + self.index + '){  //add\n'
					# s += ' ' * 20 + '	 wrw_a_' + self.curThreadNum + '_num = 0; //add\n'
					for lowPrioThreadNum in self.lowPrioThreadNums:
						s += ' ' * 20 + '	 wrw_a_' + lowPrioThreadNum + ' = 1; //add\n'
					s += ' ' * 20 + '}\n\n'
					# self.subscript = ''
				else:
					s += '\n' 
					# s += ' ' * 20 + 'wrw_a_' + self.curThreadNum + '_num = 0; //add\n' # wrw模式忽略w之间的r
					for lowPrioThreadNum in self.lowPrioThreadNums:
						s += ' ' * 20 + 'wrw_a_' + lowPrioThreadNum + ' = 1; //add\n'
					s += '\n' 

				# add by wuyf
				if pointer_wr and pointer_wr in self.pointer_list[variable]:
					s += '\n' + ' ' * 18 + '}\n'
			elif self.find_write(stmt, variable) == True and self.randomFunc[self.currentFun].prio != self.highestPrio:
				s += ''.join(self._generate_stmt(stmt))

				# add by wuyf
				if pointer_wr and pointer_wr in self.pointer_list[variable]:
					s += '\n' + ' ' * 18 + 'if(%s == __cs_variable_address) {'% pointer_wr

				if self.subscript != '':
					s += '\n'
					s += ' ' * 20 + 'if(' + self.subscript + ' == ' + self.index + '){  //add\n'
					s += ' ' * 20 + '	 if(wrw_a_' + self.curThreadNum + '_num != 0){  //add\n'
					s += ' ' * 20 + '	 	 assert(wrw_a_' + self.curThreadNum + ' == 0);\n'
					s += ' ' * 20 + '	 }\n'
					s += ' ' * 20 + '	 wrw_a_' + self.curThreadNum + '_num++;\n'
					s += ' ' * 20 + '	 wrw_a_' + self.curThreadNum + ' = 0; \n\n'
					s += ' ' * 20 + '}\n\n'
					# self.subscript = ''

				else:
					s += '\n' 
					s += ' ' * 20 + 'if(wrw_a_' + self.curThreadNum + '_num != 0){  //add\n'
					s += ' ' * 20 + '	 assert(wrw_a_' + self.curThreadNum + ' == 0);\n'
					s += ' ' * 20 + '}\n'
					s += ' ' * 20 + 'wrw_a_' + self.curThreadNum + '_num++;\n'
					s += ' ' * 20 + 'wrw_a_' + self.curThreadNum + ' = 0; \n\n'						

				# add by wuyf
				if pointer_wr and pointer_wr in self.pointer_list[variable]:
					s += '\n' + ' ' * 18 + '}\n'
			else:
				s += ''.join(self._generate_stmt(stmt)) 
		else:
			s += ''.join(self._generate_stmt(stmt))

		self.subscript = ''

		return s

	def isLoopAbsStmt(self, stmt): # 用来屏蔽循环抽象导致的读写  应当保证只在loop里边才屏蔽 见017
		if type(stmt) == c_ast.Assignment:
			if type(stmt.rvalue) == c_ast.ID and stmt.rvalue.name == self.variable:
				if type(stmt.lvalue) == c_ast.ID and stmt.lvalue.name.endswith(self.variable+'_0'): 
					# loop_1_cnt_0 = cnt
					return True
			'''
			if type(stmt.lvalue) == c_ast.ID and stmt.lvalue.name == self.variable:
				if type(stmt.rvalue) == c_ast.BinaryOp:
					if type(stmt.rvalue.left) == c_ast.ID and stmt.rvalue.left.name.startswith('loop_') and stmt.rvalue.left.name.endswith(self.variable+'_0') :
						
						# cnt = resetIOVar_cnt_list[]
						# cnt = loop_1_cnt_0 + 
						# cnt = IOVar_cnt_list[] + k1
						# cnt = nondet_int()
						return True
			'''
			if type(stmt.lvalue) == c_ast.ID and stmt.lvalue.name == self.variable:
				assignStmt = self.visit(stmt.rvalue)
				if assignStmt.find('resetIOVar_%s_list['%(self.variable)) != -1:
					return True
				if assignStmt.find('IOVar_%s_list['%(self.variable)) != -1:
					return True
				if assignStmt.find(self.variable+'_0') > assignStmt.find('='):
					return True
				if type(stmt.rvalue) == c_ast.FuncCall:
					fref = self._parenthesize_unless_simple(stmt.rvalue.name)
					if fref.find('nondet_') != -1:
						return True
			return False

	def visit_Compound(self, n): # add   在instrumenter模块之前 以及instrumenter模块非main_task main_thread的线程

		if self.name()=="instrumenter":
			# print("C_generator.func_visit_Compound:print self.currentFunct")
			# print(self.currentFunct)
			if self.currentFunct == 'main_task_0': # 让 if 等其他maintask内的compound用visit_mainTaskBody访问
				return self.visit_mainTaskBody(n)

			if self.currentFunct == 'main_thread':
				return self.visit_mainThreadBody(n)

		s = self._make_indent() + '{\n'
		self.indent_level += 2
		if n.block_items:
				for stmt in n.block_items:	
					# 处理单变量访问序	待检测变量类型不为指针
					if self.name()=="instrumenter" and self.currentFun in self.randomFunc and self.mode in ['rww', 'wwr', 'rwr', 'wrw']:
						
						if self.isLoopAbsStmt(stmt):	# 屏蔽循环抽象导致的读写
							s += ''.join(self._generate_stmt(stmt))					
						elif self.variable_is_pointer():
							s += self.deal_with_svp_pointer(stmt)

						else:
							s += self.deal_with_svp(stmt)

					else:			
						s += ''.join(self._generate_stmt(stmt))

		self.indent_level -= 2
		s += self._make_indent() + '}\n'

		return s

	def visit_mainTaskBody(self, n):   # add by ql 只在instrumenter模块处理main_task
		# print("C_generator.func_visit_mainTaskBody")
		# print(self.indent_level)

		def is_eventEqualsNode(string , node): # 用于判断事件字符串和node对象是否相等   
			statement = string.replace(';', '')
			lvalue = statement[:statement.find('=')].strip()
			rvalue = statement[statement.find('=')+1:].strip()

			if self.visit(node.lvalue) == lvalue and node.rvalue.value == rvalue:
				return True
			else:
				return False

		
		s = self._make_indent() + '{\n'
		self.indent_level += 2

		if n.block_items:
			
			for stmt in n.block_items:

				if type(stmt) == c_ast.Compound:
					# 和visit_Compound通过visit()调用自己不同 是直接调自己
					# 存在特殊情况 type不是Compound 但其内部含有Compound 如 IF
					s += ''.join(self.visit_mainTaskBody(stmt)) 

				elif type(stmt) == c_ast.While and str(stmt.cond.value) == '1':
					# 碰到while(1) 是unroller模块加的 在这里去掉
					print("C_generator.func_visit_mainTaskBody:find while(1)")
					self.firstWhile_1 = True

					continue

				# 处理单变量访问序
				elif self.name()=="instrumenter" and self.currentFun in self.randomFunc and self.mode in ['rww', 'wwr', 'rwr', 'wrw']:
					if self.isLoopAbsStmt(stmt):	# 屏蔽循环抽象导致的读写
						s += ''.join(self._generate_stmt(stmt))		
					elif self.variable_is_pointer():
						s += self.deal_with_svp_pointer(stmt)
					else:
						s += self.deal_with_svp(stmt)

				else: 
					# if type(stmt) == c_ast.Assignment:
					# 	if type(stmt.lvalue) == c_ast.StructRef:
					# 		print(stmt.lvalue.name)
					# 		print(stmt.lvalue.children())

					s += ''.join(self._generate_stmt(stmt)) 				



				# 处理三种中断
				if type(stmt) == c_ast.FuncCall and self._parenthesize_unless_simple(stmt.name) == '__CSEQ_rawline':
					self.labelNum +=1

				# 加线程变量定义
				# if type(stmt) == c_ast.FuncCall and self._parenthesize_unless_simple(stmt.name) == '__CSEQ_rawline':
				if self.firstInMain_task == True:
					self.firstInMain_task = False
					for threadVariable in self.eventThreadDic:
						s += ' '* 10 + "static cspthread_t %s;\n" % threadVariable
						s += ' '* 10 + "__cs_init_scalar(& %s, sizeof(cspthread_t));\n\n" % threadVariable
					for threadVariable in self.timerThreadDic:
						s += ' '* 10 + "static cspthread_t %s;\n" % threadVariable
						s += ' '* 10 + "__cs_init_scalar(& %s, sizeof(cspthread_t));\n\n" % threadVariable
						
					if self.timerThreadDic: # 加周期线程相关变量
						i = 0
						self.timerInterrupt = {} #周期中断字典 key 中断名 value 该中断的序号（表示有几个不同的周期中断） 周期 时间约束
						for threadVariable in self.timerThreadDic:
							threadName = self.timerThreadDic[threadVariable].threadName
							interruptName = threadName[:threadName.rfind('_')]
								
							if interruptName not in self.timerInterrupt:
								i += 1
								t = self.timerThreadDic[threadVariable].node.t
								constraint = int(self.timerThreadDic[threadVariable].node.constraint)
								T = t + constraint
									# print(t)
									# print(constraint)
								self.timerInterrupt[interruptName]={'seq': i, 'T':t, 'constraint':constraint}
									
								s += ' '* 10 + "static int T%s;\n" % i
								s += ' '* 10 + "T%s = (%s);\n\n"  % (i, T) 

								s += ' '* 10 + "static int statement_counter%s;\n" % i
								s += ' '* 10 + "statement_counter%s = nondet_int();\n" %(i)
								s += ' '* 10 + "__CPROVER_assume(statement_counter%s>=0 && statement_counter%s<=%s);\n\n" %(i,i,str(constraint*2)) # 

								s += ' '* 10 + "static int period_counter%s;\n" % i
								s += ' '* 10 + "period_counter%s = (%s);\n\n" %(i, 0 )

				

				# 加事件触发线程判断  语句计数counter++  周期线程判断
				if type(stmt)  == c_ast.Assignment :
					s += '\n'
					currentStmtisEvent = False

					if self.firstWhile_1 == True and self.haveConstraint: # 默认main_task里含有while(1)
						sapceNum = 20
						s += ' '* sapceNum + '_cs_counter++;\n' 


					for threadVariable in self.eventThreadDic: # 加事件中断
						if is_eventEqualsNode(self.eventThreadDic[threadVariable].node.event.replace(';', ''), stmt) and self.eventThreadDic[threadVariable].visit == False:
							print("C_generator.find %s eventflag" % threadVariable)
							currentStmtisEvent = True
							#sapceNum = self._generate_stmt(stmt).find('eventflag')
							#print(sapceNum)
							# s += ' '* sapceNum + self.createDic[func_name].pop(0)[2:] + ';\n'
							
							self.eventThreadDic[threadVariable].visit = True # 表示该记录已经被访问过了
							spaceNum = 20
							threadInfo = self.eventThreadDic[threadVariable] # 
							threadName = threadInfo.threadName
							index = threadInfo.index
							s += ' '* spaceNum + 'pthread_create_2(& %s, 0, %s, 0, %d);\n' %(threadVariable, threadName, index)
							# s += ' '* spaceNum + 'counter_before = counter;'
							
							if len(self.timerThreadDic) == 0 :

								s += ' '* spaceNum + '__cs_pc_cs[1]=' + str(self.labelNum) + ';\n'  # 为了简便下标固定是1  实际应该是main_task的索引
								s += ' '* spaceNum + 'goto  tmain_task_0_' + str(self.threadsizes['main_task_0']) + ';\n'
	  
							break


					if self.timerThreadDic and self.firstWhile_1 == True: # 加周期中断

						for interruptName in self.timerInterrupt:
							seq = self.timerInterrupt[interruptName]['seq']

							spaceNum = 20
							s += ' '* spaceNum + 'statement_counter%s++;\n\n' % seq

							s += ' '* spaceNum + 'static _Bool if_cond_10;\n' # 不能含有__cs_tmp_if 因为在翻译时会认为这对应源代码里某个条件语句 会找其行数 找不到就是？
							s += ' '* spaceNum + 'if_cond_10 = (statement_counter%s == T%s);\n' %(seq,seq)
							s += ' '* spaceNum + 'if(if_cond_10) {\n' 
							s += ' '* spaceNum + '    period_counter%s++;\n\n' % seq

							i = 1
							for threadVariable in self.timerThreadDic:

								threadInfo = self.timerThreadDic[threadVariable] # 
								threadName = threadInfo.threadName
								index = threadInfo.index

								s += ' '* spaceNum + '    static _Bool if_cond_1%s;\n' % i
								s += ' '* spaceNum + '    if_cond_1%s = (period_counter%s==%s);\n' % (i,seq, i)
								s += ' '* spaceNum + '    if(if_cond_1%s) {\n' % i
								s += ' '* spaceNum + '        pthread_create_2(& %s, 0, %s, 0, %d);\n' %(threadVariable, threadName, index) 
								s += ' '* spaceNum + '    }\n'
								i+=1

							s +='\n'
							s += ' '* spaceNum + '    statement_counter%s=nondet_int();\n' % seq
							s += ' '* spaceNum + '    __CPROVER_assume(statement_counter%s>=0);\n' % seq
							s += ' '* spaceNum + '    __CPROVER_assume(statement_counter%s<=%s);\n' % (seq, str(int(self.timerInterrupt[interruptName]['constraint'])*2)) # 
							s += ' '* spaceNum + '    __cs_pc_cs[1]=' + str(self.labelNum) + ';\n'
							s += ' '* spaceNum + '    goto  tmain_task_0_' + str(self.threadsizes['main_task_0']) + ';\n'
							

							if currentStmtisEvent == True:
								s += ' '* spaceNum + '}else{\n'
								s += ' '* spaceNum + '    __cs_pc_cs[1]=' + str(self.labelNum) + ';\n'
								s += ' '* spaceNum + '    goto  tmain_task_0_' + str(self.threadsizes['main_task_0']) + ';\n'
								s += ' '* spaceNum + '}\n'
							else:
								s += ' '* spaceNum + '}\n'


		self.indent_level -= 2
		s += self._make_indent() + '}\n'
		return s

	def visit_mainThreadBody(self, n):   # add by ql

		s = self._make_indent() + '{\n'
		self.indent_level += 2
		if n.block_items:

			for stmt in n.block_items:
				if type(stmt) == c_ast.Compound:
					# 和visit_Compound通过visit()调用自己不同 是直接调自己
					# 存在特殊情况 type不是Compound 但其内部含有Compound 如 IF
					s += ''.join(self.visit_mainThreadBody(stmt))  

				elif type(stmt) == c_ast.FuncCall and stmt.name.name == 'pthread_create': #  self._parenthesize_unless_simple(stmt.name) 
				# 注释掉 事件触发线程 和周期线程 的创建
					# print(stmt.name.name)
					# print("C_generator.func_mainThreadBody:find Thread create")
					# print( self.visit(stmt))
				   
					statement = self.visit(stmt)
					threadVariable = statement[:statement.find(',')]
					threadVariable = threadVariable[threadVariable.find('&')+2:]
					# print(threadVariable)
					if threadVariable in self.eventThreadDic or threadVariable in self.timerThreadDic:
						createStmt = self._generate_stmt(stmt)
						left = createStmt[:createStmt.find('pthread_create')]
						right = createStmt[createStmt.find('pthread_create'):]
						s += '\n'+left + '//'+ right

					else:
						s += '\n'+''.join(self._generate_stmt(stmt))
					
					# s += ''.join(self._generate_stmt(stmt))

				elif type(stmt) == c_ast.FuncCall and stmt.name.name == '__cs_init_scalar': #  self._parenthesize_unless_simple(stmt.name) 
				# 注释掉 事件触发线程 和周期线程 的线程变量初始化
				   
					statement = self.visit(stmt)
					threadVariable = statement[:statement.find(',')]
					threadVariable = threadVariable[threadVariable.find('&')+2:]
					# print(threadVariable)
					if threadVariable in self.eventThreadDic or threadVariable in self.timerThreadDic:
						createStmt = self._generate_stmt(stmt)
						left = createStmt[:createStmt.find('__cs_init_scalar')]
						right = createStmt[createStmt.find('__cs_init_scalar'):]
						s += left + '//'+ right

					else:
						s += ''.join(self._generate_stmt(stmt))
					

				elif type(stmt) == c_ast.Decl and (stmt.name in self.eventThreadDic or stmt.name in self.timerThreadDic): 
				# 注释掉 事件触发线程 和周期线程的线程变量定义 

					threadVarStmt = self._generate_stmt(stmt)
					left = threadVarStmt[:threadVarStmt.find('static')]
					right = threadVarStmt[threadVarStmt.find('static'):]
					s += left + '//'+ right
					
				else:

					s += ''.join(self._generate_stmt(stmt))   

			   

		self.indent_level -= 2
		s += self._make_indent() + '}\n'
		return s


	def visit_CompoundLiteral(self, n):
		return '(' + self.visit(n.type) + '){' + self.visit(n.init) + '}'


	def visit_EmptyStatement(self, n):
		return ';'

	def visit_ParamList(self, n):
		return ', '.join(self.visit(param) for param in n.params)

	def visit_Return(self, n):
		s = 'return'
		if n.expr: s += ' ' + self.visit(n.expr)
		return s + ';'

	def visit_Break(self, n):
		return 'break;'

	def visit_Continue(self, n):
		return 'continue;'

	def visit_TernaryOp(self, n):
		s  = '(' + self._visit_expr(n.cond) + ') ? '
		s += '(' + self._visit_expr(n.iftrue) + ') : '
		s += '(' + self._visit_expr(n.iffalse) + ')'
		return s

	def visit_If(self, n):
		s = 'if ('
		if n.cond: s += self.visit(n.cond)
		s += ')\n'
		s += self._generate_stmt(n.iftrue, add_indent=True)
		if n.iffalse:
			s += self._make_indent() + 'else\n'
			s += self._generate_stmt(n.iffalse, add_indent=True)
		return s

	def visit_For(self, n):
		s = 'for ('
		if n.init: s += self.visit(n.init)
		s += ';'
		if n.cond: s += ' ' + self.visit(n.cond)
		s += ';'
		if n.next: s += ' ' + self.visit(n.next)
		s += ')\n'
		s += self._generate_stmt(n.stmt, add_indent=True)
		return s

	def visit_While(self, n):
		s = 'while ('
		if n.cond: s += self.visit(n.cond)
		s += ')\n'
		s += self._generate_stmt(n.stmt, add_indent=True)
		return s

	def visit_DoWhile(self, n):
		s = 'do\n'
		s += self._generate_stmt(n.stmt, add_indent=True)
		s += self._make_indent() + 'while ('
		if n.cond: s += self.visit(n.cond)
		s += ');'
		return s

	def visit_Switch(self, n):
		s = 'switch (' + self.visit(n.cond) + ')\n'
		s += self._generate_stmt(n.stmt, add_indent=True)
		return s

	def visit_Case(self, n):
		s = 'case ' + self.visit(n.expr) + ':\n'
		for stmt in n.stmts:
			s += self._generate_stmt(stmt, add_indent=True)
		return s

	def visit_Default(self, n):
		s = 'default:\n'
		for stmt in n.stmts:
			s += self._generate_stmt(stmt, add_indent=True)
		return s

	def visit_Label(self, n):
		return n.name + ':\n' + self._generate_stmt(n.stmt)

	def visit_Goto(self, n):
		return 'goto ' + n.name + ';'

	def visit_EllipsisParam(self, n):
		return '...'

	def visit_Struct(self, n):
		return self._generate_struct_union(n, 'struct')

	def visit_Typename(self, n):
		return self._generate_type(n.type)

	def visit_Union(self, n):
		return self._generate_struct_union(n, 'union')

	def visit_NamedInitializer(self, n):
		s = ''
		for name in n.name:
			if isinstance(name, c_ast.ID):
				s += '.' + name.name
			elif isinstance(name, c_ast.Constant):
				s += '[' + name.value + ']'
		s += ' = ' + self._visit_expr(n.expr)
		return s

	def visit_FuncDecl(self, n):
		return self._generate_type(n)

	def _generate_struct_union(self, n, name):
		""" Generates code for structs and unions. name should be either
			'struct' or union.
		"""
		s = name + ' ' + (n.name or '')
		if n.decls:
			s += '\n'
			s += self._make_indent()
			self.indent_level += 2
			s += '{\n'
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

		# if hasattr(self, 'name') and self.name() == 'LoopAbstraction':
		# 	print('c_generator.func__generate_stmt: %s'%type(n))

		typ = type(n)
		if add_indent: self.indent_level += 2
		indent = self._make_indent()
		if add_indent: self.indent_level -= 2

		# add
		#if self.name()=="instrumenter" and typ in c_ast.FuncCall and self._parenthesize_unless_simple(n.name) == 'pthread_create':
		#    self.createList.append(n)

		if typ in (
				c_ast.Decl, c_ast.Assignment, c_ast.Cast, c_ast.UnaryOp,
				c_ast.BinaryOp, c_ast.TernaryOp, c_ast.FuncCall, c_ast.ArrayRef,
				c_ast.StructRef, c_ast.Constant, c_ast.ID, c_ast.Typedef,
				c_ast.ExprList, pycparserext.ext_c_parser.Asm):  			#  对ext_c_parser.Asm应该加；
			# These can also appear in an expression context so no semicolon
			# is added to them automatically
			#
			return indent + self.visit(n) + ';\n'
		elif typ in (c_ast.Compound,):
			# No extra indentation required before the opening brace of a
			# compound - because it consists of multiple lines it has to
			# compute its own indentation.
			#
			return self.visit(n)
		else:
			return indent + self.visit(n) + '\n'

	def _generate_decl(self, n):
		""" Generation from a Decl node.
		"""
		s = ''
		if n.funcspec: s = ' '.join(n.funcspec) + ' '
		if n.storage: s += ' '.join(n.storage) + ' '
		s += self._generate_type(n.type)
		return s

	def _generate_type(self, n, modifiers=[]):  # 此函数没被使用 parser里用的是ext_c_generator的_generate_type
		""" Recursive generation from a type node. n is the type node.
			modifiers collects the PtrDecl, ArrayDecl and FuncDecl modifiers
			encountered on the way down to a TypeDecl, to allow proper
			generation from it.
		"""
		typ = type(n)
		#~ print(n, modifiers)

		

		if typ == c_ast.TypeDecl:
			s = ''
			if n.quals: s += ' '.join(n.quals) + ' '
			s += self.visit(n.type)

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
			if nstr: s += ' ' + nstr
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

	def _parenthesize_if(self, n, condition):
		""" Visits 'n' and returns its string representation, parenthesized
			if the condition function applied to the node returns True.
		"""
		s = self._visit_expr(n)
		if condition(n):
			return '(' + s + ')'
		else:
			return s

	def _parenthesize_unless_simple(self, n):
		""" Common use case for _parenthesize_if
		"""
		return self._parenthesize_if(n, lambda d: not self._is_simple_node(d))

	def _is_simple_node(self, n):
		""" Returns True for nodes that are "simple" - i.e. nodes that always
			have higher precedence than operators.
		"""
		return isinstance(n,(   c_ast.Constant, c_ast.ID, c_ast.ArrayRef,
								c_ast.StructRef, c_ast.FuncCall))
