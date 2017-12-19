namespace IRTree
{

	using namespace std;

	//Типы бинарных операций
	enum class binOpType { PLUS, MINUS, MULTIPLY, MOD, AND, OR, LESS, GREATER, EQUAL };
	enum class compareOpType {EQ, LT, GT};

	static vector<string> treeDependencies;//Здесь записаны все зависимости IRTree

	//Составить строку с числом в скобочках
	string CompoundString(string arg1, int arg2)
	{
		ostringstream ost;
		ost << arg1 << "v" << arg2;
		return ost.str();
	}

	//Сложить строку и число
	string ConcatenateString(string arg1, int arg2)
	{
		ostringstream ost;
		ost << arg1 << arg2;
		return ost.str();
	}

	string IntToString(int arg)
	{
		ostringstream ost;
		ost <<"n"<< arg;
		return ost.str();
	}

	string BinopToString(binOpType _op)
	{
		switch (_op)
		{
		case binOpType::PLUS:
			return "plus";
		case binOpType::MINUS:
			return "minus";
		case binOpType::MULTIPLY:
			return "mul";
		case binOpType::MOD:
			return "mod";
		case binOpType::AND:
			return "and";
		case binOpType::OR:
			return "or";
		case binOpType::EQUAL:
			return "eq";
		case binOpType::LESS:
			return "less";
		case binOpType::GREATER:
			return "greater";
		default:
			return "binOPError";
		}
	}

	string CompareToString(compareOpType _op)
	{
		switch (_op)
		{
		case compareOpType::EQ:
			return "EQ";
		case compareOpType::LT:
			return "LT";
		case compareOpType::GT:
			return "GT";
		default:
			return "compareOpError";
		}
	}

	//Перевод из бинарной операции в операцию сравнения (для корректного перевода exp->conditional
	compareOpType BinopToCompare(binOpType _op)
	{
		compareOpType newOP;
		switch (_op)
		{
		case binOpType::EQUAL:
			return compareOpType::EQ;
		case binOpType::LESS:
			return compareOpType::LT;
		case binOpType::GREATER:
			return compareOpType::GT;
		default:
			return compareOpType::EQ;
		}

	}

	//Функция, которая позволяет создавать уникальные имена для поддеревьев IRTree
	string GetTreeName(string newName)
	{
		static unordered_map<string, int> allTreeNames;
		auto cached = allTreeNames.find(newName);
		if (cached != allTreeNames.end())
		{
			cached->second++;
			return CompoundString(newName, cached->second);
		}
		allTreeNames.insert({ newName,0 });
		return CompoundString(newName, 0);
	}

	//Функция, которая позволяет создавать уникальные имена
	string GetUniqueName(string newName)
	{
		static unordered_map<string, int> allNames;
		auto cached = allNames.find(newName);
		if (cached != allNames.end())
		{
			cached->second++;
			return ConcatenateString(newName, cached->second);
		}
		allNames.insert({ newName,0 });
		return ConcatenateString(newName, 0);
	}

	//Вывести всё дерево в тектовый файл
	void PrintTree()
	{
		ofstream fout;
		fout = ofstream("graph.dot");
		fout << "digraph G" << endl << "{" << endl;
		for (string s : treeDependencies)
			fout << s << endl;
		fout << "}" << endl;
		fout.close();
	}

	//Класс пометки, которая используется для JUMP
	struct Label
	{
		string lName;

		Label(string _lName, bool setUnique=true)
		{
			if (setUnique)
				lName = GetUniqueName(_lName);
			else
				lName = _lName;
		}

	};

	//Класс, характеризующий один из бесконечного числа регистров
	struct Temp
	{
		string tName;

		Temp(string _tName, bool setUnique=true)
		{
			if (setUnique)
				tName = GetUniqueName(_tName);
			else
				tName = _tName;
		}
	};

	//Класс, характеризующий выражение, которое возвращает некоторое значение
	class IExp 
	{
	public:
		string name="";
		virtual ~IExp() {}
		virtual void Print() const= 0;//Зафиксировать все зависимости, исходящие из данного поддерева
	};

	//Список выражений, возвращающих значение
	class ExpList 
	{
	public:

		const IRTree::IExp* head;
		const IRTree::ExpList* tail;

		ExpList(const IExp* _head, const ExpList* _tail):head(_head),tail(_tail){};

		void PrintDependence(string parent) const
		{
			treeDependencies.push_back(parent + "->" + (head->name));
			if (tail != nullptr)
				tail->PrintDependence(parent);
		}

		void Print() const
		{
			head->Print();
			if (tail != nullptr)
				tail->Print();
		}

	};

	//Класс, характеризующий выражение, которое ничего не возвращает
	class IStm
	{
	public:
		string name = "";
		virtual ~IStm() {}
		virtual void Print() const = 0;//Зафиксировать все зависимости, исходящие из данного поддерева
	};

	//Список выражений, не возвращающих значение
	class StmList
	{
	public:

		const IStm* head;
		const StmList* tail;

		StmList(const IStm* _head, const StmList* _tail) : head(_head), tail(_tail) {};
	};

#pragma region expressions

	//Выражение, возвращающее константу
	class ConstExp: public IExp
	{
	public:
		int value;

		ConstExp(int _value) :value(_value) 
		{
			name = GetTreeName("CONST");
		}

		void Print() const
		{
			treeDependencies.push_back(name + "->" + GetTreeName(IntToString(value)));
		}
	};

	//Выражение, возвращающее название
	class NameExp : public IExp
	{
	public:
		const Label label;

		NameExp(const Label _label) :label(_label) 
		{
			name = GetTreeName("NAME");
		}

		void Print() const
		{
			treeDependencies.push_back(name + "->" + GetTreeName(label.lName));
		}

	};

	//Выражение, обращающееся к регистру (в области временных переменных)
	class TempExp : public IExp
	{
	public:
		Temp temp;

		TempExp(Temp _temp) :temp(_temp)
		{
			name = GetTreeName("TEMP");
		}

		void Print() const
		{
			treeDependencies.push_back(name + "->" + GetTreeName(temp.tName));
		}
	};

	//Выражение, возвращающее результат бинарной операции
	class BinopExp : public IExp
	{
	public:
		const binOpType binop;
		const IExp* left;
		const IExp* right;

		BinopExp(binOpType _binop, const IExp* _left, const IExp* _right) : binop(_binop), left(_left), right(_right) 
		{
			name = GetTreeName(BinopToString(_binop));
		};

		void Print() const
		{
			treeDependencies.push_back(name + "->"+(left->name));
			treeDependencies.push_back(name + "->" + (right->name));
			left->Print();
			right->Print();
		}

	};

	//Выражение, возвращающее результат обращения к памяти
	class MemExp : public IExp
	{
	public:
		const IExp* exp; //Выражение, которое возвращает адрес, к которому надо обратиться
		const int size;//размер памяти (в байтах), которую нужно вернуть

		MemExp(const IExp* _exp, int _size) : exp(_exp), size(_size) 
		{
			name = GetTreeName("MEM");
		}

		void Print() const
		{
			treeDependencies.push_back(name + "->" + (exp->name));
			treeDependencies.push_back(name + "->" + GetTreeName(IntToString(size)));
			exp->Print();
		}

	};

	//Выражение, возвращающее результат работы вызываемой функции
	class CallExp : public IExp
	{
	public:
		const IExp* func;
		IRTree::ExpList* args;//Список аргументов

		CallExp(const IExp* _func, ExpList* _args):func(_func),args(_args)
		{
			name = GetTreeName("CALL");
		}

		/*CallExp()
		{
			func = nullptCr;
			args = nullptr;
			name = GetTreeName("CALL");
		}*/

		void Print() const
		{
			treeDependencies.push_back(name + "->" + (func->name));
			args->PrintDependence(name);
			func->Print();
			args->Print();
		}
	};

	//Выражение, выполняющее заданный Stm и возвращающий Exp
	class EseqExp : public IExp
	{
	public:
		const IStm* stm;
		const IExp* exp;

		EseqExp(const IStm* _stm, const IExp* _exp) : stm(_stm), exp(_exp)
		{
			name = GetTreeName("ESEQ");
		}

		void Print() const
		{
			treeDependencies.push_back(name + "->" + (stm->name));
			treeDependencies.push_back(name + "->" + (exp->name));
			stm->Print();
			exp->Print();
		}

	};

#pragma endregion

#pragma region statements

	//Класс, характериующий присваивание
	class MoveStm : public IStm
	{
	public:
		const IExp* dst;
		const IExp* src;

		MoveStm(const IExp* _dst, const IExp* _src) : dst(_dst), src(_src) 
		{
			name = GetTreeName("MOVE");
		}

		void Print() const
		{
			treeDependencies.push_back(name + "->" + (dst->name));
			treeDependencies.push_back(name + "->" + (src->name));
			dst->Print();
			src->Print();
		}

	};

	//Класс, выполняющий работу IExp, но ничего не возвращающее
	class ExpStm : public IStm
	{
	public:
		const IExp* exp;

		ExpStm(const IExp* _exp) : exp(_exp)
		{
			name = GetTreeName("EXP");
		}

		void Print() const
		{
			treeDependencies.push_back(name + "->" + (exp->name));
			exp->Print();
		}

	};

	//Класс, выполняющий переход в метку, указанную в exp
	class JumpStm : public IStm
	{
	public:
		const IExp* exp;//Куда произойдёт переход
		const vector<Label> targets;//Список, в котором описаны всевозможные переходы. Нужен для будущих работ

		//vector<const IStm*> targetStms; - ссылка на stm, на которые можно перейти. Возможно, понадобится в будущем

		JumpStm(const IExp* _exp, const vector<Label> _targets) : exp(_exp), targets(_targets)
		{
			name = GetTreeName("JUMP");
		}

		void Print() const
		{
			treeDependencies.push_back(name + "->" + (exp->name));
			for (int i = 0; i < targets.size(); i++)
				treeDependencies.push_back(name + "->" + GetTreeName(targets[i].lName));
			exp->Print();
		}

	};

	//Класс, выполняющий условный переход в различные метки
	class CJumpStm : public IStm
	{
	public:
		const compareOpType relop;
		const IExp* left;
		const IExp* right;
		Label iftrue;//Куда произойдёт переход, если проверяемое условие - правда
		Label iffalse;//и если это условие - ложь

		//const vector<Label> targets;//Список, в котором описаны всевозможные переходы. Нужен для будущих работ

		//const IStm* trueStm; - ссылки на stm, на которые можно перейти. Возможно, понадобится в будущем
		//const IStm* falseStm;

		CJumpStm(const compareOpType _relop, const IExp* _left, const IExp* _right, Label _iftrue, Label _iffalse) :
													relop(_relop), left(_left), right(_right), iftrue(_iftrue), iffalse(_iffalse)
		{
			name = GetTreeName("CJUMP");
		}

		void Print() const
		{
			treeDependencies.push_back(name + "->" + GetTreeName(CompareToString(relop)));
			treeDependencies.push_back(name + "->" + (left->name));
			treeDependencies.push_back(name + "->" + (right->name));
			treeDependencies.push_back(name + "->" + GetTreeName(iftrue.lName));
			treeDependencies.push_back(name + "->" + GetTreeName(iffalse.lName));
			left->Print();
			right->Print();
		}

	};

	//Класс, создающий последовательность выражений
	class SeqStm :public IStm
	{
	public:

		const IStm* left;
		const IStm* right;

		SeqStm(const IStm* _left, const IStm* _right) : left(_left), right(_right)
		{
			name = GetTreeName("SEQ");
		}

		void Print() const
		{
			treeDependencies.push_back(name + "->" + (left->name));
			treeDependencies.push_back(name + "->" + (right->name));
			left->Print();
			right->Print();
		}
	};

	//Класс, характеризующий выражение пометку. Им можно помечать различные участки дерева, в которые можно производить переход
	class LabelStm :public IStm
	{
	public:

		const Label label;

		//const IStm* labelStm;//Помеченное выражение. Это поле может пригодится потом

		LabelStm(const Label _label) : label(_label)
		{
			name = GetTreeName("LABEL");
		}

		void Print() const
		{
			treeDependencies.push_back(name + "->" + GetTreeName(label.lName));
		}
	};


#pragma endregion

}