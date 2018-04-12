#include "Soldier.h"

Soldier::Soldier(const wchar_t *f, const Position &p, const int c)
	: Attacker(p, c, 150, 10, 2, 2), filename(f) {}

Soldier::~Soldier() {}

const Size & Soldier::GetSize() const { return size; }
const wchar_t * Soldier::GetFilename() const { return filename; }
const int & Soldier::GetColour() const { return colour; }
void Soldier::RestoreMovements() { moves = 2; }