#pragma once
#include "UnitBuilder.h"

class Armoury :	public UnitBuilder
{
public:
	Armoury(const wchar_t *f, const Position &p, const int & c);
	~Armoury();

	const int GetMaxHealth() const;
	const std::string GetName() const;
	const std::string GetOption() const;
	const Size & GetSize() const;
	const wchar_t * GetFilename() const;
	const int & GetColour() const;

	void RestoreActions();

	IUnit * GetUnit(const wchar_t * f, const Position & p, const int & c, const char & id);

private:
	const wchar_t* filename;
	const int maxhealth = 200;
	const std::string name = "Armoury";
	const std::string option = "1) Create Soldier\n2) Create Medic\n3) Create Mechanic\n4) Create Saboteur";
};

inline void Armoury::RestoreActions() {
	hasPlaced = false;
}