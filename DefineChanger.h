int WORD_SIZE = 4;
int MAX_IN_REG = 4;

int intSize = 1 * WORD_SIZE;
int shortSize = 1 * WORD_SIZE;
int booleanSize = 1 * WORD_SIZE;
int referenceSize = 1 * WORD_SIZE;

#pragma region Wrappers

//Родительский класс объекта-обёртки, который может возвращать правильный тип из IRTree в зависимости от ситуации
class ISubtreeWrapper
{
public:
	virtual ~ISubtreeWrapper(){}
	virtual const IRTree::IExp* ToExp() const = 0;
	virtual const IRTree::IStm* ToStm() const = 0;
	virtual const IRTree::IStm* ToConditional(const  IRTree::Label t, const  IRTree::Label f) const = 0;

};

//Конвертер для обычных выражений, с которыми нет никаких проблем
class ExpWrapper: public ISubtreeWrapper
{
public:
		
	ExpWrapper(const IRTree::IExp* _exp) : exp(_exp) {}

	const IRTree::IExp* ToExp() const 
	{
		return exp; 
	}

	const IRTree::IStm* ToStm() const
	{
		return new IRTree::ExpStm(exp);
	}
		
	const IRTree::IStm* ToConditional(const  IRTree::Label t, const  IRTree::Label f) const
	{
		return new IRTree::CJumpStm(IRTree::compareOpType::GT, exp, new IRTree::ConstExp(0), t, f);
	}

private:
	const IRTree::IExp* exp;
};

//Конвертер для обычных стейтментов, с которыми нет никаких проблем
class StmWrapper : public ISubtreeWrapper
{
public:

	StmWrapper(const IRTree::IStm* _stm) : stm(_stm) {}

	const IRTree::IExp* ToExp() const
	{
		return new IRTree::EseqExp(stm, new IRTree::ConstExp(0));
	}

	const IRTree::IStm* ToStm() const
	{
		return stm;
	}

	const IRTree::IStm* ToConditional(const  IRTree::Label t, const  IRTree::Label f) const
	{
		return stm;
	}

private:
	const IRTree::IStm* stm;

};

//Конвертер для конъюнкции. Конъюнкция должна корректно обрабатываться в условных выражениях. Если левая часть неверна, то 
//правая часть не должна проверяться
class BinopAndExpWrapper : public ISubtreeWrapper
{
public:

	BinopAndExpWrapper(const IRTree::IExp* _left, const ISubtreeWrapper* _right) : left(_left), right(_right) {}

	const IRTree::IExp* ToExp() const
	{
		//Считаем правую часть только в том случае, когда верна левая
		IRTree::Temp temp("temp");
		IRTree::Label t("true");
		IRTree::Label f("false");
		IRTree::Label q("quit");
		return new IRTree::EseqExp(
									new IRTree::SeqStm(
														new IRTree::CJumpStm(
																			IRTree::compareOpType::GT,
																			left,
																			new IRTree::ConstExp(0),
																			t,
																			f
																			),
														new IRTree::SeqStm(
																			new IRTree::SeqStm(
																								new IRTree::LabelStm(t),
																								new IRTree::SeqStm(
																													new IRTree::MoveStm(
																																		new IRTree::TempExp(temp),
																																		right->ToExp()
																																		),
																													new IRTree::JumpStm(new IRTree::NameExp(q),{q})
																													)
																								),
																			new IRTree::SeqStm(
																								new IRTree::LabelStm(f),
																								new IRTree::MoveStm(
																													new IRTree::TempExp(temp),
																													new IRTree::ConstExp(0)
																													)
																								)
																			)
														),
									new IRTree::EseqExp(
														new IRTree::LabelStm(q),
														new IRTree::MemExp(new IRTree::TempExp(temp),booleanSize)
														)
									);
	}

	const IRTree::IStm* ToStm() const
	{
		return new IRTree::ExpStm(this->ToExp());
	}

	const IRTree::IStm* ToConditional(const  IRTree::Label t, const  IRTree::Label f) const
	{
		IRTree::Label z("rightTrue");
		//Корректно обработаем конънкцию, как поддерево с как минимум двумя условными переходами
		return new IRTree::SeqStm(
									new IRTree::CJumpStm(
														IRTree::compareOpType::GT, 
														left, 
														new IRTree::ConstExp(0), 
														z, 
														f
														), 
									new IRTree::SeqStm(
														new IRTree::LabelStm(z),
														right->ToConditional(t,f)
														)
									);
	}

private:
	const IRTree::IExp* left;
	const ISubtreeWrapper* right;
};

//Конвертер для дизъюнкции. Дизъюнкция должна корректно обрабатываться в условных выражениях. Если левая часть верна, то 
//правая часть не должна проверяться
class BinopOrExpWrapper : public ISubtreeWrapper
{
public:

	BinopOrExpWrapper(const IRTree::IExp* _left, const ISubtreeWrapper* _right) : left(_left), right(_right) {}

