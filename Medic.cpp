#include "Medic.h"

Medic::Medic(const wchar_t *f, const Position &p, const int & c)
	: Healer(p, c, 1), IUnit(p, { 1,1 }, c, 60, 150), filename(f) {}

Medic::~Medic() {}

const int Medic::GetMaxHealth() const { return maxhealth; }
const std::string Medic::GetName() const { return name; }
const std::string Medic::GetOption() const { return Infantry::GetOption() + option; }
const Size & Medic::GetSize() const { return size; }
const wchar_t * Medic::GetFilename() const { return filename; }
const int & Medic::GetColour() const { return colour; }
void Medic::RestoreActions() { moves = 1; }