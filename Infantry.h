#pragma once
#include "IUnit.h"
class Infantry : public IUnit
{
public:
	Infantry(const Position &p, const int c, int h, int m, int cos);
	~Infantry();

	const std::string GetOption() const;
	int GetMoves();
	Position GetOldPosition();

	void SetPosition(Position p);
	void SetOldPosition(Position p);
	void DepleteMoves(int m);
	bool UnitOnStructure(const IUnit* unit);
	void SetPosition2(Position p);

protected:
	Position oldPosition;
	Size size;
	int moves;
	const std::string option = "1) Move";
};