	const IRTree::IExp* ToExp() const
	{
		//Считаем правую часть только в том случае, когда верна левая
		IRTree::Temp temp("temp");
		IRTree::Label t("true");
		IRTree::Label f("false");
		IRTree::Label q("quit");
		return new IRTree::EseqExp(
									new IRTree::SeqStm(
														new IRTree::CJumpStm(
																			IRTree::compareOpType::GT,
																			left,
																			new IRTree::ConstExp(0),
																			t,
																			f
																			),
														new IRTree::SeqStm(
																			new IRTree::SeqStm(
																								new IRTree::LabelStm(t),
																								new IRTree::SeqStm(
																													new IRTree::MoveStm(
																																		new IRTree::TempExp(temp),
																																		new IRTree::ConstExp(1)
																																		),
																													new IRTree::JumpStm(new IRTree::NameExp(q),{q})
																													)
																			),
																			new IRTree::SeqStm(
																								new IRTree::LabelStm(f),
																								new IRTree::MoveStm(
																													new IRTree::TempExp(temp),
																													right->ToExp()
																													)
																			)
														)
									),
									new IRTree::EseqExp(
														new IRTree::LabelStm(q),
														new IRTree::MemExp(new IRTree::TempExp(temp), booleanSize)
														)
									);
	}

	const IRTree::IStm* ToStm() const
	{
		return new IRTree::ExpStm(this->ToExp());
	}

	const IRTree::IStm* ToConditional(const  IRTree::Label t, const  IRTree::Label f) const
	{
		IRTree::Label z("rightFalse");
		//Корректно обработаем конънкцию, как поддерево с как минимум двумя условными переходами
		return new IRTree::SeqStm(
								new IRTree::CJumpStm(
													IRTree::compareOpType::GT,
													left,
													new IRTree::ConstExp(0),
													t,
													z
													),
								new IRTree::SeqStm(
													new IRTree::LabelStm(z),
													right->ToConditional(t, f)
													)
								);
	}

private:
	const IRTree::IExp* left;
	const ISubtreeWrapper* right;
};

//Конвертер для операции >
class BinopGreaterExpWrapper : public ISubtreeWrapper
{
public:

	BinopGreaterExpWrapper(const IRTree::IExp* _left, const IRTree::IExp* _right) : left(_left), right(_right) {}

	const IRTree::IExp* ToExp() const
	{
		return new IRTree::BinopExp(IRTree::binOpType::MINUS,left,right);
	}

	const IRTree::IStm* ToStm() const
	{
		return new IRTree::ExpStm(this->ToExp());
	}

	const IRTree::IStm* ToConditional(const  IRTree::Label t, const  IRTree::Label f) const
	{
		return new IRTree::CJumpStm(IRTree::compareOpType::GT, left, right, t, f);
	}

private:
	const IRTree::IExp* left;
	const IRTree::IExp* right;
};

//Конвертер для операции <
class BinopLessExpWrapper : public ISubtreeWrapper
{
public:

	BinopLessExpWrapper(const IRTree::IExp* _left, const IRTree::IExp* _right) : left(_left), right(_right) {}

	const IRTree::IExp* ToExp() const
	{
		return new IRTree::BinopExp(IRTree::binOpType::MINUS, right, left);
	}

	const IRTree::IStm* ToStm() const
	{
		return new IRTree::ExpStm(this->ToExp());
	}

	const IRTree::IStm* ToConditional(const  IRTree::Label t, const  IRTree::Label f) const
	{
		return new IRTree::CJumpStm(IRTree::compareOpType::LT, left, right, t, f);
	}

private:
	const IRTree::IExp* left;
	const IRTree::IExp* right;
};

//Конвертер для операции ==
class BinopEqualExpWrapper : public ISubtreeWrapper
{
public:

	BinopEqualExpWrapper(const IRTree::IExp* _left, const IRTree::IExp* _right) : left(_left), right(_right) {}

	const IRTree::IExp* ToExp() const
	{
		IRTree::Temp temp("temp");
		IRTree::Label t("true");
		IRTree::Label f("false");
		IRTree::Label q("quit");
		return new IRTree::EseqExp(
									new IRTree::SeqStm(
														new IRTree::CJumpStm(
																			IRTree::compareOpType::EQ,
																			left,
																			right,
																			t,
																			f
																			),
														new IRTree::SeqStm(
																			new IRTree::SeqStm(
																								new IRTree::LabelStm(t),
																								new IRTree::SeqStm(
																													new IRTree::MoveStm(
																																		new IRTree::TempExp(temp),
																																		new IRTree::ConstExp(1)
																																		),
																													new IRTree::JumpStm(new IRTree::NameExp(q),{q})
																													)
																								),
																			new IRTree::SeqStm(
																								new IRTree::LabelStm(f),
																								new IRTree::MoveStm(
																													new IRTree::TempExp(temp),
																													new IRTree::ConstExp(0)
																													)
																								)
																			)
														),
									new IRTree::EseqExp(
														new IRTree::LabelStm(q),
														new IRTree::MemExp(new IRTree::TempExp(temp), booleanSize)
														)
									);
	}

	const IRTree::IStm* ToStm() const
	{
		return new IRTree::ExpStm(this->ToExp());
	}

	const IRTree::IStm* ToConditional(const  IRTree::Label t, const  IRTree::Label f) const
	{
		return new IRTree::CJumpStm(IRTree::compareOpType::EQ, left, right, t, f);
	}

private:
	const IRTree::IExp* left;
	const IRTree::IExp* right;
};

#pragma endregion

//Фрагмент кода - результат трансляции одной функции
struct CCodeFragment
{
	string fragmentName;
	const IFrame* frame;
	const IRTree::IStm* body;
	CCodeFragment* next=nullptr;

	CCodeFragment(string _fragmentName, const IFrame* _frame, const IRTree::IStm* _body):	fragmentName(_fragmentName), 
																							frame(_frame), body(_body){};


};

