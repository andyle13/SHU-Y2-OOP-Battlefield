#pragma once
#include <string>

struct Position {
	int x, y;
};

struct Size {
	int width, height;
};

class IUnit
{
public:
	IUnit(const Position & p, const int c, int h, int cos);
	virtual ~IUnit() = 0;

	virtual const Size & GetSize() const = 0;
	virtual const wchar_t * GetFilename() const = 0;
	virtual const int GetMaxHealth() const = 0;
	virtual const std::string GetName() const = 0;
	virtual const std::string GetOption() const = 0;

	const int GetCost() const;
	virtual const Position & GetPosition() const;
	virtual const int & GetHealth() const;
	virtual const int & GetColour() const;
	void SetPosition(int x, int y);
	void SetHealth(int changeHealth);
	void DecreaseHealth(int damage);

protected:
	Position position;
	int health;
	const int colour, cost;
};