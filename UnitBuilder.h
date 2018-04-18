#pragma once
#include "Structure.h"
class UnitBuilder :	public Structure
{
public:
	UnitBuilder(const Position &p, const int c, int h, int cost);
	~UnitBuilder();
	virtual IUnit * GetUnit(const wchar_t *f, const Position &p, const int c, char id) = 0;
	const int & UnitBuilder::GetColour() const;
	const int & UnitBuilder::GetHealth() const;
	void UnitBuilt();
	void Reset();
	const bool IsUnitAvail();

protected:
	int colour;
	Size size;
	int unitsAvail = 1;
};

inline const bool UnitBuilder::IsUnitAvail()
{
	return unitsAvail;
}

inline void UnitBuilder::UnitBuilt()
{
	unitsAvail--;
}

inline void UnitBuilder::Reset()
{
	unitsAvail = 1;
}