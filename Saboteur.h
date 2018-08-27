#pragma once
#include "Attacker.h"
class Saboteur : public Attacker
{
public:
	Saboteur(const wchar_t *f, const Position &p, const int & c);
	~Saboteur();

	const int GetMaxHealth() const;
	const std::string GetName() const;
	const std::string GetOption() const;
	const Size & GetSize() const;
	const wchar_t * GetFilename() const;
	const int & GetColour() const;
	const int & GetRange() const;
	const int & GetStrength() const;

	void RestoreActions();
	void Attack(IUnit * enemy);
	bool CanAttackStruc(const IUnit* unit);

	void Promote();

private:
	const wchar_t* filename;
	int maxhealth = 100;
	const std::string name = "Saboteur";
	const std::string option = "Attack: Move this unit at least two spaces away from a enemy soldier or place it on an enemy structure.";
};

inline void Saboteur::RestoreActions() {
	hasAttacked = false;
	moves = 2;
}

inline bool Saboteur::CanAttackStruc(const IUnit* unit)
{
	for(int i = 0; i < unit->GetSize().width; i++)
		for(int j = 0; j < unit->GetSize().height; j++)
			if ((position.x == unit->GetPosition().x + i) && (position.y == unit->GetPosition().y + j))
				return true;

	return false;
}