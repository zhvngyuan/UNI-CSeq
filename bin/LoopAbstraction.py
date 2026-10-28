#coding=utf-8
""" 
    loopAbstraction
	
Author:
    ql

Changes:
	2025.06.10 Modify the header of the generated loop, add by zy

To do:
  

"""

import pycparser.c_ast
from modules import module


class IOVarType():# 存储IO变量的信息

	def __init__(self,resetExpression, selfRecurrenceExpression, otherExpression, oprandList, IOVarNonDeter=None,kind=None):
		self.resetExpression = resetExpression
		self.selfRecurrenceExpression = selfRecurrenceExpression
		self.otherExpression = otherExpression
		self.oprandList = oprandList   		# 存储表达式的运算符和操作数 用空格隔开
		self.IOVarNonDeter = IOVarNonDeter  # 存储 随机数的变量名
		self.kind = kind			# 存储该IO变量的类型


class LoopAbstraction(module.Translator):

	# visitingCond = False
	visitingAssignment = False
	visitingAssignmentRvalue = False
	visitingArrayRef = False
	visitingStructRef = False
	# visitingArray = False
	visitingVar = False
	assertToAssume = False
	
	haveAssert = {} 		# key loopNode  value 该循环是否含有断言
	inputVar = {}  			# key loopNode  value 该循环的I变量列表
	inputVarName = {}
	outputVar = {}			# key loopNode  value 该循环的O变量列表
	outputVarName = {}
	outputVarAssignment = {}# key loopNode  value 字典 ：key->该循环内O变量名 value->O变量的赋值语句  
	inputOutputVar = {}		# key loopNode  value 该循环的IO变量列表
	inputOutputVarName = {}
	IOVarInfo = {} 			# key loopNode  value 字典 ：key->该循环内IO变量 value->IO变量的信息IOVarType对象
	#IOVarNonDeter = {} 		#存储使用过的随机数变量名

	stmtMapBlock = {}		# key loopNode  value 字典 ：key->赋值语句对象  value->该语句对应的blocked
	blockMapNonDeter = {}   # key loopNode  value 字典 ：key->blockid  value->该块对应的随机数变量名
	usedBlockNonDeter = {}		# key loopNode  value 该循环的用到的随机数变量名 来自blockMapNonDeter的value的value

	loopNode = None 		#存储当前循环节点 
	oldBlockid = ''			#存储循环体的blockid 在访问递增操作时使用
	loopDic = {} # key loopNode  value 该循环对应编号
	loopNum = 0  #存储循环数 用来给随机数变量命名
	blockOfLoop = ''  # 存储循环所在的block

	'''
	def visit_Compound(self,n):
		self.compoundNode = n
		s = super(LoopAbstraction, self).visit_Compound(n)

		return s
	'''

	def init(self):
		'''		
		with open("../Cseq/modules/absOption",'rb') as flagfile:
			absOption = pickle.load(flagfile)
			self.loopAbsFlag = absOption['loopAbs']
		print('loopAbsFlag:%s' % self.loopAbsFlag)
		'''
		pass
		

	def loadfromstring(self,string,env):
		self.loopAbsFlag = env.loopAbs
		# print(self.loopAbsFlag)
		# print(self.getinputparam('loopAbs'))
		
		super(LoopAbstraction, self).loadfromstring(string,env)
		
		self.setoutputparam('loopAbsFlag', self.loopAbsFlag)

		# 生成输出字符串 add by zy
		self.output = self.visit(self.Parser.ast)

	def visit_While(self, n):
		if self.loopAbsFlag:

			if self.visitingVar:
				
				return ''
				
			else:
			
				if self.visit(n.cond) == '1': # while(1)一般对于主任务 不抽象
					s = 'while (1)\n'
					s += self._generate_stmt(n.stmt, add_indent=True)
					
				else:
					self.blockOfLoop = self.blockid
					self.oldBlockid = self.blockid + '.0'					

					s = self.loopAbstraction(n)
				
				return s
		else:
			return super(LoopAbstraction, self).visit_While(n)

	def visit_For(self, n):

		if self.loopAbsFlag:
			if self.visitingVar:
				self.visit(n.init) # 初始化语句属于循环外语句
				
				return ''
				
			else:
				# print('%s %s'%(self.blockd, self.block))
				self.blockOfLoop = self.blockid
				self.oldBlockid = self.blockid + '.0'			

				s = self.loopAbstraction(n)	
				# print(s)	
				return s
		else:
			return super(LoopAbstraction, self).visit_For(n)

	def visit_ID(self, n):
		if self.visitingAssignmentRvalue and not self.visitingArrayRef and not self.visitingStructRef: 		# self.visitingCond or 
			varName = n.name
			if varName not in self.inputVarName[self.loopNode]:
				self.inputVarName[self.loopNode].append(varName)
				self.inputVar[self.loopNode].append(n)
			return ''

		return n.name

	def visit_ArrayRef(self, n):

		if self.visitingAssignmentRvalue and not self.visitingStructRef:
			self.visitingArrayRef = True
			arrayName = self._parenthesize_unless_simple(n.name)
					
			if arrayName not in self.inputVarName[self.loopNode]:
				self.inputVarName[self.loopNode].append(arrayName) # 放数组名 后面计算IO会排除
				self.inputVar[self.loopNode].append(n) 
			self.visitingArrayRef = False
			return ''

		arrayName = self._parenthesize_unless_simple(n.name)
		subName = self.visit(n.subscript)
		return '%s[%s]'%(arrayName, subName)

	def visit_StructRef(self, n):
		if self.visitingAssignmentRvalue:
			self.visitingStructRef = True
			sref = self._parenthesize_unless_simple(n.name)

			if sref not in self.inputVarName[self.loopNode]:
				self.inputVarName[self.loopNode].append(sref) # 放变量名 a 或 a[i]
				self.inputVar[self.loopNode].append(n) 
			self.visitingStructRef = False
			return ''

		sref = self._parenthesize_unless_simple(n.name)
		return sref + n.type + self.visit(n.field)
	
	def visit_UnaryOp(self, n):
		
		if self.visitingVar and not self.visitingAssignment:
			if n.op in ['p++', 'p--']:

				varName = self._parenthesize_unless_simple(n.expr) 	# a 或 a[i]  a.mode
				if type(n.expr) == pycparser.c_ast.ArrayRef: 
					varName = self._parenthesize_unless_simple(n.expr.name)	

				# 
				if varName not in self.outputVarAssignment[self.loopNode]: # 保存该当前循环的该变量的赋值表达式
					self.outputVarAssignment[self.loopNode][varName] = []
					self.outputVarAssignment[self.loopNode][varName].append(n)					
				else:
					self.outputVarAssignment[self.loopNode][varName].append(n) 

				# print('%s%s'%(varName, n.op))
				# print(self.blockid)

				# 配置 stmtMapBlock  blockMapNonDeter
				blockid = self.blockid
				self.stmtMapBlock[self.loopNode][n] = blockid
				num = len(self.blockMapNonDeter[self.loopNode]) + 1
				if blockid not in self.blockMapNonDeter[self.loopNode]:
					self.blockMapNonDeter[self.loopNode][blockid] = 'loop_%s_block_%s' %(str(self.loopDic[self.loopNode]), str(num))
				

				if varName not in self.inputVarName[self.loopNode]:
					self.inputVarName[self.loopNode].append(varName)
					self.inputVar[self.loopNode].append(n.expr)
				if varName not in self.outputVarName[self.loopNode]:
					self.outputVarName[self.loopNode].append(varName)
					self.outputVar[self.loopNode].append(n.expr)	
					
			return ''	

		operand = self._parenthesize_unless_simple(n.expr)
		if n.op == 'p++':
			return '%s++' % operand
		elif n.op == 'p--':
			return '%s--' % operand
		elif n.op == 'sizeof':
			# Always parenthesize the argument of sizeof since it can be
			# a name.
			return 'sizeof(%s)' %(self.visit(n.expr))
		else:
			return '%s%s' % (n.op, operand)

	def visit_Assignment(self, n):

		if self.visitingVar:
			# 默认等号左边是变量
			self.visitingAssignment = True

			varName = self.visit(n.lvalue) 
			if type(n.lvalue) == pycparser.c_ast.StructRef:
				varName = self._parenthesize_unless_simple(n.lvalue.name)				
				
			elif type(n.lvalue) == pycparser.c_ast.ArrayRef:
				varName = self._parenthesize_unless_simple(n.lvalue.name)	

			elif type(n.lvalue) == pycparser.c_ast.UnaryOp:
				self.visitingAssignment = False
				return ''


			if varName not in self.outputVarAssignment[self.loopNode]: # 保存该变量的赋值表达式
				self.outputVarAssignment[self.loopNode][varName] = []
				self.outputVarAssignment[self.loopNode][varName].append(n)				
			else:
				self.outputVarAssignment[self.loopNode][varName].append(n) 

			# print('%s stmt'%(varName))
			# print(self.blockid)

			# 配置 stmtMapBlock  blockMapNonDeter
			blockid = self.blockid
			self.stmtMapBlock[self.loopNode][n] = blockid
			num = len(self.blockMapNonDeter[self.loopNode]) + 1
			if blockid not in self.blockMapNonDeter[self.loopNode]:
				self.blockMapNonDeter[self.loopNode][blockid] = 'loop_%s_block_%s' %(str(self.loopDic[self.loopNode]), str(num))
				

			if varName not in self.outputVarName[self.loopNode]:
				self.outputVarName[self.loopNode].append(varName)
				self.outputVar[self.loopNode].append(n.lvalue)	
				
			if n.op in ['+=', '-=', '*=', '/=']: 		
				if varName not in self.inputVarName[self.loopNode]:
					self.inputVarName[self.loopNode].append(varName)
					self.inputVar[self.loopNode].append(n.lvalue)
		
			self.visitingAssignmentRvalue = True
			self.visit(n.rvalue)	
			self.visitingAssignmentRvalue = False

			self.visitingAssignment = False
			
			return ''


		rval_str = self._parenthesize_if(
						n.rvalue,
						lambda n: isinstance(n, pycparser.c_ast.Assignment))

		return '%s %s %s' % (self.visit(n.lvalue), n.op, rval_str)
	
	def visit_FuncCall(self, n):

		if self.visitingVar:
			if self._parenthesize_unless_simple(n.name) == 'assert':
				self.haveAssert[self.loopNode] = True
				return '' 
				
		if self.assertToAssume:
			if self._parenthesize_unless_simple(n.name) == 'assert':
				return '__CPROVER_assume(%s)' %(self.visit(n.args))

		fref = self._parenthesize_unless_simple(n.name)
		return fref + '(' + self.visit(n.args) + ')'

	def calIOVarInfo(self, n):

		IONum = 1 # IO变量编号
		for var in self.inputOutputVar[n]:
			resetExpression = False
			selfRecurrenceExpression = False
			otherExpression = False
			oprandList = [] # 存储表达式的运算符和操作数 用空格隔开

			varName = self.visit(var)
			for node in self.outputVarAssignment[n][varName]:
				blockid = self.stmtMapBlock[n][node]
				
				if type(node) == pycparser.c_ast.UnaryOp:
					# a++ a--
					oprandList.append('%s 1 %s' %(node.op, blockid))	# p++ 1  p-- 1			

					selfRecurrenceExpression = True
					continue

				if type(node) == pycparser.c_ast.Assignment:					
					if node.op in ['+=', '-=']:	
						# a+=2  a+=b (a += b+2类未处理）	
						if type(node.rvalue) == pycparser.c_ast.Constant:	
							oprandList.append('%s %s %s' %(node.op, str(node.rvalue.value), blockid)) # += 2  -= 2

							selfRecurrenceExpression = True
							continue
						if type(node.rvalue) == pycparser.c_ast.ID and self.visit(node.rvalue) not in self.inputOutputVarName[n]:
							
							oprandList.append('%s %s %s' %(node.op, node.rvalue.name, blockid)) # += b  -= b

							selfRecurrenceExpression = True
							continue
					
					if node.op == '=':	
						# a = 2  a = b  (a = b+2类未处理）				
						if type(node.rvalue) == pycparser.c_ast.Constant:
							oprandList.append('= %s %s'%(node.rvalue.value, blockid)) # = 2

							resetExpression = True	
							continue					
						if type(node.rvalue) == pycparser.c_ast.ID and self.visit(node.rvalue) not in self.inputOutputVarName[n]:
							oprandList.append('= %s %s'%(node.rvalue.name, blockid)) # = b

							resetExpression = True
							continue

						# a = a+2  a = a+b
						if type(node.rvalue) == pycparser.c_ast.BinaryOp and node.rvalue.op in ['+', '-']:
							if type(node.rvalue.left) == pycparser.c_ast.ID and self.visit(node.rvalue.left) == varName:
								if type(node.rvalue.right) == pycparser.c_ast.Constant:
									oprandList.append('%s %s %s'%(node.rvalue.op, str(node.rvalue.right.value), blockid)) # + 2  - 2

									selfRecurrenceExpression = True
									continue
								if type(node.rvalue.right) == pycparser.c_ast.ID and self.visit(node.rvalue.right) not in self.inputOutputVarName[n]:
									oprandList.append('%s %s %s'%(node.rvalue.op, node.rvalue.right.name, blockid)) # + b  - b									

									selfRecurrenceExpression = True
									continue
							if type(node.rvalue.right) == pycparser.c_ast.ID and self.visit(node.rvalue.right) == varName:
								if type(node.rvalue.left) == pycparser.c_ast.Constant:
									oprandList.append('%s %s %s'%(node.rvalue.op, str(node.rvalue.left.value), blockid)) # + 2  - 2

									selfRecurrenceExpression = True
									continue
								if type(node.rvalue.left) == pycparser.c_ast.ID and self.visit(node.rvalue.left) not in self.inputOutputVarName[n]:
									oprandList.append('%s %s %s'%(node.rvalue.op, node.rvalue.left.name, blockid)) # + b  - b

									selfRecurrenceExpression = True
									continue

				otherExpression = True

			self.IOVarInfo[n][var] = IOVarType(resetExpression, selfRecurrenceExpression, otherExpression, oprandList)
			self.IOVarInfo[n][var].IOVarNonDeter = []

			
			# 设置随机数的变量名 k加编号  包括block对应的随机数变量名和表示数组下标的随机数变量名
			varName = 'k%s'%(str(IONum))
			IONum += 1

			if resetExpression == True and selfRecurrenceExpression == False and otherExpression == False:

				nonDeterVarName = 'loop_%s_%s_1' %(str(self.loopDic[n]), varName) #随机数的变量名 含有循环编号信息 IO变量名信息 放在循环前声明
				self.IOVarInfo[n][var].IOVarNonDeter.append(nonDeterVarName)
				
			elif resetExpression == False and selfRecurrenceExpression == True and otherExpression == False:				
				for exp in oprandList:
					
					blockid = exp[exp.rfind(' ')+1:]	
					nonDeterVarName = self.blockMapNonDeter[n][blockid]
					if nonDeterVarName not in self.usedBlockNonDeter[n]:						
						self.usedBlockNonDeter[n].append(nonDeterVarName)				

			elif resetExpression == True and selfRecurrenceExpression == True and otherExpression == False:
				
				nonDeterVarName_0 = 'loop_%s_%s_1' %(str(self.loopDic[n]), varName) #随机数的变量名 含有循环编号信息 IO变量名信息 放在循环前声明
				self.IOVarInfo[n][var].IOVarNonDeter.append(nonDeterVarName_0)				
											
				for exp in oprandList:

					op = exp[:exp.find(' ')]					
					if op != '=': 								
						
						blockid = exp[exp.rfind(' ')+1:]	
						nonDeterVarName = self.blockMapNonDeter[n][blockid]
						if nonDeterVarName not in self.usedBlockNonDeter[n]:
							self.usedBlockNonDeter[n].append(nonDeterVarName)						
						

			# 查找该IO变量类型
			# b = self.Parser.blocknode[n.stmt]	# 使用循环体的block
			# 应该用O变量的赋值所在blockid
			# assignNode = self.outputVarAssignment[n][self.visit(var)][0]
			# b = self.stmtMapBlock[n][assignNode]
			loopBodyBlock = self.Parser.blocknode[n.stmt]
			b = loopBodyBlock[:loopBodyBlock.rfind('.')]

			'''	
			if type(var) == pycparser.c_ast.ID:
				declNode = self.Parser.decl(b, var.name)	 
				varType = self.visit(declNode.type)				
			elif type(var) == pycparser.c_ast.ArrayRef:
				arrayName = self._parenthesize_unless_simple(var.name)
				declNode = self.Parser.decl(b, arrayName) 		
				varType = self.visit(declNode.type.type) 	# declNode.type是arrayDecl declNode.type.type才是typeDecl
			'''
			# print(self.Parser.blockdefid(b, var.name))

			declNode = self.Parser.decl(b, var.name)
			varType = self.visit(declNode.type)
			if type(declNode.type) == pycparser.c_ast.PtrDecl: # 如果定义的是指针类型需要加上 *
				varType += ' *'
				
			self.IOVarInfo[n][var].kind = varType

	def loopAbstraction(self, n):
		# 根据循环体内是否含有断言 选择执行函数 simpleAbs() 和 inductionAbs()
		

		if n not in self.loopDic: #首次访问循环时计算该循环的各种变量集合
			self.loopNum+=1
			self.loopDic[n] = self.loopNum		
			self.loopNode = n

			self.haveAssert[n] = False
			self.inputVar[n] = []
			self.inputVarName[n] = []
			self.outputVar[n] = []
			self.outputVarName[n] = []
			self.outputVarAssignment[n] = {}
			self.inputOutputVar[n] = []
			self.inputOutputVarName[n] = []
			self.IOVarInfo[n] = {} 
		
			self.stmtMapBlock[n] = {}
			self.blockMapNonDeter[n] = {}
			self.usedBlockNonDeter[n] = []

			self.visitingVar = True	

			self.linemarking = False 	# 不加linemarkers
			self.visit(n.stmt) 
			# for node in n.stmt.block_items:				
			# 	self.visit(node)

			if type(n) == pycparser.c_ast.For: # for循环的递增操作也属于循环体
				tmp = self.blockid 
				self.blockid = self.oldBlockid # 递增操作的blockid应该是循环体的blockid
				self.visit(n.next)	
				self.blockid = tmp
				
			self.visitingVar = False		


			for var1 in self.outputVar[n]:
				for var2 in self.inputVar[n]:
					if self.visit(var1) == self.visit(var2):
						# 应该放对象 而不是字符串 因为后面需要得到该变量的类型 
						if type(var1) == pycparser.c_ast.ArrayRef:
							continue
						elif type(var1) == pycparser.c_ast.StructRef and type(var1.name) == pycparser.c_ast.ArrayRef:
							continue
						elif self.visit(var1).startswith('__cs_temporary_'): # 引入的中间变量不算IO
							continue	
						else:
							# print(self.Parser.blocknode[n.stmt])
							# print(self.blockOfLoop)
							# print(self.visit(var1))
							# io变量的判定：应该是定义在所在循环的block及外边 不能是里边
							loopBodyBlock = self.Parser.blocknode[n.stmt]
							block = loopBodyBlock[:loopBodyBlock.rfind('.')]
							if self.Parser.decl(block, self.visit(var1)) is None:
								print("var def in loop")
							else:
								self.inputOutputVarName[n].append(self.visit(var1))
								self.inputOutputVar[n].append(var1)

			
			# print('loop_%s var set:'%(self.loopNum))
			# print('input:%s'%self.inputVarName[n])			
			# print('output:%s'%self.outputVarName[n])		
			# print('IO:%s'%self.inputOutputVarName[n])
			# print(self.haveAssert[n])
			# print('IOAssignment:')
			'''
			for name in self.inputOutputVarName[n]:
				for node in self.outputVarAssignment[n][name]:
					print('%s: %s'%(name, self.visit(node)))
			'''
			self.calIOVarInfo(n)  # IOVarInfo[n]
			# print('stmtMapBlock:%s'%self.stmtMapBlock[n])
			# print('blockMapNonDeter:%s'%self.blockMapNonDeter[n])

			self.linemarking = True 

		s = ''
		if self.haveAssert[n]:
			s += self.inductionAbs(n)
		else:
			s += self.simpleAbs(n,'simple')

		s += '__CPROVER_assume(!(%s));\n' %(self.visit(n.cond))

		return s

	def simpleAbs(self, n, flag):
		# 先调用 genAbstractLoopHeader  accelerateIOs genAssumes
		# 再根据flag的值决定是否需要把循环体内的断言转化为assume

		self.linemarking = False 	# 不加linemarkers

		s = self.genAbstractLoopHeader(n)

		# 添加声明 否则可能出现先使用 后声明
		s += self.genDecl(n.stmt)


		# 更新IO变量的初值	
		IONum = 1	
		for var in self.inputOutputVar[n]:
			s += 'loop_%s_IOVar%s = %s;\n'%(str(self.loopDic[n]), str(IONum), self.visit(var))
			IONum += 1
		# 给block对应的随机数变量名赋随机数
		for nonDeterVarName in self.usedBlockNonDeter[n]:
			s += '%s = __VERIFIER_nondet_int();\n' %(nonDeterVarName)

		s += self.accelerateIOs(n)
		s += self.genAssumes(n)

		self.linemarking = True 

		if flag == 'induction':
			# 循环体 将断言转为assume	
			self.assertToAssume = True
			s += self._generate_stmt(n.stmt, add_indent=True)
			self.assertToAssume = False
			# for node in n.stmt.block_items:
			# 	self.assertToAssume = True  # 对内层的含断言的循环处理好像不对			
			# 	s += self._generate_stmt(node)  # self.visit()				
			# 	self.assertToAssume = False
			
		elif flag == 'simple':		
			# print('LoopAbstraction.1111')
			s += self._generate_stmt(n.stmt, add_indent=True)
			# for node in n.stmt.block_items:
			# 	s += self._generate_stmt(node)  # self.visit()
		

		# for循环还要加上 next 操作	
		if type(n) == pycparser.c_ast.For: 
				lineCoords = '\n'+self._getmarker(n)+'\n'  # 添加标记
				s += lineCoords
				s += self.visit(n.next) + ';\n'	

		# 在循环体结尾加上循环变量递增
		loop_counter = 't_%s' % str(self.loopDic[n])
		s += '    %s++;\n' % loop_counter	

		s += '}\n' #对应循环头的括号
	

		# 定义IO变量初值和使用过的随机数变量 若是for循环 还要初始赋值
		VarDeclStmt = ''				 
		if type(n) == pycparser.c_ast.For:
			VarDeclStmt += '%s;\n'%(self.visit(n.init))

		# VarDeclStmt += '\n# 0 "<previous_module>"\n' 		# 添加标记 add by zy (我增加了注释)

		IONum = 1
		for var in self.inputOutputVar[n]: 		# type loop_1_IOVar1 = ;				
			# print('loop_%s定义%s初值:' %(str(self.loopDic[n]), self.visit(var)))	
			VarDeclStmt += '%s loop_%s_IOVar%s;\n' %(self.IOVarInfo[n][var].kind, str(self.loopDic[n]), str(IONum))
			IONum += 1			
			
		for var in self.IOVarInfo[n]:  			# int loop_1_k1_1;
			for k in self.IOVarInfo[n][var].IOVarNonDeter:
				VarDeclStmt += 'int %s;\n'%(k)	

		for nonDeterVarName in self.usedBlockNonDeter[n]:
			VarDeclStmt += 'int %s;\n' %(nonDeterVarName)

		s = VarDeclStmt + s

		return s
		

	def inductionAbs(self, n):
		# 先判断能否执行一次 if(c) loop
		# 再调用simpleAbs(Induction)
		# 最后执行 if(c) loop
		s = ''
		s += 'if(%s){\n'%(self.visit(n.cond))
		s += self._generate_stmt(n.stmt)
		# for node in n.stmt.block_items:				
		# 	s += self._generate_stmt(node) # self.visit()				
		s += '}\n'

		s += self.simpleAbs(n, 'induction')

		s += 'if(%s){\n'%(self.visit(n.cond))
		s += self._generate_stmt(n.stmt)
		# for node in n.stmt.block_items:				
		# 	s += self._generate_stmt(node) # self.visit()				
		s += '}\n'

		return s

	def genAbstractLoopHeader(self, n):
		'''
		# 生成新循环的头 for循环模式
		s = ''
		lineCoords = '\n'+self._getmarker(n)+'\n' 	# 添加标记
		s += lineCoords
		s += 'for(int t_%s = 0; t_%s < %s && '%(str(self.loopDic[n]), str(self.loopDic[n]), str(len(self.outputVar[n]))) + self.visit(n.cond) + '; t_%s++){\n' % str(self.loopDic[n])
		
		return s
		'''
		s = ''
		lineCoords = '\n'+self._getmarker(n)+'\n'
		s += lineCoords

		loop_counter = 't_%s' % str(self.loopDic[n])
		outputVarLen = str(len(self.outputVar[n]))
		cond = self.visit(n.cond)
		s += 'int %s = 0;\n' % loop_counter

		# 返回while循环条件
		s += 'while (%s < %s && %s) {\n' % (loop_counter, outputVarLen, cond)

		return s
		

	def accelerateIOs(self, n):
		# IO变量加速 根据类型输出对应的语句

		s = ''
		
		IONum = 1
		for var in self.inputOutputVar[n]:		
			resetExpression = self.IOVarInfo[n][var].resetExpression
			selfRecurrenceExpression = self.IOVarInfo[n][var].selfRecurrenceExpression
			otherExpression = self.IOVarInfo[n][var].otherExpression
			oprandList = self.IOVarInfo[n][var].oprandList
			
			if resetExpression == True and selfRecurrenceExpression == False and otherExpression == False:			
				expressionNum = len(self.outputVarAssignment[n][self.visit(var)])
				listName = 'resetIOVar_%s_list' %(str(IONum)) 			

				s += '%s %s[%s];\n' %(self.IOVarInfo[n][var].kind, listName, str(expressionNum+1))
				s += '%s[0] = loop_%s_IOVar%s;\n'%(listName, str(self.loopDic[n]), str(IONum)) 	#使用IO变量的初值
				q = 1							
				for exp in oprandList:
					# op = exp[:exp.find(' ')]
					num = exp[exp.find(' ')+1:exp.rfind(' ')]					
					s += '%s[%s] = %s;\n' %(listName, str(q), num)
					q+=1

				nonDeterVarName = 'loop_%s_k%s_1' %(str(self.loopDic[n]), str(IONum)) #随机数的变量名 
			
				s += '%s = __VERIFIER_nondet_int();\n' %(nonDeterVarName) 
				s += '__CPROVER_assume(%s>=0);\n'%(nonDeterVarName) 
				s += '__CPROVER_assume(%s<=%s);\n'%(nonDeterVarName, str(expressionNum))
				s += '%s = %s[%s];\n'%(self.visit(var), listName, nonDeterVarName) 
			
			elif resetExpression == False and selfRecurrenceExpression == True and otherExpression == False:	# resetExpression == False and 
				# expressionNum = len(self.outputVarAssignment[var])
				
				q = 1
				assignStmt = ''
				assignStmt += '%s = loop_%s_IOVar%s ' %(self.visit(var), str(self.loopDic[n]), str(IONum)) #使用IO变量的初值
				for exp in oprandList:
					# nonDeterVarName = 'loop_%s_k%s_%s' %(str(self.loopDic[n]), str(IONum), str(q))					
					# s += '%s = __VERIFIER_nondet_int();\n'%(nonDeterVarName)
					# s += '__CPROVER_assume(%s>=0);\n'%(nonDeterVarName) 

					op = exp[:exp.find(' ')]
					num = exp[exp.find(' ')+1:exp.rfind(' ')]
					blockid = exp[exp.rfind(' ')+1:]	
					nonDeterVarName = self.blockMapNonDeter[n][blockid]					

					if op in ['p++', '+=', '+']:
						assignStmt += '+ %s * %s ' %(num, nonDeterVarName)
					elif op in ['p--', '-=', '-']:
						assignStmt += '- %s * %s ' %(num, nonDeterVarName)

					q+=1

				assignStmt += ';\n'
				s += assignStmt

			elif resetExpression == True and selfRecurrenceExpression == True and otherExpression == False:
			# 对于内部声明的变量 可能存在问题：先使用了该变量，后面才声明 
				resetVarList = []
				assignList = []
				for exp in oprandList:
					op = exp[:exp.find(' ')]
					num = exp[exp.find(' ')+1:exp.rfind(' ')]					

					if op == '=': 					# resetExpression
						resetVarList.append(num)
					else:  							# selfRecurrenceExpression
						assignList.append(exp)				

				listName = 'IOVar_%s_list' %(str(IONum)) 
				s += '%s %s[%s];\n' %(self.IOVarInfo[n][var].kind, listName, str(len(resetVarList)+1))

				s += '%s[0] = loop_%s_IOVar%s;\n'%(listName, str(self.loopDic[n]), str(IONum)) #使用IO变量的初值
				q = 1
				for num in resetVarList:										
					s += '%s[%s] = %s;\n' %(listName,str(q), num)
					q+=1

				nonDeterVarName_0 = 'loop_%s_k%s_1' %(str(self.loopDic[n]), str(IONum)) #随机数的变量名 
				
				s += '%s = __VERIFIER_nondet_int();\n' %(nonDeterVarName_0) 
				s += '__CPROVER_assume(%s>=0);\n'%(nonDeterVarName_0)
				s += '__CPROVER_assume(%s<=%s);\n'%(nonDeterVarName_0, str(len(resetVarList)))
				assignStmt = ''
				assignStmt += '%s = %s[%s] '%(self.visit(var), listName, nonDeterVarName_0)

				q = 2								
				for exp in assignList:
					# nonDeterVarName = 'loop_%s_k%s_%s' %(str(self.loopDic[n]), str(IONum), str(q))					
					# s += '%s = __VERIFIER_nondet_int();\n'%(nonDeterVarName)
					# s += '__CPROVER_assume(%s>=0);\n'%(nonDeterVarName) 

					op = exp[:exp.find(' ')]
					num = exp[exp.find(' ')+1:exp.rfind(' ')]
					blockid = exp[exp.rfind(' ')+1:]	
					nonDeterVarName = self.blockMapNonDeter[n][blockid]					

					if op in ['p++', '+=', '+']:
						assignStmt += '+ %s * %s ' %(num, nonDeterVarName)
					elif op in ['p--', '-=', '-']:
						assignStmt += '- %s * %s ' %(num, nonDeterVarName)

					q+=1

				assignStmt += ';\n'
				s += assignStmt

			else:				
				varType = self.IOVarInfo[n][var].kind
				if varType != 'int': # (unsigned int)  (float)    int *
					s += '%s = (%s)nondet_int();\n' %(self.visit(var), varType)
				else:	
					s += '%s = nondet_%s();\n' %(self.visit(var), self.IOVarInfo[n][var].kind)

			IONum += 1
			

		# 对block对应的随机数进行约束
		for nonDeter in self.usedBlockNonDeter[n]:
			s += '__CPROVER_assume(%s>=0);\n'%(nonDeter)

		for blockid in self.blockMapNonDeter[n]:

			if self.blockMapNonDeter[n][blockid] in self.usedBlockNonDeter[n]:
				tmp = blockid
				while tmp != '0':
					tmp = tmp[:tmp.rfind('.')]
					if tmp in self.blockMapNonDeter[n] and self.blockMapNonDeter[n][tmp] in self.usedBlockNonDeter[n]:
						s += '__CPROVER_assume(%s<=%s);\n'%(self.blockMapNonDeter[n][blockid], self.blockMapNonDeter[n][tmp])
						break

		return s
	def genAssumes(self, n):
		# 
		s = '__CPROVER_assume(' + self.visit(n.cond) + ');\n'
		return s

	def genDecl(self, n):
		# print type(n) # Compound
		res = ''
		if n.block_items:
			for stmt in n.block_items:
				if type(stmt) == pycparser.c_ast.Decl:
					# print self.visit(stmt)
					res += self._generate_stmt(stmt, add_indent=True)

		return res

	# add by zy
	def string(self):
    		return self.output

class LOOPAbstraction(LoopAbstraction):
    pass	
		

		
