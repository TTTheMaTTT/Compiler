namespace IRTree
{

	using namespace std;

	//���� �������� ��������
	enum class binOpType { PLUS, MINUS, MULTIPLY, MOD, AND, OR, LESS, GREATER, EQUAL };
	enum class compareOpType {EQ, LT, GT};

	static vector<string> treeDependencies;//����� �������� ��� ����������� IRTree

	//��������� ������ � ������ � ���������
	string CompoundString(string arg1, int arg2)
	{
		ostringstream ost;
		ost << arg1 << "v" << arg2;
		return ost.str();
	}

	//������� ������ � �����
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

	//������� �� �������� �������� � �������� ��������� (��� ����������� �������� exp->conditional
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

	//�������, ������� ��������� ��������� ���������� ����� ��� ����������� IRTree
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

	//�������, ������� ��������� ��������� ���������� �����
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

	//������� �� ������ � �������� ����
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

	//����� �������, ������� ������������ ��� JUMP
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

	//�����, ��������������� ���� �� ������������ ����� ���������
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

	//�����, ��������������� ���������, ������� ���������� ��������� ��������
	class IExp 
	{
	public:
		string name="";
		virtual ~IExp() {}
		virtual void Print() const= 0;//������������� ��� �����������, ��������� �� ������� ���������
	};

	//������ ���������, ������������ ��������
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

	//�����, ��������������� ���������, ������� ������ �� ����������
	class IStm
	{
	public:
		string name = "";
		virtual ~IStm() {}
		virtual void Print() const = 0;//������������� ��� �����������, ��������� �� ������� ���������
	};

	//������ ���������, �� ������������ ��������
	class StmList
	{
	public:

		const IStm* head;
		const StmList* tail;

		StmList(const IStm* _head, const StmList* _tail) : head(_head), tail(_tail) {};
	};

#pragma region expressions

	//���������, ������������ ���������
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

	//���������, ������������ ��������
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

	//���������, ������������ � �������� (� ������� ��������� ����������)
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

	//���������, ������������ ��������� �������� ��������
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

	//���������, ������������ ��������� ��������� � ������
	class MemExp : public IExp
	{
	public:
		const IExp* exp; //���������, ������� ���������� �����, � �������� ���� ����������
		const int size;//������ ������ (� ������), ������� ����� �������

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

	//���������, ������������ ��������� ������ ���������� �������
	class CallExp : public IExp
	{
	public:
		const IExp* func;
		IRTree::ExpList* args;//������ ����������

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

	//���������, ����������� �������� Stm � ������������ Exp
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

	//�����, �������������� ������������
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

	//�����, ����������� ������ IExp, �� ������ �� ������������
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

	//�����, ����������� ������� � �����, ��������� � exp
	class JumpStm : public IStm
	{
	public:
		const IExp* exp;//���� ��������� �������
		const vector<Label> targets;//������, � ������� ������� ������������ ��������. ����� ��� ������� �����

		//vector<const IStm*> targetStms; - ������ �� stm, �� ������� ����� �������. ��������, ����������� � �������

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

	//�����, ����������� �������� ������� � ��������� �����
	class CJumpStm : public IStm
	{
	public:
		const compareOpType relop;
		const IExp* left;
		const IExp* right;
		Label iftrue;//���� ��������� �������, ���� ����������� ������� - ������
		Label iffalse;//� ���� ��� ������� - ����

		//const vector<Label> targets;//������, � ������� ������� ������������ ��������. ����� ��� ������� �����

		//const IStm* trueStm; - ������ �� stm, �� ������� ����� �������. ��������, ����������� � �������
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

	//�����, ��������� ������������������ ���������
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

	//�����, ��������������� ��������� �������. �� ����� �������� ��������� ������� ������, � ������� ����� ����������� �������
	class LabelStm :public IStm
	{
	public:

		const Label label;

		//const IStm* labelStm;//���������� ���������. ��� ���� ����� ���������� �����

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