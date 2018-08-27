#include "DefenceTurret.h"

//Attacker(const Position &p, const int c, int h, int s, int m, int r, int cost);
DefenceTurret::DefenceTurret(const wchar_t *f, const Position &p, const int & c)
	: Defence(p, c, 200, 150), filename(f), Attacker(p, c, 200, 25, 0, 6, 150, "The Menace"), IUnit(p, { 1,1 }, c, 200, 150), Structure(p, { 1,1 }, c, 200, 150), Infantry(p, { 1,1 }, c, 200, 0, 150) {}

DefenceTurret::~DefenceTurret() {}

const wchar_t * DefenceTurret::GetFilename() const { return filename; }
const int DefenceTurret::GetMaxHealth() const { return DefenceTurret::maxhealth; }
const std::string DefenceTurret::GetName() const { return name; }
const std::string DefenceTurret::GetOption() const { return option; }
const Size & DefenceTurret::GetSize() const { return Defence::size; }
const int & DefenceTurret::GetColour() const { return Defence::colour; }
const int & DefenceTurret::GetRange() const { return Attacker::range; }
const int & DefenceTurret::GetStrength() const { return Attacker::strength; }

void DefenceTurret::Attack(IUnit* enemy)
{
	if (enemy->GetColour() != colour) {
		enemy->DecreaseHealth(strength);
		hasAttacked = true;
		if (enemy->GetHealth() <= 0) {
			killstreak++;
			Promote();
		}
	}
}

void DefenceTurret::Promote() {
	switch (killstreak) {
	case 3:
		rank = "The Hunter";
		maxhealth = 220;
		strength = 30;
		moves = moves++;
		break;
	case 7:
		rank = "The Oppressor";
		maxhealth = 300;
		strength = 45;
		break;
	case 13:
		rank = "The Dictator";
		maxhealth = 420;
		strength = 70;
		moves = 3;
		break;
	}
}