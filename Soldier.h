#pragma once
#include "Attacker.h"
class Soldier :	public Attacker
{
public:
	Soldier(const wchar_t *f, const Position &p, const int c);
	~Soldier();

	const Size & GetSize() const;
	const wchar_t * GetFilename() const;
	const int & GetColour() const;

	void RestoreMovements();

private:
	const wchar_t* filename;
	int strength, range;
};
