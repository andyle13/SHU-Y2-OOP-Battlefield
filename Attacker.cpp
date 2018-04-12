#include "Attacker.h"

Attacker::Attacker(const Position &p, const int c, int h, int s, int m, int r)
	: Infantry(p, c, h, m), strength(s), range(r) {}

Attacker::~Attacker() {}
