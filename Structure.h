#pragma once
#include "IUnit.h"
class Structure : public IUnit
{
public:
	Structure(const Position & p, const int c, int h);
	~Structure();

};

