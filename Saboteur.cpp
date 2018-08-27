#include "Saboteur.h"
#include "Structure.h"

Saboteur::Saboteur(const wchar_t *f, const Position &p, const int & c)
	: Attacker(p, c, 100, 5, 2, 2, 200, "Amateur"), IUnit(p, { 1, 1 }, c, 100, 150), Infantry(p, { 1,1 }, c, 100, 2, 200), filename(f) {}

Saboteur::~Saboteur() {}

const int Saboteur::GetMaxHealth() const { return maxhealth; }
const std::string Saboteur::GetName() const { return name; }
const std::string Saboteur::GetOption() const { return Infantry::GetOption() + option; }
const Size & Saboteur::GetSize() const { return size; }
const wchar_t * Saboteur::GetFilename() const { return filename; }
const int & Saboteur::GetColour() const { return colour; }
const int & Saboteur::GetRange() const { return range; }
const int & Saboteur::GetStrength() const { return strength; }


void Saboteur::Attack(IUnit * enemy)
{
	if (enemy->GetColour() != colour) {
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
}

void Saboteur::Promote() {
	switch (killstreak) {
	case 3:
		rank = "Silent Killer";
		maxhealth = 150;
		strength = 15;
		moves = moves++;
		break;
	case 7:
		rank = "Master Assassin";
		maxhealth = 180;
		strength = 25;
		moves = moves++;
		break;
	case 13:
		rank = "Legend";
		maxhealth = 270;
		strength = 40;
		moves = moves++;
		break;
	}
}