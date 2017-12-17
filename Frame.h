#pragma once

#include "Access.h"
#include "Symbol.h"
#include "GrammarDescriptions.h"

class IFrame {
public:
	virtual ~IFrame() { }

	virtual void AddFormal(const IArgumentList* n) = 0;
	virtual void AddLocal(const IVarDeclarationList* n) = 0;
	virtual int FormalsCount() const = 0;
	virtual const IAccess* Formal(int index) const = 0;
	virtual const IAccess* FindLocalOrFormal(const Symbol* _name) const = 0;
};
