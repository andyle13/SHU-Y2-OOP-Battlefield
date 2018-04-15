#include "Infantry.h"

Infantry::Infantry(const Position &p, const int c, int h, int m)
	: IUnit(p, c, h), moves(m), size({ 1,1 }) {}

Infantry::~Infantry() {}

/*bool Infantry::IsValidMove(Position p) {
	const float ty = position.y + (size.height / 2.0f);
	const float tx = position.x + (size.width / 2.0f);
	const float tolerance = (moves + size.width) * (moves + size.width);

	const float cx = p.x + (1.0f / 2.0f);
	const float cy = p.y + (1.0f / 2.0f);
	const float dx = tx - cx;
	const float dy = ty - cy;
	const float distsqr = (dx*dx) + (dy*dy);
	if (distsqr < tolerance) // don't bother to sqrt distsqr, just sqr both sides of the equation for speed
		return true;

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
}*/

int Infantry::GetMoves() 
{
	return moves;
}