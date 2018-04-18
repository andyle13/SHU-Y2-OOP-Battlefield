#include "Healer.h"

Healer::Healer(const Position &p, const int c, int m) 
	: Infantry(p, c, 60, m, 150) {}

Healer::~Healer() {}

bool Healer::CanHeal(const IUnit* unit)
{
	if ((GetPosition().x == unit->GetPosition().x) && (GetPosition().y == unit->GetPosition().y))
		return true;

	return false;
}

void Healer::Heal(IUnit* unit)
{
	if (unit != NULL)
		unit->SetHealth(unit->GetMaxHealth());
}
