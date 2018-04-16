#include "Healer.h"

Healer::Healer(const Position &p, const int c, int h, int m) 
	: Infantry(p, c, h, m, 150) {}

Healer::~Healer() {}


void Healer::Heal(IUnit* unit)
{
	unit->SetHealth(unit->GetMaxHealth());
}