//Класс посетителя, который создаёт дерево промежуточного представления
class IRTranslator : public IVisitor
{
public:

	CCodeFragment* programTranslation;	//Результат работы транслятора. 
										//В результате мы получим IR-деревья для всех методов в программе

	//Задать таблицу символов
	void SetSymbolTable(const Info* _symbolTable)
	{
		symbolTable = _symbolTable;
	}

	//Задать иерархию классов
	void SetClassHierarchy(ClassHierarchy* _cHierarchy)
	{
		cHierarchy = _cHierarchy;
	}

	//Задать список записей активации (фреймов)
	void SetFrameTable(const Info* _frameTable)
	{
		frameTable = _frameTable;
	}

	rValue visit(const Program* n)
	{
		rValue r;

		CreateClassTable(symbolTable);//Выделяем из таблицы символов таблицу классов
		

		//Получение дерева
		n->mClass->Accept(this);
		for (auto cDeclaration : n->classes)
			cDeclaration->Accept(this);

		//Вывод информации
		currentTranslation = programTranslation;
		while (currentTranslation != nullptr)
		{
			IRTree::treeDependencies.push_back(currentTranslation->fragmentName + "->" + currentTranslation->body->name);
			currentTranslation->body->Print();
			currentTranslation = currentTranslation->next;
		}

		IRTree::PrintTree();

		return r;
	}

	rValue visit(const IMainClass* n)
	{
		rValue r;

		//Инициализация
		programTranslation = new CCodeFragment(
			"Main",
			new X86MiniJavaFrame(),
			n->statement->Accept(this).info->GetTreeWrapper()->ToStm()
			);

		currentTranslation = programTranslation;

		return r;
	}

	rValue visit(const IClassDeclaration* n)
	{
		rValue r;

		//Получим всю необходимую информацию о классе
		currentClassName = n->name;
		ClassHierarchy* classInHierarchy = cHierarchy->FindDescendant(currentClassName);

		classOffsets = GetClassVarsOffsetsDict(GetClassVars(classInHierarchy));
		classSizes = GetClassVarsSizesDict(GetClassVars(classInHierarchy));
		classTypes = GetClassTypesDict(GetClassVars(classInHierarchy));
		classFrames = GetClassFramesList(classInHierarchy);

		//Пройдём по всем методам и составим по ним IR-деревья
		for (int i = 0; i < n->methods.size();i++)
		{
			currentFrame = classFrames[i];
			n->methods[i]->Accept(this);
		}

		return r;
	}

	rValue visit(const IVarDeclaration* n)
	{
		rValue name;
		return name;
	}

	rValue visit(const IMethodDeclaration* n)
	{
		rValue r;

		const IRTree::IStm* body;
		vector<const IRTree::IStm*> stms;
		for (auto statement : n->statements)
			stms.push_back(statement->Accept(this).info->GetTreeWrapper()->ToStm());

		if (stms.size() > 0)
			body = stms[stms.size() - 1];
		else
			body = new IRTree::ExpStm(new IRTree::ConstExp(0));
		for (int i = stms.size() - 2; i >= 0; i--)
			body = new IRTree::SeqStm(stms[i], body);

		//Добавим новый фрагмент кода
		body = new IRTree::ExpStm(new IRTree::EseqExp(body, n->e->Accept(this).info->GetTreeWrapper()->ToExp()));
		CCodeFragment* newTranslation = new CCodeFragment(currentClassName->str + "_" + n->name->str, currentFrame, body);
		currentTranslation->next = newTranslation;
		currentTranslation = newTranslation;

		return r;
	}


	rValue visit(const CompoundStatement* n)
	{
		rValue r;

		const IRTree::IStm* body;
		vector<const IRTree::IStm*> stms;
		for (auto statement : n->statements)
			stms.push_back(statement->Accept(this).info->GetTreeWrapper()->ToStm());

		if (stms.size() > 0)
			body = stms[stms.size() - 1];
		else
			body = new IRTree::ExpStm(new IRTree::ConstExp(0));
		for (int i = stms.size() - 2; i >= 0; i--)
			body = new IRTree::SeqStm(stms[i], body);

		r.info = new SubtreeWrapperInfo(new StmWrapper(body));

		return r;
	}

	rValue visit(const ConditionalStatement* n)
	{
		rValue r;

		const ISubtreeWrapper* ifExpWrapper = n->ifExp->Accept(this).info->GetTreeWrapper();
		const ISubtreeWrapper* thenStateWrapper = n->thenState->Accept(this).info->GetTreeWrapper();
		const ISubtreeWrapper* elseStateWrapper = n->elseState->Accept(this).info->GetTreeWrapper();

		IRTree::IStm* body;
		IRTree::Label t("true");
		IRTree::Label f("false");
		IRTree::Label q("quitCondition");

		body = new IRTree::SeqStm(new IRTree::SeqStm(
			ifExpWrapper->ToConditional(t, f),
			new IRTree::SeqStm(
				new IRTree::SeqStm(
					new IRTree::LabelStm(t),
					new IRTree::SeqStm(
						thenStateWrapper->ToStm(),
						new IRTree::JumpStm(new IRTree::NameExp(q), { q })
						)
					),
				new IRTree::SeqStm(
					new IRTree::LabelStm(f),
					elseStateWrapper->ToStm()
					)
				)
			), new IRTree::LabelStm(q));

		r.info = new SubtreeWrapperInfo(new StmWrapper(body));
		return r;
	}

