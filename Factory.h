#pragma once
#include "UnitBuilder.h"
class Factory :
	public UnitBuilder
{
public:
	Factory(const wchar_t *f, const Position &p, const int c);
	~Factory();

	const int GetMaxHealth() const;
	const std::string GetName() const;
	const std::string GetOption() const;
	const Size & GetSize() const;
	const wchar_t * GetFilename() const;
	const int & GetColour() const;

	void RestoreActions();

	IUnit * GetUnit(const wchar_t * f, const Position & p, const int & c, const char & id);

private:
	const wchar_t* filename;
	const int maxhealth = 200;
	const std::string name = "Factory";
	const std::string option = "1) Create Truck\n2) Create Tank";
};

