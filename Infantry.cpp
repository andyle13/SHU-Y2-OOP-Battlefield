#include "Infantry.h"

Infantry::Infantry(const Position &p, const int c, int h, int m)
	: IUnit(p, c, h), moves(m), size({ 1,1 }) {}

Infantry::~Infantry() {}

const std::string Infantry::GetOption() const{
	return (option + " (Moves available: " + std::to_string(moves) + ")\n");
}

int Infantry::GetMoves() 
{
	return moves;
}

void Infantry::DepleteMoves(int m) {
	moves -= m;
}