	rValue visit(const CycleStatement* n)
	{
		rValue r;

		const ISubtreeWrapper* conditionExpWrapper = n->conditionExp->Accept(this).info->GetTreeWrapper();
		const ISubtreeWrapper* actionStateWrapper = n->actionState->Accept(this).info->GetTreeWrapper();

		IRTree::IStm* body;
		IRTree::Label t("true");
		IRTree::Label f("false");

		body = new IRTree::SeqStm(new IRTree::SeqStm(
			conditionExpWrapper->ToConditional(t, f),
			new IRTree::SeqStm(new IRTree::LabelStm(t), actionStateWrapper->ToStm())
			), new IRTree::LabelStm(f));

		r.info = new SubtreeWrapperInfo(new StmWrapper(body));
		return r;
	}

	rValue visit(const PrintStatement* n)
	{
		rValue r;

		IRTree::ExpList* args = new IRTree::ExpList(n->e->Accept(this).info->GetTreeWrapper()->ToExp(), nullptr);
		IRTree::IStm* body = new IRTree::ExpStm(new IRTree::CallExp
			(
				new IRTree::NameExp(IRTree::Label("print", false)),
				args
				));
		const StmWrapper* wrapper = new StmWrapper(body);
		r.info = new SubtreeWrapperInfo(wrapper);
		return r;
	}

	rValue visit(const AssignStatement* n)
	{
		rValue r;

		const IRTree::IExp* dst;
		if (currentFrame->CheckLocalOrFormal(n->varName))
			dst = currentFrame->FindLocalOrFormal(n->varName)->GetExp(currentFrame->FP());
		else
			dst = GetClassVariableExp(n->varName);

		r.info = new SubtreeWrapperInfo(new StmWrapper(new IRTree::MoveStm(dst, n->e->Accept(this).info->GetTreeWrapper()->ToExp())));

		return r;
	}

	rValue visit(const AssignArrayElementStatement* n)
	{
		//Когда работаем с массивом, помним, что он начинается с ячейки размером int, в которой находится длина массива

		rValue r;

		const IRTree::IExp* dst;
		if (currentFrame->CheckLocalOrFormal(n->varName))
		{
			const IRTree::IExp* arr;
			const IAccess* acc = currentFrame->FindLocalOrFormal(n->varName);
			arr = acc->GetExp(currentFrame->FP());
			int size = 0;
			if (acc->GetVarType() == T_VariableType::VT_ShortArray)
				size = shortSize;
			else
				size = intSize;
			dst = new IRTree::MemExp(
				new IRTree::BinopExp(
					IRTree::binOpType::PLUS,
					arr,
					new IRTree::BinopExp
					(
						IRTree::binOpType::PLUS,
						new IRTree::BinopExp(
											IRTree::binOpType::MULTIPLY,
											n->index->Accept(this).info->GetTreeWrapper()->ToExp(),
											new IRTree::ConstExp(size)),
						new IRTree::ConstExp(intSize))),
				size
				);

		}
		else
		{
			const IRTree::IExp* arr;
			arr = GetClassVariableExp(n->varName);
			int size = classTypes[n->varName]->typeName->str == "array of short" ? shortSize : intSize;
			dst = new IRTree::MemExp(
				new IRTree::BinopExp(
					IRTree::binOpType::PLUS,
					arr,
					new IRTree::BinopExp
					(
						IRTree::binOpType::PLUS,
						new IRTree::BinopExp(
							IRTree::binOpType::MULTIPLY, 
							n->index->Accept(this).info->GetTreeWrapper()->ToExp(),
							new IRTree::ConstExp(size)
							),
						new IRTree::ConstExp(intSize)
						)
					),
				size
				);
		}

		const IRTree::IStm* body;

		body = new IRTree::MoveStm(dst, n->e->Accept(this).info->GetTreeWrapper()->ToExp());

		r.info = new SubtreeWrapperInfo(new StmWrapper(body));

		return r;
	}

	rValue visit(const BinopExp* n)
	{
		rValue r;

		ISubtreeWrapper* wrapper=nullptr;

		const Info* info1 = n->e1->Accept(this).info;
		const Info* info2 = n->e2->Accept(this).info;
		const IType* typ=nullptr;


		switch (n->opType)
		{
		case binOpType::AND:
			wrapper = new BinopAndExpWrapper(info1->GetTreeWrapper()->ToExp(),
				info2->GetTreeWrapper());
			typ = new IType("bool");
		case binOpType::EQUAL:
			wrapper = new BinopEqualExpWrapper(info1->GetTreeWrapper()->ToExp(),
				info2->GetTreeWrapper()->ToExp());
			typ = new IType("bool");
		case binOpType::GREATER:
			wrapper = new BinopGreaterExpWrapper(info1->GetTreeWrapper()->ToExp(),
				info2->GetTreeWrapper()->ToExp());
			typ = new IType("bool");
		case binOpType::LESS:
			wrapper = new BinopLessExpWrapper(info1->GetTreeWrapper()->ToExp(),
				info2->GetTreeWrapper()->ToExp());
			typ = new IType("bool");
		case binOpType::MINUS:
			wrapper = new ExpWrapper(new IRTree::BinopExp(IRTree::binOpType::MINUS,
				info1->GetTreeWrapper()->ToExp(),
				info2->GetTreeWrapper()->ToExp()));
			typ = GetGreatestType({ info1->GetType(),info2->GetType() });
		case binOpType::MOD:
			wrapper = new ExpWrapper(new IRTree::BinopExp(IRTree::binOpType::MOD,
				info1->GetTreeWrapper()->ToExp(),
				info2->GetTreeWrapper()->ToExp()));
			typ = GetGreatestType({ info1->GetType(),info2->GetType() });
		case binOpType::MULTIPLY:
			wrapper = new ExpWrapper(new IRTree::BinopExp(IRTree::binOpType::MULTIPLY,
				info1->GetTreeWrapper()->ToExp(),
				info2->GetTreeWrapper()->ToExp()));
			typ = GetGreatestType({ info1->GetType(),info2->GetType() });
		case binOpType::OR:
			wrapper = new BinopOrExpWrapper(info1->GetTreeWrapper()->ToExp(),
				info2->GetTreeWrapper());
			typ = new IType("bool");
		case binOpType::PLUS:
			wrapper = new ExpWrapper(new IRTree::BinopExp(IRTree::binOpType::PLUS,
				info1->GetTreeWrapper()->ToExp(),
				info2->GetTreeWrapper()->ToExp()));
			typ = GetGreatestType({ info1->GetType(),info2->GetType() });
		}

		r.info = new SubtreeWrapperInfo(typ, wrapper);
		return r;
	}

