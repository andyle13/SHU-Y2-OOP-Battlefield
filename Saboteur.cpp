#include "Saboteur.h"

Saboteur::Saboteur(const wchar_t *f, const Position &p, const int c)
	: Attacker(p, c, 100, 5, 2, 2), filename(f) {}

Saboteur::~Saboteur() {}

const Size & Saboteur::GetSize() const { return size; }
const wchar_t * Saboteur::GetFilename() const { return filename; }
const int & Saboteur::GetColour() const { return colour; }
void Saboteur::RestoreMovements() { moves = 2; }