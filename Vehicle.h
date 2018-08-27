#pragma once
#include "IUnit.h"
#include "Attacker.h"

class Vehicle :	virtual public IUnit
{
public:
	Vehicle(const Position &p, const int & c, int h, const int & cos);
	~Vehicle();

protected:
	const std::string option = "1) Move";
};

