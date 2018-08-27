#pragma once
#include "Vehicle.h"
class Tank :
	public virtual Vehicle, public virtual Attacker
{
public:
	Tank(const wchar_t *f, const Position &p, const int & c);
	~Tank();

	void Promote();
	void Attack(IUnit * enemy);
	const int & GetRange() const;
	const int & GetStrength() const;
	const int GetMaxHealth() const;
	const std::string GetName() const;
	const std::string GetOption() const;
	const Size & GetSize() const;
	const wchar_t * GetFilename() const;
	const int & GetColour() const;

	void RestoreActions();

private:
	const wchar_t* filename;
	int maxhealth = 350;
	const std::string name = "Tank";
	const std::string option = "1) Move";
};

inline void Tank::RestoreActions() {
	hasAttacked = true;
	moves = 2;
}
