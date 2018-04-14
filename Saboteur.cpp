#include "Saboteur.h"
#include "Structure.h"

Saboteur::Saboteur(const wchar_t *f, const Position &p, const int c)
	: Attacker(p, c, 100, 5, 2, 2), filename(f) {}

Saboteur::~Saboteur() {}

const int Saboteur::GetMaxHealth() const { return maxhealth; }
const std::string Saboteur::GetName() const { return name; }
const std::string Saboteur::GetOption() const { return option; }
const Size & Saboteur::GetSize() const { return size; }
const wchar_t * Saboteur::GetFilename() const { return filename; }
const int & Saboteur::GetColour() const { return colour; }
void Saboteur::RestoreMovements() { moves = 2; }

void Saboteur::Attack(IUnit * enemy)
{
	if (enemy == dynamic_cast<Structure*>(enemy))
	{
		enemy->UpdateHealth(-(strength * 20));
	}
	else
		enemy->UpdateHealth(-strength);
}