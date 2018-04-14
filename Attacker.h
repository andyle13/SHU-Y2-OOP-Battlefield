#pragma once
#include "Infantry.h"
class Attacker : public Infantry
{
public:
	Attacker(const Position &p, const int c, int h, int s, int m, int r);
	~Attacker();

	virtual void Attack(IUnit * enemy) = 0;

protected:
	int strength, range;
};

