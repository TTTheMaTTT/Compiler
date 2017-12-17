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
	virtual const int GetSize() const = 0;
};

class InFrameAccess : public IAccess {
public:
	InFrameAccess(T_RecordsType _type, int _size, int _offset, int _address) : size(_size), address(_address), offset(_offset), recordType(_type) {}
	virtual const int GetSize() const { return size; }
	virtual const T_RecordsType GetRecordType() { return recordType; }
	const int Offset() const { return offset; }
	const int Address() const {	return address;	}
private:
	const int size;
	int address;
	const int offset;
	const T_RecordsType recordType;
};

class InRegAccess : public IAccess {
public:
	InRegAccess(T_RecordsType _type, int _size, int _regNumber) : type(_type), size(_size), regNumber(_regNumber) {}
	virtual const int GetSize() const override { return size; }
	virtual const T_RecordsType GetRecordType() override { return type; }
	virtual const int GetRegNumber() const { return regNumber; }

private:
	T_RecordsType type;
	int size;
	int regNumber;
};
