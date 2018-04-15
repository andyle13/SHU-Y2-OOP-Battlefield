#include "DefenceTurrent.h"



DefenceTurrent::DefenceTurrent(const Position &p, const int c) : Defence(p, c, 150)
{
}


DefenceTurrent::~DefenceTurrent()
{
}

void DefenceTurrent::Attack(IUnit* u)
{
	u->SetHealth(-25);
}
/*
const bool DefenceTurrent::CanAttack(IUnit* u) const
{

	if ((position.x > u->GetPosition().x) && (position.y > u->GetPosition().y))
	{
		if ((((position.x - u->GetPosition().x) >= 1) && ((position.x - u->GetPosition().x) <= 6)) && (((position.y - u->GetPosition().y) >= 1) && ((position.y - u->GetPosition().y) <= 6)))
			return true;
	}
	else if ((position.x < u->GetPosition().x) && (position.y > u->GetPosition().y))
	{
		if ((((u->GetPosition().x - position.x) >= 1) && ((u->GetPosition().x - position.x) <= 6)) && (((position.y - u->GetPosition().y) >= 1) && ((position.y - u->GetPosition().y) <= 6)))
			return true;
	}
	else if ((position.x > u->GetPosition().x) && (position.y < u->GetPosition().y))
	{
		if ((((position.x - u->GetPosition().x) >= 1) && ((position.x - u->GetPosition().x) <= 6)) && (((u->GetPosition().y - position.y) >= 1) && ((u->GetPosition().y - position.y) <= 6)))
			return true;
	}
	else if ((position.x < u->GetPosition().x) && (position.y < u->GetPosition().y))
	{
		if ((((u->GetPosition().x - position.x) >= 1) && ((u->GetPosition().x - position.x) <= 6)) && (((u->GetPosition().y - position.y) >= 1) && ((u->GetPosition().y - position.y) <= 6)))
			return true;
	}
	else
	{
		return false;
	}

	/*
	if((position.x > u->GetPosition().x) && (position.y > u->GetPosition().y))

		if ((position.x < u->GetPosition().x) && (position.y > u->GetPosition().y))

			if ((position.x > u->GetPosition().x) && (position.y < u->GetPosition().y))

				if ((position.x < u->GetPosition().x) && (position.y < u->GetPosition().y))

}*/