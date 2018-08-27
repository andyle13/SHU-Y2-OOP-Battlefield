#pragma once
#include "IUnit.h"
class Infantry : public virtual IUnit
{
public:
	Infantry(const Position &p, const Size & s, const int & c, int h, int m, const int & cos);
	~Infantry();

	const std::string GetOption() const;
	int GetMoves();

	void SetPosition(Position p);
	const Position & GetSavedPosition();
	void DepleteMoves(int m);
	void CheckUnitOnStructure(const IUnit* unit);

	void Move();

protected:
	Position oldPosition;
	Size size;
	int moves;
	bool isOnStructure, isMoving;
	const std::string option = "1) Move";
};

inline void Infantry::CheckUnitOnStructure(const IUnit* unit)
{
	for (int i = 0; i < unit->GetSize().width; i++)
		for (int j = 0; j < unit->GetSize().height; j++)
			if (this != unit && (GetPosition().x == unit->GetPosition().x + i) && (GetPosition().y == unit->GetPosition().y + j))
				isOnStructure = true;
}

inline void Infantry::DepleteMoves(int m) {
	moves -= m;
}
