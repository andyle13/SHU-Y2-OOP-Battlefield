#pragma once
#include "Structure.h"
class UnitBuilder :	public Structure
{
public:
	UnitBuilder(const Position &p, const int c, int h, int cost);
	~UnitBuilder();
	const bool CanPlaceUnit() const;
	virtual IUnit * GetUnit(const wchar_t *f, const Position &p, const int c, char id) = 0;
<<<<<<< HEAD
	const int & GetColour() const;
	const int & GetHealth() const;
=======
	const int & UnitBuilder::GetColour() const;
	const int & UnitBuilder::GetHealth() const;
	void UnitBuilt();
	void Reset();
	const bool IsUnitAvail();

>>>>>>> daniel
protected:
	Size size;
<<<<<<< HEAD
	int colour;
	bool hasPlaced;
=======
	int unitsAvail = 1;
>>>>>>> daniel
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