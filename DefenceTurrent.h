#pragma once
#include "Defence.h"
class DefenceTurrent :
	public Defence
{
public:
	DefenceTurrent(const wchar_t *f, const Position &p, const int c);
	~DefenceTurrent();
	void Attack(IUnit* p);
	const int GetMaxHealth() const;
	const std::string GetName() const;
	const std::string GetOption() const;
	const Size & GetSize() const;
	const wchar_t * GetFilename() const;
	const int & GetColour() const;
	//const bool CanAttack(IUnit* p) const;

private:
	const wchar_t * filename;
	const int maxhealth = 200;
	const std::string name = "Defence Turrent";
	const std::string option = "Use turrent to attack enemy or right-click to deselect";
};

