#include "Factory.h"
#include "Warthog.h"
#include "Tank.h"


Factory::Factory(const wchar_t *f, const Position &p, const int c)
	: UnitBuilder(p, c, 200, 250), IUnit(p, { 2,2 }, c, 200, 250), filename(f) {}


Factory::~Factory()
{
}

const int Factory::GetMaxHealth() const { return maxhealth; }
const std::string Factory::GetName() const { return name; }
const std::string Factory::GetOption() const { return option; }
const Size & Factory::GetSize() const { return UnitBuilder::size; }
const wchar_t * Factory::GetFilename() const { return filename; }
const int & Factory::GetColour() const { return IUnit::GetColour(); }

void Factory::RestoreActions() {
	hasPlaced = false;
}

IUnit * Factory::GetUnit(const wchar_t * f, const Position & p, const int & c, const char & id) {
	switch (id)
	{
	case '1':
		return new Warthog(f, p, c);
	case '2':
		return new Tank(f, p, c);
	default:
		return nullptr;
	}
}
