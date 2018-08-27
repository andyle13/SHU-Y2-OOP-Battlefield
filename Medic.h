#pragma once
#include "Healer.h"
class Medic : public Healer
{
public:
	Medic(const wchar_t *f, const Position &p, const int & c);
	~Medic();

	const int GetMaxHealth() const;
	const std::string GetName() const;
	const std::string GetOption() const;
	const Size & GetSize() const;
	const wchar_t * GetFilename() const;
	const int & GetColour() const;

	void RestoreActions();

private:
	const wchar_t* filename;
	const int maxhealth = 60;
	const std::string name = "Medic";
	const std::string option = "Heal: Place the medic on a friendly infantry to heal.";
};
