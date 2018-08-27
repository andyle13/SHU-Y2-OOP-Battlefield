#pragma once
#include "Healer.h"
class Mechanic : public Healer
{
public:
	Mechanic(const wchar_t *f, const Position &p, const int & c);
	~Mechanic();

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
	const std::string name = "Mechanic";
	const std::string option = "Repair: Place the mechanic on a friendly structure to repair.";
};
