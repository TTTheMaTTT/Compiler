#pragma once

#include <unordered_map> 
#include <vector>
#include <string>
#include <memory>

namespace X86Sizes
{
	static const int WORD_SIZE = 4;
	static const int MAX_IN_REG = 3;

	static const int intSize = 1 * WORD_SIZE;
	static const int shortSize = 1 * WORD_SIZE;
	static const int booleanSize = 1 * WORD_SIZE;
	static const int referenceSize = 1 * WORD_SIZE;
}

int typeSize(T_VariableType type) {
	switch (type) {
	case VT_Int:
		return X86Sizes::intSize;
	case VT_Short:
		return X86Sizes::shortSize;
	case VT_IntArray:
		return X86Sizes::referenceSize;
	case VT_ShortArray:
		return X86Sizes::referenceSize;
	case VT_Boolean:
		return X86Sizes::booleanSize;
	case VT_UserClass:
		return X86Sizes::referenceSize;
	default:
		return X86Sizes::referenceSize;
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

		IAccess* var = createFormal(RT_Formal,type, typeSize(type));
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

		IAccess* var = createLocal(typeSize(type),type);
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

	//Проверка на наличие переменной в фрейме
	bool CheckLocalOrFormal(const Symbol* name) const
	{
		auto res = localAccess.find(name);
		if (res == localAccess.end()) {
			res = formalAccess.find(name);
			if (res == formalAccess.end())
				return false;
			return true;
		}
		return true;
	}

	const int FormalSize(int index) const { return formalList[index]->GetSize(); }

	const int FormalSize(const Symbol* name) const {
		auto res = formalAccess.find(name);
		return res->second->GetSize();
	}

	const int FTP() const { return formalTopPointer; }

	const int LTP() const { return localTopPointer; }

	const IRTree::Temp FP() const
	{
		return fp;
	}

private:
	std::vector<IAccess*> formalList;
	std::unordered_map<const Symbol*, std::unique_ptr<IAccess>> formalAccess;
	std::unordered_map<const Symbol*, std::unique_ptr<IAccess>> localAccess;
	int formalTopPointer = 0;
	int localTopPointer = 0;
	IRTree::Temp fp=IRTree::Temp("fp",false);

	//В регистры можем положить 4 аргумента, если их число выше, то кладем их в стек
	//Так как мы работаем только с методами классов, значит в каждую функцию первым аргументом передаётся объект класса
	//А значит первый регистр - его
	IAccess* createFormal(T_RecordsType type,T_VariableType _varType, int size)
	{
		if (formalList.size() < X86Sizes::MAX_IN_REG) {
			return new InRegAccess(type,_varType, size, formalList.size());
		}
		else {
			IAccess* access = new InFrameAccess(type, _varType, size, -formalTopPointer-size, 0);
			formalTopPointer += size;
			return access;
		}
	}

	IAccess* createLocal(int size, T_VariableType _varType)
	{
		IAccess* access = new InFrameAccess(RT_Local, _varType, size, localTopPointer, 0);
		localTopPointer += size;
		return access;
	}

	ofstream fout;
};
