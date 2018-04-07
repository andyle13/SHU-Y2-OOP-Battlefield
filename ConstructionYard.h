#pragma once
#include "IUnit.h"

class ConstructionYard : public IUnit
{
public:
	ConstructionYard(const wchar_t *f, const Position &p, Size s, int h, int c);
	~ConstructionYard();

	const Size & GetSize() const;
	const wchar_t * GetFilename() const;
	const int & GetColour() const;

private:
	const wchar_t* filename;
	Size size;
	int colour;
};