	rValue visit(const TernExp* n)
	{
		rValue r;

		const Info* info1 = n->e1->Accept(this).info;
		const Info* info2 = n->e2->Accept(this).info;
		const Info* info3 = n->e3->Accept(this).info;

		int size = GetTypeSize(GetGreatestType({ info2->GetType(),info3->GetType() }));
		IRTree::Temp temp("temp");
		IRTree::Label t("true");
		IRTree::Label f("false");
		IRTree::Label q("quitTernExp");
		IRTree::IExp* body = new IRTree::EseqExp
			(
				new IRTree::SeqStm
				(
					info1->GetTreeWrapper()->ToConditional(t, f),
					new IRTree::SeqStm
					(
						new IRTree::SeqStm
						(
							new IRTree::LabelStm(t),
							new IRTree::SeqStm
							(
								new IRTree::MoveStm
								(
									new IRTree::TempExp(temp),
									info2->GetTreeWrapper()->ToExp()
									),
								new IRTree::JumpStm(new IRTree::NameExp(q), { q })
								)
							),
						new IRTree::SeqStm
						(
							new IRTree::LabelStm(f),
							new IRTree::MoveStm
							(
								new IRTree::TempExp(temp),
								info3->GetTreeWrapper()->ToExp()
								)
							)
						)
					),
				new IRTree::EseqExp(new IRTree::LabelStm(q), new IRTree::MemExp(new IRTree::TempExp(temp), size))
				);

		r.info = new SubtreeWrapperInfo(GetGreatestType({ info2->GetType(),info3->GetType() }), new ExpWrapper(body));

		return r;
	}

	rValue visit(const GetArrayElementExp* n)
	{
		//Когда работаем с массивом, помним, что он начинается с ячейки размером int, в которой находится длина массива
		rValue r;

		const Info* info1 = n->e1->Accept(this).info;
		const Info* info2 = n->e2->Accept(this).info;

		const IType* elementType = new IType(getIntern(info1->GetType()->typeName == getIntern("array of short") ? "short" : "int"));
		int size = GetTypeSize(elementType);
		IRTree::IExp* body = new IRTree::MemExp
			(
				new IRTree::BinopExp
				(
					IRTree::binOpType::PLUS,
					info1->GetTreeWrapper()->ToExp(),
					new IRTree::BinopExp
					(
						IRTree::binOpType::PLUS,
						info2->GetTreeWrapper()->ToExp(),
						new IRTree::ConstExp(intSize)
						)
					),
				size
				);
		r.info = new SubtreeWrapperInfo(elementType, new ExpWrapper(body));

		return r;
	}

	rValue visit(const GetLengthExp* n)
	{
		//Когда работаем с массивом, помним, что он начинается с ячейки размером int, в которой находится длина массива
		rValue r;

		const Info* info = n->e1->Accept(this).info;

		IRTree::IExp* body = new IRTree::MemExp(info->GetTreeWrapper()->ToExp(), intSize);

		r.info = new SubtreeWrapperInfo(new IType(getIntern("int")), new ExpWrapper(body));

		return r;
	}

	rValue visit(const MethodExp* n)
	{
		rValue r;

		//И всё это ради того, чтобы узнать тип возвращаемой функции. А то мало ли. А вообще, это ерунда, так как типы одного размера
		const Info* classInfo = n->e1->Accept(this).info;
		vector<const Info*> argInfos;
		for (auto arg : n->args)
			argInfos.push_back(arg->Accept(this).info);
		Info* args = new ContainerInfo(argInfos);
		unordered_map<const Symbol*, vector<const Info*>> methodsInfo = 
												GetClassMethods(cHierarchy->FindDescendant(classInfo->GetType()->typeName));
		const Info* methodInfo = FindMethodByName(methodsInfo, n->methodName, args);
		const IType* typ = new IType(methodInfo != nullptr ? methodInfo->GetType()->typeName : getIntern("unknown"));

		IRTree::ExpList* eList=nullptr;
		for (int i = argInfos.size() - 1; i >= 0;i--)
			eList = new IRTree::ExpList(argInfos[i]->GetTreeWrapper()->ToExp(), eList);
		eList = new IRTree::ExpList(classInfo->GetTreeWrapper()->ToExp(),eList);
		IRTree::IExp* body = new IRTree::CallExp(new IRTree::NameExp(IRTree::Label(n->methodName->str, false)), eList);
			
		r.info = new SubtreeWrapperInfo(typ,new ExpWrapper(body));

		return r;
	}

