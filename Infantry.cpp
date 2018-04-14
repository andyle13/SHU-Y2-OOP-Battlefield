#include "Infantry.h"

Infantry::Infantry(const Position &p, const int c, int h, int m)
	: IUnit(p, c, h), moves(m), size({ 1,1 }) {}

Infantry::~Infantry() {}

bool Infantry::IsValidMove(Position p) {
	if (p.x <= (position.x + moves) && p.y <= (position.y + moves))
		return true;
	else if (p.x <= (position.x + moves) && p.y >= (position.y - moves))
		return true;
	else if (p.x >= (position.x - moves) && p.y >= (position.y - moves))
		return true;
	else if (p.x >= (position.x - moves) && p.y <= (position.y + moves))
		return true;
	else
		return false;
}

int Infantry::GetMoves() 
{
	return moves;
}