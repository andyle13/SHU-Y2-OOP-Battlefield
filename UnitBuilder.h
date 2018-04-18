#pragma once
#include "Structure.h"
class UnitBuilder :	public Structure
{
public:
	UnitBuilder(const Position &p, const int c, int h, int cost);
	~UnitBuilder();
	const bool CanPlaceUnit() const;
	virtual IUnit * GetUnit(const wchar_t *f, const Position &p, const int c, char id) = 0;
	const int & GetColour() const;
	const int & GetHealth() const;
protected:
	Size size;
	int colour;
	bool hasPlaced;
};

