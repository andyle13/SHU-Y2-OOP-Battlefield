#include "Infantry.h"

Infantry::Infantry(const Position &p, const int c, int h, int m, int cos)
	: IUnit(p, c, h, cos), moves(m), size({ 1,1 }), isOnStructure(false), isMoving(false) {}

Infantry::~Infantry() {}

const std::string Infantry::GetOption() const {
	return (option + " (Moves available: " + std::to_string(moves) + ")\n");
}

void Infantry::CheckUnitOnStructure(const IUnit* unit)
{
	for (int i = 0; i < unit->GetSize().width; i++)
		for (int j = 0; j < unit->GetSize().height; j++)
			if (this != unit && (GetPosition().x == unit->GetPosition().x + i) && (GetPosition().y == unit->GetPosition().y + j))
				isOnStructure = true;
}

void Infantry::Move() {
	isMoving = true;
}

int Infantry::GetMoves() { return moves; }

void Infantry::SetPosition(Position p) {
	if (isMoving) {
		oldPosition = position;
		isMoving = false;
	} // creates a memento of previous position;
	position = p;
}

void Infantry::DepleteMoves(int m) {
	moves -= m;
}
