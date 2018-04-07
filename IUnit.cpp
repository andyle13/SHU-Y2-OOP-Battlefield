#include "IUnit.h"

IUnit::IUnit(const Position & p, int h)
	: position(p), health(h) {}

IUnit::~IUnit() {}

const Position & IUnit::GetPosition() const { return position; }
const int & IUnit::GetHealth() const { return health; }

void IUnit::SetPosition(int setX, int setY) {
	position = { setX, setY };
}

void IUnit::SetHealth(int changeHealth) {
	health = changeHealth;
}