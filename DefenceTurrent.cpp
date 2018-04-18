#include "DefenceTurrent.h"

DefenceTurrent::DefenceTurrent(const wchar_t *f, const Position &p, const int c)
	: Defence(p, c, 200, 150), /*Attacker(p, c, 200, 25, 0, 6, 150),*/ filename(f) {}

DefenceTurrent::~DefenceTurrent() {}

void DefenceTurrent::Attack(IUnit * enemy)
{
	//enemy->DecreaseHealth(strength);
}

const wchar_t * DefenceTurrent::GetFilename() const { return filename; }
const int DefenceTurrent::GetMaxHealth() const { return maxhealth; }
const std::string DefenceTurrent::GetName() const { return name; }
const std::string DefenceTurrent::GetOption() const { return option; }
void DefenceTurrent::RestoreActions() { /*hasAttacked = false;*/ }
const Size & DefenceTurrent::GetSize() const { return { 1,1 }; }
const int & DefenceTurrent::GetColour() const { return 0; }
const int DefenceTurrent::GetStrength() const { return 0; /*strength;*/ }