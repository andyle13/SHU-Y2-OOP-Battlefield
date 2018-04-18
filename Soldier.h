#pragma once
#include "Attacker.h"
class Soldier :	public Attacker
{
public:
	Soldier(const wchar_t *f, const Position &p, const int c);
	~Soldier();

	const int GetMaxHealth() const;
	const std::string GetName() const;
	const std::string GetOption() const;
	const Size & GetSize() const;
	const wchar_t * GetFilename() const;
	const int & GetColour() const;
	const int GetStrength() const;

	void RestoreActions();
	void Attack(IUnit * enemy);

	void Promote();

private:
	const wchar_t* filename;
	const int maxhealth = 150;
	const std::string name = "Soldier";
	const std::string option = "Attack: Move this unit at least two spaces away from an opponent.";
};
