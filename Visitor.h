//—труктура, в которую будем оборачивать возвращаемое визиторами значени€, которые могут иметь разные типы
typedef enum { STR, INFO, STRS} rType;
enum class binOpType { PLUS, MINUS, MULTIPLY, MOD, AND, OR, LESS, GREATER, EQUAL };

typedef struct {
	rType typ;// typ is separate.
	string sValue;//кака€-нибудь строка
	Info* info;//кака€-нибудь информаци€ об объекте
} rValue;

// ласс посетител€
class IVisitor
{
public:
	virtual rValue visit(const Program* n) = 0;
	virtual rValue visit(const IMainClass* n) = 0;
	virtual rValue visit(const IClassDeclaration* n) = 0;
	virtual rValue visit(const IVarDeclaration* n) = 0;
	virtual rValue visit(const IMethodDeclaration* n) = 0;
	virtual rValue visit(const CompoundStatement* n) = 0;
	virtual rValue visit(const ConditionalStatement* n) = 0;
	virtual rValue visit(const CycleStatement* n) = 0;
	virtual rValue visit(const PrintStatement* n) = 0;
	virtual rValue visit(const AssignStatement* n) = 0;
	virtual rValue visit(const AssignArrayElementStatement* n) = 0;
	virtual rValue visit(const TernExp* n) = 0;
	virtual rValue visit(const BinopExp* n) = 0;
	virtual rValue visit(const GetArrayElementExp* n) = 0;
	virtual rValue visit(const GetLengthExp* n) = 0;
	virtual rValue visit(const MethodExp* n) = 0;
	virtual rValue visit(const NumExp* n) = 0;
	virtual rValue visit(const BoolExp* n) = 0;
	virtual rValue visit(const IDExp* n) = 0;
	virtual rValue visit(const ThisExp* n) = 0;
	virtual rValue visit(const GetArrayExp* n) = 0;
	virtual rValue visit(const NewObjectExp* n) = 0;
	virtual rValue visit(const NegativeExp* n) = 0;
	virtual rValue visit(const EnclosedExp* n) = 0;
};