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

	void RestoreMovements();
	void Attack(IUnit * enemy);

private:
	const wchar_t* filename;
	int strength, range;
	const int maxhealth = 150;
	const std::string name = "Soldier";
	const std::string option = "Move soldier or right-click to deselect";
};
