#pragma once
#include "IUnit.h"
class UnitBuilder :	public IUnit
{
public:
	UnitBuilder(const Position &p, const int c, int h);
	~UnitBuilder();
	virtual IUnit * GetUnit(const wchar_t *f, const Position &p, const int c, char id) = 0;
	const int & UnitBuilder::GetColour() const;
protected:
	int colour;
	Size size;
};

