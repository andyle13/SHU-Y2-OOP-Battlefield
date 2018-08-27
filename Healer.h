#pragma once
#include "Infantry.h"
class Healer : public Infantry
{
public:
	Healer(const Position &p, const int & c, int m);
	~Healer();
	void Heal(IUnit* unit);
	bool Healer::CanHeal(const IUnit* unit);
};

inline bool Healer::CanHeal(const IUnit* unit)
{
	if ((GetPosition().x == unit->GetPosition().x) && (GetPosition().y == unit->GetPosition().y))
		return true;

	return false;
}