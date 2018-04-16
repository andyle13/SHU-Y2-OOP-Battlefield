#include "IUnit.h"

IUnit::IUnit(const Position & p, const int c, int h, int cos)
	: position(p), colour(c), health(h), cost(cos) {}

IUnit::~IUnit() {}

const Position & IUnit::GetPosition() const { return position; }
const int & IUnit::GetHealth() const { return health; }
const int & IUnit::GetColour() const { return colour; }

void IUnit::SetPosition(int setX, int setY) {
	position = { setX, setY };
}

void IUnit::SetHealth(int changeHealth) {
	health = changeHealth;
}

void IUnit::UpdateHealth(int changeHealth) {
	health += changeHealth;
}

const int IUnit::GetCost() const
{
	return cost;
}
