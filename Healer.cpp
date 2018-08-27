#include "Healer.h"

Healer::Healer(const Position &p, const int & c, int m) 
	: Infantry(p, { 1,1 }, c, 60, m, 150) {}

Healer::~Healer() {}

void Healer::Heal(IUnit* unit)
{
	if (unit != NULL)
		unit->SetHealth(unit->GetMaxHealth());
}
