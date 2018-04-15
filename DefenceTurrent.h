#pragma once
#include "Defence.h"
class DefenceTurrent :
	public Defence
{
public:
	DefenceTurrent(const Position &p, const int c);
	~DefenceTurrent();
	void Attack(IUnit* p);

	//const bool CanAttack(IUnit* p) const;
};

