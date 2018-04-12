#include "Medic.h"

Medic::Medic(const wchar_t *f, const Position &p, const int c)
	: Healer(p, c, 60, 1), filename(f) {}

Medic::~Medic() {}

const Size & Medic::GetSize() const { return size; }
const wchar_t * Medic::GetFilename() const { return filename; }
const int & Medic::GetColour() const { return colour; }
void Medic::RestoreMovements() { moves = 1; }