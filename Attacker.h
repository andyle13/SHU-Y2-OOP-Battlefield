#pragma once
#include "Infantry.h"
class Attacker : public Infantry
{
public:
	Attacker(const Position &p, const int c, int h, int s, int m, int r, int cost);
	~Attacker();

	virtual void Attack(IUnit * enemy) = 0;
	virtual const int GetStrength() const = 0;
	bool CanAttack(IUnit* enemy);

protected:
	int strength, range;
	bool hasAttacked;
};

