#pragma once
#include "Healer.h"
class Mechanic : public Healer
{
public:
	Mechanic(const wchar_t *f, const Position &p, const int c);
	~Mechanic();

	const Size & GetSize() const;
	const wchar_t * GetFilename() const;
	const int & GetColour() const;

	void RestoreMovements();

private:
	const wchar_t* filename;
};
