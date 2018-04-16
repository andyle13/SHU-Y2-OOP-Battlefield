#pragma once
#include "IUnit.h"
class Infantry : public IUnit
{
public:
	Infantry(const Position &p, const int c, int h, int m, int cos);
	~Infantry();

	virtual void RestoreMovements() = 0;
	//bool IsValidMove(Position p);
	int GetMoves();

protected:
	int moves;
	Size size;
};

