#pragma once
#include "UnitBuilder.h"

class Armoury :	public UnitBuilder
{
public:
	Armoury(const wchar_t *f, const Position &p, const int c);
	~Armoury();

	const Size & GetSize() const;
	const wchar_t * GetFilename() const;
	const int & GetColour() const;

	IUnit * GetUnit(const wchar_t * f, const Position & p, const int c, char id);

private:
	const wchar_t* filename;
};

