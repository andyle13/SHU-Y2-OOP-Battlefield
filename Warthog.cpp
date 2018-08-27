#include "Warthog.h"
#include "Vehicle.h"

Warthog::Warthog(const wchar_t *f, const Position &p, const int c)
	: IUnit(p, { 1,1 }, c, 250, 150), Attacker(p, c, 250, 150, 4, 4, 150, "Chaos"), Vehicle(p, c, 250, 150), Infantry(p, { 1,1 }, c, 250, 4, 150), filename(f) {}

Warthog::~Warthog() {}

const int Warthog::GetMaxHealth() const { return maxhealth; }
const std::string Warthog::GetName() const { return name; }
const std::string Warthog::GetOption() const { return option; }
const Size & Warthog::GetSize() const { return size; }
const wchar_t * Warthog::GetFilename() const { return filename; }
const int & Warthog::GetColour() const { return colour; }
void Warthog::Attack(IUnit * enemy) {
	enemy->DecreaseHealth(strength);
	hasAttacked = true;
}
void Warthog::Promote() {
	switch (killstreak) {
	case 3:
		rank = "Doombringer";
		maxhealth = 300;
		strength = 300;
		break;
	case 7:
		rank = "Armageddon";
		maxhealth = 450;
		strength = 350;
		break;
	case 13:
		rank = "Lucifer";
		maxhealth = 666;
		strength = 400;
		break;
	}
}

const int & Warthog::GetRange() const {
	return range;
}
const int & Warthog::GetStrength() const {
	return strength;
}