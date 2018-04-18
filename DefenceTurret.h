#pragma once
#include "Defence.h"
#include "Attacker.h"

class DefenceTurret : public Defence
{
public:
	DefenceTurret(const wchar_t *f, const Position &p, const int c);
	~DefenceTurret();
	void Attack(IUnit* p);
	const int GetMaxHealth() const;
	const std::string GetName() const;
	const std::string GetOption() const;
	void RestoreActions();
	const Size & GetSize() const;
	const wchar_t * GetFilename() const;
	const int & GetColour() const;
	const int GetStrength() const;

private:
	const wchar_t * filename;
	const int maxhealth = 200;
	const std::string name = "Defence Turret";
	const std::string option = "Stationary defence turret who attacks enemy units once in range.";
};

