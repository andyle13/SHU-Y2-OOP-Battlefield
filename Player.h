#pragma once
#include <string>
#include <list>
#include "IUnit.h"
class Player
{
public:
	Player(std::string p, const int c);
	~Player();

	//std::list<IUnit*> GetPlayerUnits();
	//void AddUnit(IUnit * u);
	const int GetColour();

private:
	//std::list<IUnit*> units;
	std::string playerName;
	int balance;
	const int colour;
};

