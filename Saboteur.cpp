#include "Saboteur.h"
#include "Structure.h"

Saboteur::Saboteur(const wchar_t *f, const Position &p, const int c)
	: Attacker(p, c, 100, 5, 2, 2, 200, "Amateur"), filename(f) {}

Saboteur::~Saboteur() {}

const int Saboteur::GetMaxHealth() const { return maxhealth; }
const std::string Saboteur::GetName() const { return name; }
const std::string Saboteur::GetOption() const { return option; }
const Size & Saboteur::GetSize() const { return size; }
const wchar_t * Saboteur::GetFilename() const { return filename; }
const int & Saboteur::GetColour() const { return colour; }

void Saboteur::RestoreActions() { 
	hasAttacked = false;
	moves = 2;
}

const int Saboteur::GetStrength() const {
	return strength;
}

bool Saboteur::CanAttackStruc(const IUnit* unit)
{
	if ((GetPosition().x == unit->GetPosition().x) && (GetPosition().y == unit->GetPosition().y))
	{
		return true;
	}
	return false;
}

void Saboteur::Attack(IUnit * enemy)
{
	if (enemy == dynamic_cast<Structure*>(enemy))
		enemy->DecreaseHealth(strength * 20);
	else
		enemy->DecreaseHealth(strength);
	
	hasAttacked = true;

	if (enemy->GetHealth() <= 0) {
		killstreak++;
		Promote();
	}
}

void Saboteur::Promote() {
	switch (killstreak) {
	case 3:
		rank = "Silent Killer";
		strength = 15;
		moves++;
		break;
	case 7:
		rank = "Master Assassin";
		strength = 25;
		moves++;
		break;
	case 13:
		rank = "Legend";
		strength = 40;
		moves++;
		break;
	}
}