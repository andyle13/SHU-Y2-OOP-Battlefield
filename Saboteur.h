#pragma once
#include "Attacker.h"
class Saboteur : public Attacker
{
public:
	Saboteur(const wchar_t *f, const Position &p, const int c);
	~Saboteur();

	const Size & GetSize() const;
	const wchar_t * GetFilename() const;
	const int & GetColour() const;

	void RestoreMovements();

private:
	const wchar_t* filename;
	int strength, range;
};
