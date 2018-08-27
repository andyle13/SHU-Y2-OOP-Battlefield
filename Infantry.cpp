#include "Infantry.h"

Infantry::Infantry(const Position &p, const Size & s, const int & c, int h, int m, const int & cos)
	: IUnit(p, { 1,1 }, c, h, cos), moves(m), size({ 1,1 }), isOnStructure(false), isMoving(false) {}

Infantry::~Infantry() {}

const std::string Infantry::GetOption() const {
	return (option + " (Moves available: " + std::to_string(moves) + ")\n");
}

void Infantry::Move() { isMoving = true; }

int Infantry::GetMoves() { return moves; }

void Infantry::SetPosition(Position p) {
	if (isMoving) {
		oldPosition = position;
		isMoving = false;
	} // creates a memento of previous position;
	position = p;
}

const Position & Infantry::GetSavedPosition() { return oldPosition; }