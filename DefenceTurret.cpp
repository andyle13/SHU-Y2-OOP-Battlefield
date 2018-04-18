#include "DefenceTurret.h"

//Attacker(const Position &p, const int c, int h, int s, int m, int r, int cost);
DefenceTurret::DefenceTurret(const wchar_t *f, const Position &p, const int c)
	: Defence(p, c, 200, 150), filename(f) /*, Attacker(p, c, 200, 25, 0, 6, 150)*/ {}

DefenceTurret::~DefenceTurret() {}

const int DefenceTurret::GetStrength() const { return 0 /* strength*/; }

void DefenceTurret::RestoreActions()
{
	/*hasAttacked = false;
	moves = 0;	// NEED TO CHANGE THIS IF WE DECIDE TO PROMOTE TURRET
	*/
}

void DefenceTurret::Attack(IUnit* enemy)
{
	//enemy->DecreaseHealth(strength);
}

const wchar_t * DefenceTurret::GetFilename() const { return filename; }

const int DefenceTurret::GetMaxHealth() const { return DefenceTurret::maxhealth; }
const std::string DefenceTurret::GetName() const { return name; }
const std::string DefenceTurret::GetOption() const { return option; }
const Size & DefenceTurret::GetSize() const { return Defence::size; }
const int & DefenceTurret::GetColour() const { return Defence::colour; }