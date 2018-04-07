#include "ConstructionYard.h"

ConstructionYard::ConstructionYard(const wchar_t *f, const Position &p, Size s, int h, int c)
	: IUnit(p, h), filename(f), size(s), colour(c) {}

ConstructionYard::~ConstructionYard() {}

const Size & ConstructionYard::GetSize() const { return size; }
const wchar_t * ConstructionYard::GetFilename() const { return filename; }
const int & ConstructionYard::GetColour() const { return colour; }