#include "ConstructionYard.h"
#include "UnitBuilder.h"
#include "Armoury.h"

ConstructionYard::ConstructionYard(const wchar_t *f, const Position &p, const int c)
	: UnitBuilder(p, c, 1000), filename(f) {}

ConstructionYard::~ConstructionYard() {}

const int ConstructionYard::GetMaxHealth() const { return maxhealth; }
const std::string ConstructionYard::GetName() const { return name; }
const std::string ConstructionYard::GetOption() const { return option; }
const Size & ConstructionYard::GetSize() const { return size; }
const wchar_t * ConstructionYard::GetFilename() const { return filename; }
const int & ConstructionYard::GetColour() const { return IUnit::GetColour(); }

IUnit * ConstructionYard::GetUnit(const wchar_t *f, const Position &p, const int c, char id) {
	switch (id)
	{
	case '1':
		return new Armoury(f, p, c);
	default:
		return nullptr;
	}
}