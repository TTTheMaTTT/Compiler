#pragma once

#include <unordered_map> 
#include <vector>
#include <string>
#include <memory>

static const int WORD_SIZE = 4;
static const int MAX_IN_REG = 4;

static const int intSize = 1 * WORD_SIZE;
static const int shortSize = 1 * WORD_SIZE;
static const int booleanSize = 1 * WORD_SIZE;
static const int referenceSize = 1 * WORD_SIZE;

int typeSize(T_VariableType type) {
	switch (type) {
	case VT_Int:
		return intSize;
	case VT_Short:
		return shortSize;
	case VT_IntArray:
		return referenceSize;
	case VT_ShortArray:
		return referenceSize;
	case VT_Boolean:
		return booleanSize;
	case VT_UserClass:
		return referenceSize;
	default:
		return referenceSize;
	}
}

class X86MiniJavaFrame : public IFrame {
	/*
	* LocalAddress = access address + FP
	* FormalAddress = access address or regIndex
	*/
public:

	void AddFormal(const IType* typ, const Symbol* name)
	{
		cout << "formal";
		T_VariableType type = VT_UserClass;
		if ((typ->typeName->str) == "int")
			type = VT_Int;
		if ((typ->typeName->str) == "short")
			type = VT_Short;
		if ((typ->typeName->str) == "bool")
			type = VT_Boolean;
		if ((typ->typeName->str) == "array of int")
			type = VT_IntArray;
		if ((typ->typeName->str) == "array of short")
			type = VT_ShortArray;

		IAccess* var = createFormal(RT_Formal, typeSize(type));
		formalAccess.insert(make_pair(name, std::unique_ptr<IAccess>(var)));
		formalList.push_back(var);
	}

	void AddLocal(const IType* typ, const Symbol* name)
	{
		cout << "Local";
		T_VariableType type = VT_UserClass;
		if ((typ->typeName->str) == "int")
			type = VT_Int;
		if ((typ->typeName->str) == "short")
			type = VT_Short;
		if ((typ->typeName->str) == "bool")
			type = VT_Boolean;
		if ((typ->typeName->str) == "array of int")
			type = VT_IntArray;
		if ((typ->typeName->str) == "array of short")
			type = VT_ShortArray;

		IAccess* var = createLocal(typeSize(type));
		localAccess.insert(make_pair(name, std::unique_ptr<IAccess>(var)));
	}

	int FormalsCount() const { return formalList.size(); }

	const IAccess* Formal(int index) const { return formalList[index]; }

	const IAccess* FindLocalOrFormal(const Symbol* name) const
	{
		auto res = localAccess.find(name);
		if (res == localAccess.end()) {
			res = formalAccess.find(name);
		}
		return res->second.get();
	}

	const int FormalSize(int index) const { return formalList[index]->GetSize(); }

	const int FormalSize(const Symbol* name) const {
		auto res = formalAccess.find(name);
		return res->second->GetSize();
	}

	const int FP() const { return formalTopPointer; }

	const int LP() const { return localTopPointer; }

private:
	std::vector<IAccess*> formalList;
	std::unordered_map<const Symbol*, std::unique_ptr<IAccess>> formalAccess;
	std::unordered_map<const Symbol*, std::unique_ptr<IAccess>> localAccess;
	int formalTopPointer = 0;
	int localTopPointer = 0;

	//В регистры можем положить 4 аргумента, если их число выше, то кладем их в стек
	IAccess* createFormal(T_RecordsType type, int size)
	{
		if (formalList.size() < MAX_IN_REG) {
			return new InRegAccess(type, size, formalList.size());
		}
		else {
			IAccess* access = new InFrameAccess(type, size, formalTopPointer, 0);
			formalTopPointer += size;
			return access;
		}
	}

	IAccess* createLocal(int size)
	{
		IAccess* access = new InFrameAccess(RT_Local, size, localTopPointer, 0);
		localTopPointer += size;
		return access;
	}

	ofstream fout;
};
