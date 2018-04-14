#include "UnitBuilder.h"

UnitBuilder::UnitBuilder(const Position &p, const int c, int h)
	: Structure(p, c, h), size({ 2, 2 }) {}


UnitBuilder::~UnitBuilder() {}

const int & UnitBuilder::GetColour() const
{
	return IUnit::GetColour();
}

const int & UnitBuilder::GetHealth() const
{
	return IUnit::GetHealth();
}