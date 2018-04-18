#pragma once
#include "IUnit.h"
class Infantry : public IUnit
{
public:
	Infantry(const Position &p, const int c, int h, int m, int cos);
	~Infantry();

<<<<<<< HEAD
	const std::string GetOption() const;
	int GetMoves();
=======
	virtual void RestoreMovements() = 0;
	Position GetOldPosition();
	const std::string GetOption() const;
	int GetMoves();
	void SetPosition(Position p);
	void SetOldPosition(Position p);
>>>>>>> daniel
	void DepleteMoves(int m);
	bool UnitOnStructure(const IUnit* unit);
	bool CanMove(IUnit * unit);
	void SetPosition2(Position p);

protected:
	Position oldPosition;
	Size size;
	int moves;
	const std::string option = "1) Move";
};
/*
inline Position Infantry::restoreFromMemento(Position memento)
{
	IUnit::SetPosition(memento.x,memento.y);
	position = memento;
	return position;
}*/

