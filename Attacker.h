#pragma once
#include "Infantry.h"
class Attacker : public Infantry
{
public:
	Attacker(const Position &p, const int c, int h, int s, int m, int r, int cost, std::string rk);
	~Attacker();

	virtual void Promote() = 0;
	virtual void Attack(IUnit * enemy) = 0;
	virtual const int GetStrength() const = 0;
<<<<<<< HEAD
	bool DetermineWeakestEnemy(IUnit* enemy);

	const bool CanAttack() const;
=======
	virtual bool CanAttack(IUnit* enemy);
>>>>>>> daniel

protected:
	int strength, range, killstreak;
	std::string rank;
	bool hasAttacked;
};

