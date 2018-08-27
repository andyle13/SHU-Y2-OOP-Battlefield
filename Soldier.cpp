#include "Soldier.h"

Soldier::Soldier(const wchar_t *f, const Position &p, const int & c)
	: Attacker(p, c, 150, 10, 2, 2, 100, "Novice"), IUnit(p, { 1, 1 }, c, 150, 100), Infantry(p, { 1, 1 }, c, 150, 2, 100), filename(f) {}

Soldier::~Soldier() {}

const int Soldier::GetMaxHealth() const { return maxhealth; }
const std::string Soldier::GetName() const { return name; }
const std::string Soldier::GetOption() const { return Infantry::GetOption() + option; }
const Size & Soldier::GetSize() const { return size; }
const wchar_t * Soldier::GetFilename() const { return filename; }
const int & Soldier::GetColour() const { return colour; }
const int & Soldier::GetRange() const { return range; }
const int & Soldier::GetStrength() const { return strength; }


void Soldier::Attack(IUnit * enemy) {
	if (enemy->GetColour() != colour) {
		enemy->DecreaseHealth(strength);
		hasAttacked = true;
		if (enemy->GetHealth() <= 0) {
			killstreak++;
			Promote();
		}
	}
}

void Soldier::Promote() {
	switch (killstreak) {
	case 3:
		rank = "Experienced Warrior";
		maxhealth = 190;
		strength = 20;
		moves = moves++;
		break;
	case 7:
		rank = "Elite Soldier";
		maxhealth = 250;
		strength = 35;
		moves = moves++;
		break;
	case 13:
		rank = "Legend";
		maxhealth = 300;
		strength = 50;
		moves = moves++;
		break;
	}
}