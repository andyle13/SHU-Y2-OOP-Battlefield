#include "Infantry.h"

Infantry::Infantry(const Position &p, const int c, int h, int m, int cos)
	: IUnit(p, c, h, cos), moves(m), size({ 1,1 }) {}

Infantry::~Infantry() {}

const std::string Infantry::GetOption() const{
	return (option + " (Moves available: " + std::to_string(moves) + ")\n");
}

bool Infantry::UnitOnStructure(const IUnit* unit)
{
	if ((GetPosition().x == unit->GetPosition().x) && (GetPosition().y == unit->GetPosition().y))
		return true;

	return false;
}

Position Infantry::GetOldPosition()
{
	return oldPosition;
}
int Infantry::GetMoves() 
{
	return moves;
}

void Infantry::SetPosition2(Position p)
{
	position = p;
}

void Infantry::SetOldPosition(Position p) {
	// creates a memento of previous position;
	oldPosition = p;
}

void Infantry::SetPosition(Position p) {
	// creates a memento of previous position;
	oldPosition = position;
	position = p;
}

void Infantry::DepleteMoves(int m) {
	moves -= m;
}
