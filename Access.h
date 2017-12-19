#pragma once

#include <iostream>
#include "Symbol.h"
#include <string>


enum T_RecordsType {
	RT_Formal,
	RT_Local
};
enum T_VariableType {
	VT_Int,
	VT_IntArray,
	VT_Short,
	VT_ShortArray,
	VT_Boolean,
	VT_UserClass
};


class IAccess {
public:
	virtual ~IAccess() {}
	virtual const T_RecordsType GetRecordType() = 0;
	virtual const T_VariableType GetVarType() const = 0;
	virtual const int GetSize() const = 0;

	//Функция, возвращающая соответствующее IAccess'у IR-поддерево
	virtual const IRTree::IExp* GetExp(const IRTree::Temp framePtr) const = 0;

};

class InFrameAccess : public IAccess {
public:
	InFrameAccess(T_RecordsType _type, T_VariableType _varType, int _size, int _offset, int _address) : 
											size(_size), address(_address), offset(_offset), recordType(_type), varType(_varType) {};
	
	virtual const int GetSize() const { return size; }
	
	const T_RecordsType GetRecordType() { return recordType; }
	
	const T_VariableType GetVarType() const { return varType; }

	const int Offset() const { return offset; }
	
	const int Address() const {	return address;	}

	const IRTree::IExp* GetExp(const IRTree::Temp framePtr) const
	{
		return new IRTree::MemExp(new IRTree::BinopExp(
														IRTree::binOpType::PLUS,
														new IRTree::TempExp(framePtr),
														new IRTree::ConstExp(offset)
														), size);
	}

private:
	const int size;
	int address;
	const int offset;
	const T_RecordsType recordType;
	const T_VariableType varType;
};

class InRegAccess : public IAccess {
public:
	InRegAccess(T_RecordsType _type, T_VariableType _varType, int _size, int _regNumber) : 
		type(_type), varType(_varType), size(_size), regNumber(_regNumber),temp(IRTree::ConcatenateString("r", regNumber + 2),false){};
	
	virtual const int GetSize() const override { return size; }
	
	virtual const T_RecordsType GetRecordType() override { return type; }

	const T_VariableType GetVarType() const { return varType; }
	
	virtual const int GetRegNumber() const { return regNumber; }

	const IRTree::IExp* GetExp(const IRTree::Temp framePtr) const
	{
		return new IRTree::TempExp(temp);
	}

private:
	T_RecordsType type;
	T_VariableType varType;
	int size;
	int regNumber;
	IRTree::Temp temp;//Регистр, доступ к которому даёт Access

};
