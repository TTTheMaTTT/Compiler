//—труктура, в которую будем оборачивать возвращаемое визиторами значени€, которые могут иметь разные типы
typedef enum { STR, INFO} rType;
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
	virtual rValue visit(const AddClassDeclarationList* n) = 0;
	virtual rValue visit(const EmptyClassDeclarationList* n) = 0;
	virtual rValue visit(const IClassDeclaration* n) = 0;
	virtual rValue visit(const AddVarDeclarationList* n) = 0;
	virtual rValue visit(const EmptyVarDeclarationList* n) = 0;
	virtual rValue visit(const IVarDeclaration* n) = 0;
	virtual rValue visit(const AddMethodDeclarationList* n) = 0;
	virtual rValue visit(const EmptyMethodDeclarationList* n) = 0;
	virtual rValue visit(const IMethodDeclaration* n) = 0;
	virtual rValue visit(const AddArgumentList* n) = 0;
	virtual rValue visit(const OnlyArgumentList* n) = 0;
	virtual rValue visit(const ZeroArgumentList* n) = 0;
	virtual rValue visit(const AddStatementList* n) = 0;
	virtual rValue visit(const EmptyStatementList* n) = 0;
	virtual rValue visit(const CompoundStatement* n) = 0;
	virtual rValue visit(const ConditionalStatement* n) = 0;
	virtual rValue visit(const CycleStatement* n) = 0;
	virtual rValue visit(const PrintStatement* n) = 0;
	virtual rValue visit(const AssignStatement* n) = 0;
	virtual rValue visit(const AssignArrayElementStatement* n) = 0;
	virtual rValue visit(const AddExpList* n) = 0;
	virtual rValue visit(const OnlyExpList* n) = 0;
	virtual rValue visit(const ZeroExpList* n) = 0;
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