#include "IUnit.h"

IUnit::IUnit(const Position & p, const Size & s, const int & c, int h, const int & cos)
	: position(p), size(s), colour(c), health(h), cost(cos) {}

IUnit::~IUnit() {}

//const Size & IUnit::GetSize() const { return size; }
const Position & IUnit::GetPosition() const { return position; }
const int & IUnit::GetHealth() const { return health; }
const int & IUnit::GetColour() const { return colour; }

void IUnit::SetPosition(Position p) {
	position = p;
}

void IUnit::SetHealth(int changeHealth) {
	health = changeHealth;
}

void IUnit::DecreaseHealth(int damage) {
	health -= damage;
}

const int IUnit::GetCost() const
{
	return cost;
}