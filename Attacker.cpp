#include "Attacker.h"

Attacker::Attacker(const Position &p, const int c, int h, int s, int m, int r, int cost)
	: Infantry(p, c, h, m, cost), strength(s), range(r) {}

Attacker::~Attacker() {}
