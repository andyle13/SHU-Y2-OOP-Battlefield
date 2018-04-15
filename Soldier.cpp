#include "Soldier.h"

Soldier::Soldier(const wchar_t *f, const Position &p, const int c)
	: Attacker(p, c, 150, 10, 2, 2), filename(f) {}

Soldier::~Soldier() {}

const int Soldier::GetMaxHealth() const { return maxhealth; }
const std::string Soldier::GetName() const { return name; }
const std::string Soldier::GetOption() const {
	return Infantry::GetOption() + option;
}
const Size & Soldier::GetSize() const { return size; }
const wchar_t * Soldier::GetFilename() const { return filename; }
const int & Soldier::GetColour() const { return colour; }
void Soldier::RestoreMovements() { moves = 2; }

const int Soldier::GetStrength() const {
	return strength;
}

void Soldier::Attack(IUnit * enemy) {
	enemy->DecreaseHealth(strength);
}