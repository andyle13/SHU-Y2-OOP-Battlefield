#pragma once
#include <string>
#include "UnitBuilder.h"

class ConstructionYard : public UnitBuilder
{
public:
	ConstructionYard(const wchar_t *f, const Position &p, const int & c);
	~ConstructionYard();

	const int GetMaxHealth() const;
	const std::string GetName() const;
	const std::string GetOption() const;

	const Size & GetSize() const;
	const wchar_t * GetFilename() const;
	const int & GetColour() const;
	void RestoreActions();
	IUnit * GetUnit(const wchar_t *f, const Position &p, const int & c, const char & id);

private:
	const wchar_t* filename;
	const int maxhealth = 1000;
	const std::string name = "Construction Yard";
	const std::string option = "1) Create Armoury\n2) Create Defence Wall\n3) Create Defence Turret\n4) Create Factory";
};

inline void ConstructionYard::RestoreActions() { hasPlaced = false; }