	rValue visit(const NumExp* n)
	{
		rValue r;
		r.info = new SubtreeWrapperInfo(new IType(getIntern("int")), new ExpWrapper(new IRTree::ConstExp(n->num)));
		return r;
	}

	rValue visit(const BoolExp* n)
	{
		rValue r;
		r.info = new SubtreeWrapperInfo(new IType(getIntern("bool")), new ExpWrapper(new IRTree::ConstExp(n->flag?1:0)));
		return r;
	}

	rValue visit(const IDExp* n)
	{
		rValue r;

		const IRTree::IExp* dst;
		const IType* typ;
		if (currentFrame->CheckLocalOrFormal(n->id))
		{
			const IAccess* acc = currentFrame->FindLocalOrFormal(n->id);
			dst = acc->GetExp(currentFrame->FP());
			typ =  GetType(acc->GetVarType());
		}
		else
		{
			dst = GetClassVariableExp(n->id);
			typ = classTypes[n->id];
		}
		r.info = new SubtreeWrapperInfo(typ,new ExpWrapper(dst));

		return r;
	}

	rValue visit(const ThisExp* n)
	{
		//this, т.е. указатель на экземпляр класса, выполняющего метод, всегда находится в регистре r1
		rValue r;

		r.info = new SubtreeWrapperInfo(new IType(currentClassName), 
								new ExpWrapper(new IRTree::MemExp(new IRTree::TempExp(IRTree::Temp("r1",false)),referenceSize)));
		return r;
	}

	rValue visit(const GetArrayExp* n)
	{
		rValue r;

		int elementSize = n->typ->typeName == getIntern("int") ? intSize : shortSize;
		const Info* info = n->e1->Accept(this).info;
		IRTree::Temp temp("temp");
		IRTree::IExp* body = new IRTree::EseqExp
									(
									new IRTree::SeqStm(
										new IRTree::MoveStm
											(
												new IRTree::TempExp(temp),
												new IRTree::CallExp
												(
													new IRTree::NameExp(IRTree::Label("malloc", false)),
													new IRTree::ExpList
													(
														new IRTree::BinopExp
														(
															IRTree::binOpType::PLUS,
															new IRTree::BinopExp
															(
																IRTree::binOpType::MULTIPLY,
																info->GetTreeWrapper()->ToExp(),
																new IRTree::ConstExp(elementSize)
																),
															new IRTree::ConstExp(intSize)
															),
														nullptr
													)
												)
											),
										new IRTree::MoveStm
											(
												new IRTree::TempExp(temp),
												info->GetTreeWrapper()->ToExp()//Заносим длину в первые байты массива
											)
										),
										new IRTree::TempExp(temp)											
									);
		r.info = new SubtreeWrapperInfo(new IType(getIntern(n->typ->typeName == getIntern("int") ?
																								"array of int":
																								"array of short")),
										new ExpWrapper(body));

		return r;
	}

	rValue visit(const NewObjectExp* n)
	{
		rValue r;

		int classSize = GetClassSize(cHierarchy->FindDescendant(n->typName));
		IRTree::IExp* body= new IRTree::CallExp
			(
				new IRTree::NameExp(IRTree::Label("malloc", false)),
				new IRTree::ExpList(new IRTree::ConstExp(classSize),nullptr)
			);

		//IRTree::IExp* body = new IRTree::CallExp();
		r.info = new SubtreeWrapperInfo(new IType(n->typName),new ExpWrapper(body));
		return r;
	}

	rValue visit(const NegativeExp* n)
	{
		rValue r;

		IRTree::Temp temp("temp");
		IRTree::Label t("true");
		IRTree::Label f("false");
		IRTree::Label q("quit");

		IRTree::IExp* body= 
			new IRTree::EseqExp(
				new IRTree::SeqStm(
					new IRTree::CJumpStm(
						IRTree::compareOpType::GT,
						n->e1->Accept(this).info->GetTreeWrapper()->ToExp(),
						new IRTree::ConstExp(0),
						t,
						f
						),
					new IRTree::SeqStm(
						new IRTree::SeqStm(
							new IRTree::LabelStm(t),
							new IRTree::SeqStm(
								new IRTree::MoveStm(
									new IRTree::TempExp(temp),
									new IRTree::ConstExp(0)
									),
								new IRTree::JumpStm(new IRTree::NameExp(q), { q })
								)
							),
						new IRTree::SeqStm(
							new IRTree::LabelStm(f),
							new IRTree::MoveStm(
								new IRTree::TempExp(temp),
								new IRTree::ConstExp(1)
								)
							)
						)
					),
				new IRTree::EseqExp(
					new IRTree::LabelStm(q),
					new IRTree::MemExp(new IRTree::TempExp(temp), booleanSize)
					)
			);

		r.info = new SubtreeWrapperInfo(new IType(getIntern("bool")), new ExpWrapper(body));
		return r;
	}

	rValue visit(const EnclosedExp* n)
	{
		return n->e1->Accept(this);
	}

private:

	//ofstream fout;//Файловый поток, по которому происходит вывод информации

	CCodeFragment* currentTranslation=nullptr;

