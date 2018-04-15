#pragma once
#include "Attacker.h"
class Saboteur : public Attacker
{
public:
	Saboteur(const wchar_t *f, const Position &p, const int c);
	~Saboteur();

	const int GetMaxHealth() const;
	const std::string GetName() const;
	const std::string GetOption() const;
	const Size & GetSize() const;
	const wchar_t * GetFilename() const;
	const int & GetColour() const;
	const int GetStrength() const;

	void RestoreMovements();
	void Attack(IUnit * enemy);

private:
	const wchar_t* filename;
	const int maxhealth = 100;
	const std::string name = "Saboteur";
	const std::string option = "1) Move";
};
