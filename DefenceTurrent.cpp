#include "DefenceTurret.h"


DefenceTurret::DefenceTurret(const wchar_t *f, const Position &p, const int c) : Defence(p, c, 200, 150), filename(f)
{
}


DefenceTurret::~DefenceTurret()
{
}

void DefenceTurret::Attack(IUnit* u)
{
	u->SetHealth(-25);
}

const wchar_t * DefenceTurret::GetFilename() const { return filename; }

const int DefenceTurret::GetMaxHealth() const { return maxhealth; }
const std::string DefenceTurret::GetName() const { return name; }
const std::string DefenceTurret::GetOption() const { return option; }
const Size & DefenceTurret::GetSize() const { return Defence::size; }
const int & DefenceTurret::GetColour() const { return Defence::colour; }

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