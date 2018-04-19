#pragma once
#include "IUnit.h"
class Infantry : public IUnit
{
public:
	Infantry(const Position &p, const int c, int h, int m, int cos);
	~Infantry();

	const std::string GetOption() const;
	int GetMoves();

	void SetPosition(Position p);
	void DepleteMoves(int m);
	void CheckUnitOnStructure(const IUnit* unit);

	void Move();

protected:
	Position oldPosition;
	Size size;
	int moves;
	bool isOnStructure, isMoving;
	const std::string option = "1) Move";
};

