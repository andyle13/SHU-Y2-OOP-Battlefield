#pragma once
#include "Structure.h"
class UnitBuilder :	public Structure
{
public:
	UnitBuilder(const Position &p, const int c, int h);
	~UnitBuilder();
	virtual IUnit * GetUnit(const wchar_t *f, const Position &p, const int c, char id) = 0;
	const int & UnitBuilder::GetColour() const;
	const int & UnitBuilder::GetHealth() const;
protected:
	int colour;
	Size size;
};

