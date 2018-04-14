#include "Armoury.h"
#include "Soldier.h"
#include "Medic.h"
#include "Mechanic.h"
#include "Saboteur.h"

Armoury::Armoury(const wchar_t *f, const Position &p, const int c)
	: UnitBuilder(p, c, 200), filename(f) {}

Armoury::~Armoury() {}

const int Armoury::GetMaxHealth() const { return maxhealth; }
const std::string Armoury::GetName() const { return name; }
const std::string Armoury::GetOption() const { return option; }
const Size & Armoury::GetSize() const { return size; }
const wchar_t * Armoury::GetFilename() const { return filename; }
const int & Armoury::GetColour() const { return IUnit::GetColour(); }

IUnit * Armoury::GetUnit(const wchar_t * f, const Position & p, const int c, char id) {
	switch (id)
	{
	case '1':
		return new Soldier(f, p, c);
	case '2':
		return new Medic(f, p, c);
	case '3':
		return new Mechanic(f, p, c);
	case '4':
		return new Saboteur(f, p, c);
	default:
		return nullptr;
	}
}