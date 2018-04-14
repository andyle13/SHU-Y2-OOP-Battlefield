#pragma once
#include "IUnit.h"
class Infantry : public IUnit
{
public:
	Infantry(const Position &p, const int c, int h, int m);
	~Infantry();

	virtual void RestoreMovements() = 0;

protected:
	int moves;
	Size size;
};

