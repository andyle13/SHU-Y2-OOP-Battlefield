#pragma once
#include "Defence.h"
#include "Attacker.h"

class DefenceTurret : public virtual Defence, public virtual Attacker
{
public:
	DefenceTurret(const wchar_t *f, const Position &p, const int & c);
	~DefenceTurret();

	void Promote();

	void Attack(IUnit* p);
	const int GetMaxHealth() const;
	const std::string GetName() const;
	const std::string GetOption() const;
	void RestoreActions();
	const Size & GetSize() const;
	const wchar_t * GetFilename() const;
	const int & GetColour() const;

	const int & GetRange() const;
	const int & GetStrength() const;

private:
	bool hasAttacked;
	const wchar_t * filename;
	int maxhealth = 200;
	const std::string name = "Defence Turret";
	const std::string option = "Attack: Let enemies approach to this unit at least six spaces away from it.";
};


inline void DefenceTurret::RestoreActions()
{
	hasAttacked = false;
	moves = 0;
}