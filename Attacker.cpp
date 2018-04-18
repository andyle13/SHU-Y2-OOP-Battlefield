#include "Attacker.h"

Attacker::Attacker(const Position &p, const int c, int h, int s, int m, int r, int cost, std::string rk)
	: Infantry(p, c, h, m, cost), strength(s), range(r), rank(rk), killstreak(0), hasAttacked(false) {}

Attacker::~Attacker() {}

bool Attacker::DetermineWeakestEnemy(IUnit * enemy) {
	if (colour != enemy->GetColour()) {
		const float tx = position.x + (size.width / 2.0f);
		const float ty = position.y + (size.height / 2.0f);
		const float tolerance = pow((range + size.width), 2);

		const float cx = enemy->GetPosition().x + (enemy->GetSize().width / 2.0f);
		const float cy = enemy->GetPosition().y + (enemy->GetSize().height / 2.0f);
		const float dx = tx - cx;
		const float dy = ty - cy;
		const float distsqr = pow(dx, 2) + pow(dy, 2);
		if (distsqr < tolerance)
			return true;
	} // measures the distances between the structure and opponent units
	return false;
}
const bool Attacker::CanAttack() const {
	return hasAttacked;
}