	const Info* symbolTable = nullptr;//Таблица всех символов программы

	Info* classTable;//Информация о всех классах
	ClassHierarchy* cHierarchy;//Иерархия всех классов программы
	const Symbol* currentClassName;//Название класса, который рассматривается в данный момент

	const Info* frameTable;//Таблица, в которой находится информация о фреймах
	unordered_map<const Symbol*, int> classOffsets;//Информация о том, как расположены друг относительно друга переменные класса
	unordered_map<const Symbol*, int> classSizes;//Информация о размерах переменных класса
	unordered_map<const Symbol*, const IType*> classTypes;//Информация о типах переменных класса

	vector<const IFrame*> classFrames;//Список всех фреймов, соответствующих методам рассматриваемого в 
															//данный момент класса

	const IFrame* currentFrame;

	const IType* GetType(T_VariableType _typ)
	{
		switch (_typ)
		{
		case T_VariableType::VT_Boolean:
			return new IType(getIntern("bool"));
		case T_VariableType::VT_Int:
			return new IType(getIntern("int"));
		case T_VariableType::VT_IntArray:
			return new IType(getIntern("array of int"));
		case T_VariableType::VT_Short:
			return new IType(getIntern("short"));
		case T_VariableType::VT_ShortArray:
			return new IType(getIntern("array of short"));
		case T_VariableType::VT_UserClass:
			return new IType(getIntern("user class"));

		}
	}

	//Если сложить short и int должен получиться int.
	//Эта функция помогает учесть такое
	const IType* GetGreatestType(vector<const IType*> typs)
	{
		for (auto typ : typs)
			if (typ->typeName == getIntern("int"))
				return typ;
		return typs[0];
	}

	//Вернуть размер в зависимости от типа
	int GetTypeSize(const IType* typ)
	{
		if (typ->typeName == getIntern("int"))
			return intSize;
		else if (typ->typeName == getIntern("short"))
			return shortSize;
		else if (typ->typeName == getIntern("bool"))
			return booleanSize;
		else
			return referenceSize;
	}

	bool CompareTypes(const IType* typ1, const IType* typ2)
	{
		if ((typ1->typeName == getIntern("short") || typ1->typeName == getIntern("int")) &&
			(typ2->typeName == getIntern("short") || typ2->typeName == getIntern("int")))
				return true;
		else return typ1->typeName == typ2->typeName;
	}

	//Создать таблицу с информацией обо всех классах, используемых в программе
	void CreateClassTable(const Info* inf)
	{
		classTable = new ContainerInfo({});
		for (auto cInfo : inf->GetNestedInfo())
			if (FindClassInfo(cInfo->GetName()) == nullptr)
				classTable->PushNestedInfo(cInfo);
	}

	//Вернуть информацию о классе с данным именем
	const Info* FindClassInfo(const Symbol* className)
	{
		for (auto cInfo : classTable->GetNestedInfo())
		{
			if (cInfo->GetName() == className)
				return cInfo;
		}
		return nullptr;
	}

	//Получить список переменных, которые находятся в области видимости данного класса
	const Info* GetClassVars(ClassHierarchy* _cHierarchy)
	{
		Info* varsInfo = new ContainerInfo({});

		vector<const Symbol*> classesNames = _cHierarchy->GetClassHierarchyLine();//Получить названия всех родительских классов
		for (const Symbol* className : classesNames)
		{
			const Info* cInfo = FindClassInfo(className);
			if (cInfo == nullptr)
				continue;
			for (const Info* varInfo : cInfo->GetNestedInfo())
			{
				if (varInfo->GetInfoType() != "var")
					continue;
				varsInfo->PushNestedInfo(varInfo);
			}
		}

		return varsInfo;
	}

	//Получить информацию об аргументах указанного метода
	const Info* GetMethodArgs(const Info* methodInfo)
	{
		Info* argsInfo = new ContainerInfo({});
		for (auto argInfo : methodInfo->GetNestedInfo())
			if (argInfo->GetInfoType() == "arg")
				argsInfo->PushNestedInfo(argInfo);
		return argsInfo;
	}

	//Сравнить аргументы указанного метода с указанным списком
	bool CompareMethodArgs(const Info* methodInfo, const Info* argsInfo)
	{
		vector<const Info*> methodArgs = methodInfo->GetNestedInfo();
		vector<const Info*> args = argsInfo->GetNestedInfo();
		if (methodArgs.size() != args.size())//Сравнение по размеру списков аргументов
		{
			return false;
		}
		for (int i = 0; i < methodArgs.size(); i++)//Если список аргументов подходит методу, значит все типы тоже должны совпадать
			if (!CompareTypes(methodArgs[i]->GetType(),args[i]->GetType()))
			{
				return false;
			}
		return true;
	}

	//Сравнить аргументы двух методов
	bool CompareMethods(const Info* method1, const Info* method2)
	{
		return CompareMethodArgs(method1, GetMethodArgs(method2)) && method1->GetName() == method2->GetName();
	}

	//Проверить наличие указанного метода в списке methodsInfo
	bool HaveMethod(unordered_map<const Symbol*, vector<const Info*>> methodsInfo, const Info* methodInfo)
	{
		auto res = methodsInfo.find(methodInfo->GetName());
		if (res == methodsInfo.end())
			return false;
		for (const Info* _methodInfo : methodsInfo[methodInfo->GetName()])
			if (CompareMethods(methodInfo, _methodInfo))
				return true;
		return false;
	}

