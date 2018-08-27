#pragma once
#include "Vehicle.h"
class Warthog :
	public virtual Vehicle, public virtual Attacker
{
public:
	Warthog(const wchar_t *f, const Position &p, const int c);
	~Warthog();

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
	int maxhealth = 250;
	const std::string name = "Warthog";
	const std::string option = "1) Move";
};

inline void Warthog::RestoreActions() {
	hasAttacked = true;
	moves = 6;
}