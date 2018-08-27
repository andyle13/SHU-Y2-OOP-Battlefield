#include "Tank.h"
#include "Vehicle.h"

Tank::Tank(const wchar_t *f, const Position &p, const int & c)
	: IUnit(p, { 1,1 }, c, 350, 250), Attacker(p, c, 350, 250, 2, 6, 150, "The Dominator"), Vehicle(p, c, 350, 250), Infantry(p, { 1,1 }, c, 350, 2, 150), filename(f) {}

Tank::~Tank() {}

const int & Tank::GetRange() const { return range; }
const int & Tank::GetStrength() const { return strength; }
const int Tank::GetMaxHealth() const { return maxhealth; }
const std::string Tank::GetName() const { return name; }
const std::string Tank::GetOption() const { return option; }
const Size & Tank::GetSize() const { return size; }
const wchar_t * Tank::GetFilename() const { return filename; }
const int & Tank::GetColour() const { return colour; }
void Tank::Attack(IUnit * enemy) {
	enemy->DecreaseHealth(strength);
	hasAttacked = true;
}

void Tank::Promote() {
	switch (killstreak) {
	case 3:
		rank = "Man of War";
		maxhealth = 450;
		break;
	case 7:
		rank = "War Lord";
		maxhealth = 700;
		break;
	case 13:
		rank = "God of War";
		maxhealth = 1000;
		strength = 400;
		break;
	}
}