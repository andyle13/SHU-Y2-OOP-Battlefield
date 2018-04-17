#include "Saboteur.h"
#include "Structure.h"

Saboteur::Saboteur(const wchar_t *f, const Position &p, const int c)
	: Attacker(p, c, 100, 5, 2, 2, 200), filename(f) {}

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

void Saboteur::Attack(IUnit * enemy)
{
	if (enemy == dynamic_cast<Structure*>(enemy))
	{
		enemy->DecreaseHealth(strength * 20);
	}
	else
		enemy->DecreaseHealth(strength);
}