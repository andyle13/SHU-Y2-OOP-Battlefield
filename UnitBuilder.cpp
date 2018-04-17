#include "UnitBuilder.h"

UnitBuilder::UnitBuilder(const Position &p, const int c, int h, int cost)
	: Structure(p, c, h, cost), size({ 2, 2 }) {}


UnitBuilder::~UnitBuilder() {}

const int & UnitBuilder::GetColour() const
{
	return IUnit::GetColour();
}

const int & UnitBuilder::GetHealth() const
{
	return IUnit::GetHealth();
}