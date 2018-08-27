#pragma once
#include "IUnit.h"
class Structure : public virtual IUnit
{
public:
	Structure(const Position & p, const Size & s, const int & c, int h, const int & cost);
	~Structure();

};

