#include "Mechanic.h"

Mechanic::Mechanic(const wchar_t *f, const Position &p, const int & c)
	: Healer(p, c, 1), IUnit(p, { 1,1 }, c, 60, 150), filename(f) {}

Mechanic::~Mechanic() {}

const int Mechanic::GetMaxHealth() const { return maxhealth; }
const std::string Mechanic::GetName() const { return name; }
const std::string Mechanic::GetOption() const { return Infantry::GetOption() + option; }
const Size & Mechanic::GetSize() const { return size; }
const wchar_t * Mechanic::GetFilename() const { return filename; }
const int & Mechanic::GetColour() const { return colour; }
void Mechanic::RestoreActions() { moves = 1; }