#pragma once

class IFrame {
public:
	virtual ~IFrame() { }

	virtual void AddFormal(const IType* typ, const Symbol* name) = 0;
	virtual void AddLocal(const IType* typ, const Symbol* name) = 0;
	virtual int FormalsCount() const = 0;
	virtual const IAccess* Formal(int index) const = 0;
	virtual const IAccess* FindLocalOrFormal(const Symbol* _name) const = 0;
	virtual bool CheckLocalOrFormal(const Symbol* _name) const = 0;
	virtual const IRTree::Temp FP() const=0;

};
