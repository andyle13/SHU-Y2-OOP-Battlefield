#pragma once
#include "Healer.h"
class Medic : public Healer
{
public:
	Medic(const wchar_t *f, const Position &p, const int c);
	~Medic();

	const Size & GetSize() const;
	const wchar_t * GetFilename() const;
	const int & GetColour() const;

	void RestoreMovements();

private:
	const wchar_t* filename;
};
