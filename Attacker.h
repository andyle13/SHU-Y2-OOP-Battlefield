#pragma once
#include "Infantry.h"
class Attacker : public virtual Infantry
{
public:
	Attacker(const Position &p, const int & c, int h, int s, int m, int r, const int & cost, std::string rk);
	~Attacker();

	virtual void Promote() = 0;
	virtual void Attack(IUnit * enemy) = 0;
	virtual const int & GetRange() const = 0;
	virtual const int & GetStrength() const = 0;
	const int GetKills() const;
	const std::string GetRank() const;
	bool DetermineWeakestEnemy(const IUnit* enemy);

	const bool CanAttack() const;

protected:
	int strength, range, killstreak;
	std::string rank;
	bool hasAttacked;
};