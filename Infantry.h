#pragma once
#include "IUnit.h"
class Infantry : public IUnit
{
public:
	Infantry(const Position &p, const int c, int h, int m, int cos);
	~Infantry();

	const std::string GetOption() const;
	int GetMoves();
	void DepleteMoves(int m);

protected:
	Size size;
	int moves;
	const std::string option = "1) Move";
};

