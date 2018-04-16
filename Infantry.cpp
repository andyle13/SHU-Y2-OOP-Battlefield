#include "Infantry.h"

Infantry::Infantry(const Position &p, const int c, int h, int m, int cos)
	: IUnit(p, c, h, cos), moves(m), size({ 1,1 }) {}

Infantry::~Infantry() {}

int Infantry::GetMoves() 
{
	return moves;
}