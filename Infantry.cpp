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
	{
		return true;
	}
	return false;
}




bool Infantry::CanMove(IUnit * unit) {
	if (colour != unit->GetColour()) {
		/*
		const float tx = GetPosition().x;
		const float ty = GetPosition().y;
		const float cx = unit->GetPosition().x;
		const float cy = unit->GetPosition().y;

		if (ty == cy)
		{
			if (tx < cx)
			{
				for (int i(cx); i > tx; i--)
				{
					if ()
					{
						return false;
					}
				}
			}
			else
			{
				for (int i(cx); i < tx; i++)
				{
					if ()
					{
						return false;
					}
				}
			}
		}
		else if (tx == cx)
		{
			if (ty < cy)
			{
				for (int i(cy); i > ty; i--)
				{
					if ()
					{
						return false;
					}
				}
			}
			else
			{
				for (int i(cy); i < ty; i++)
				{
					if ()
					{
						return false;
					}
				}
			}
		}

		
		const float tx = GetPosition().x + (size.width / 2.0f);
		const float ty = position.y + (size.height / 2.0f);
		const float tolerance = pow((range + size.width), 2);

		const float cx = unit->GetPosition().x + (unit->GetSize().width / 2.0f);
		const float cy = unit->GetPosition().y + (unit->GetSize().height / 2.0f);
		const float dx = tx - cx;
		const float dy = ty - cy;
		const float distsqr = pow(dx, 2) + pow(dy, 2);
		if (distsqr < tolerance)
			return true;*/
	} // measures the distances between the structure and opponent units
	return true;
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