	//Вернуть все методы, которые может вызывать экземпляр данного класса
	unordered_map<const Symbol*, vector<const Info*>> GetClassMethods(ClassHierarchy* _cHierarchy)
	{
		unordered_map<const Symbol*, vector<const Info*>> methodsInfo;

		vector<const Symbol*> classesNames = _cHierarchy->GetClassHierarchyLine();//Получить названия всех родительских классов
		for (const Symbol* className : classesNames)
		{
			const Info* cInfo = FindClassInfo(className);
			if (cInfo == nullptr)
				continue;
			for (const Info* methodInfo : cInfo->GetNestedInfo())
			{
				if (methodInfo->GetInfoType() != "method")
					continue;
				if (HaveMethod(methodsInfo,methodInfo))
					continue;
				auto res = methodsInfo.find(methodInfo->GetName());
				if (res == methodsInfo.end())
					methodsInfo.insert({ methodInfo->GetName(),{methodInfo} });
				else
					methodsInfo[methodInfo->GetName()].push_back(methodInfo);
			}
		}
		return methodsInfo;
	}

	//Получить размер экземпляра класса
	int GetClassSize(ClassHierarchy* _cHierarchy)
	{
		const Info* classVars = GetClassVars(_cHierarchy);
		int size = 0;
		for (auto varInfo : classVars->GetNestedInfo())
		{
			string typeName = varInfo->GetType()->typeName->str;
			if (typeName == "int")
				size += intSize;
			else if (typeName == "short")
				size += shortSize;
			else if (typeName == "bool")
				size += booleanSize;
			else if (typeName == "array of int")
				size += referenceSize;
			else if (typeName == "array of short")
				size += referenceSize;
			else
				size += referenceSize;
		}
		return size;
	}

	//Вернуть словарь смещений всех переменных класса по имени
	unordered_map<const Symbol*, int> GetClassVarsOffsetsDict(const Info* _classVars)
	{
		unordered_map<const Symbol*, int> offsetDict;
		int offset = 0;
		for (auto varInfo : _classVars->GetNestedInfo())
		{
			offsetDict.insert({varInfo->GetName(),offset});
			string typeName = varInfo->GetType()->typeName->str;
			if (typeName == "int")
				offset += intSize;
			else if (typeName == "short")
				offset += shortSize;
			else if (typeName == "bool")
				offset += booleanSize;
			else if (typeName == "array of int")
				offset += referenceSize;
			else if (typeName == "array of short")
				offset += referenceSize;
			else
				offset += referenceSize;
		}
		return offsetDict;
	}

	//Вернуть словарь размеров всех переменных класса по имени
	unordered_map<const Symbol*, int> GetClassVarsSizesDict(const Info* _classVars)
	{
		unordered_map<const Symbol*, int> sizeDict;
		for (auto varInfo : _classVars->GetNestedInfo())
		{
			int size = 0;
			string typeName = varInfo->GetType()->typeName->str;
			if (typeName == "int")
				size = intSize;
			else if (typeName == "short")
				size = shortSize;
			else if (typeName == "bool")
				size = booleanSize;
			else if (typeName == "array of int")
				size = referenceSize;
			else if (typeName == "array of short")
				size = referenceSize;
			else
				size = referenceSize;
			sizeDict.insert({ varInfo->GetName(),size });
		}
		return sizeDict;
	}

	//Вернуть словарь типов всех переменных класса по имени
	unordered_map<const Symbol*, const IType*> GetClassTypesDict(const Info* _classVars)
	{
		unordered_map<const Symbol*, const IType*> typeDict;
		for (auto varInfo : _classVars->GetNestedInfo())
			typeDict.insert({ varInfo->GetName(),varInfo->GetType() });
		return typeDict;
	}

	//Вернуть словарь фреймов для текущего класса
	vector<const IFrame*> GetClassFramesList(ClassHierarchy* _cHierarchy)
	{
		vector< const IFrame*> classFrames;
		const Info* classInfo=nullptr;
		for (auto _classInfo : frameTable->GetNestedInfo())
		{
			if (_classInfo->GetName() == _cHierarchy->className)
			{
				classInfo = _classInfo;
				break;
			}
		}

		for (auto frameInfo : classInfo->GetNestedInfo())
			classFrames.push_back(frameInfo->GetFrame());
			
		return classFrames;
	}

	const IRTree::IExp* GetClassVariableExp(const Symbol* varName)
	{
		//Считаем, что указатель на объект класса, в котором вызывается метд находится по регистру a1
			
		return new IRTree::MemExp(new IRTree::BinopExp(
														IRTree::binOpType::PLUS,
														new IRTree::TempExp(IRTree::Temp("r1",false)),
														new IRTree::ConstExp(classOffsets[varName])
														), classSizes[varName]);
	}

	//Из заданного списка методов найти тот метод, который имеет заданное имя и заданный список аргументов
	const Info* FindMethodByName(unordered_map<const Symbol*, vector<const Info*>> _methodsInfo, const Symbol* _methodName, const Info* methodArgs)
	{
		//fout << "Начинаем поиск метода " <<_methodName->str<< endl;
		//int i = 0;
		if (_methodsInfo.find(_methodName) == _methodsInfo.end())
			return nullptr;
		for (const Info* _method : _methodsInfo[_methodName])
		{
			if (_method->GetName() == _methodName && CompareMethodArgs(GetMethodArgs(_method), methodArgs))
				return _method;
		}
		return nullptr;
	}

};