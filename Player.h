#pragma once
#include <string>
#include <list>
#include "IUnit.h"

class Player
{
public:
	Player(const wchar_t p, const int c);
	~Player();

	//std::list<IUnit*> GetPlayerUnits();
	//void AddUnit(IUnit * u);
	const int GetColour();
	const wchar_t GetName();
	const int GetBalance();
	void Buy(const int & price);

	void AddWarTrophy(const int & prize);


private:
	//std::list<IUnit*> units;
	const wchar_t playerName;
	int balance;
	const int colour;
	
};