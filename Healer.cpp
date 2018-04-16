#include "Healer.h"

Healer::Healer(const Position &p, const int c, int m) 
	: Infantry(p, c, 60, m, 150) {}

Healer::~Healer() {}


void Healer::Heal(IUnit* unit)
{
	unit->SetHealth(unit->GetMaxHealth());
}
