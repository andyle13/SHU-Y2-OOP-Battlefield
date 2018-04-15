#pragma once
#include "IUnit.h"
class Infantry : public IUnit
{
public:
	Infantry(const Position &p, const int c, int h, int m);
	~Infantry();

	virtual void RestoreMovements() = 0;
	const std::string GetOption() const;
	int GetMoves();
	void GetLegalMoves(Position p);
	void DepleteMoves(int m);

protected:
	Size size;
	int moves;
	const std::string option = "1) Move";
};

