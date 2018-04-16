#pragma once
#include "Infantry.h"
class Healer : public Infantry
{
public:
	Healer(const Position &p, const int c, int m);
	~Healer();
	void Heal(IUnit* unit);

protected:

};

