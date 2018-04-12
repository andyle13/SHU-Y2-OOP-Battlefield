#pragma once
#include "IUnit.h"
class UnitBuilder :	public IUnit
{
public:
	UnitBuilder(const Position &p, int h, int c);
	~UnitBuilder();

	virtual IUnit * GetUnit(const wchar_t *f, const Position &p, const int c, char id) = 0;

protected:
	int colour;
	Size size;
};

