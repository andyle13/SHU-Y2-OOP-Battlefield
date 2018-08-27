#include "UnitBuilder.h"

UnitBuilder::UnitBuilder(const Position &p, const int & c, int h, const int & cost)
	: Structure(p, { 2,2 }, c, h, cost), size({ 2,2 }), hasPlaced(false) {}


UnitBuilder::~UnitBuilder() {}

const int & UnitBuilder::GetColour() const
{
	return IUnit::GetColour();
}

const int & UnitBuilder::GetHealth() const
{
	return IUnit::GetHealth();
}

const bool UnitBuilder::CanPlaceUnit() const {
	return hasPlaced;
}

void UnitBuilder::UnitPlaced() {
	hasPlaced = true;
}