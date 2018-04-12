#pragma once

struct Position {
	int x, y;
};

struct Size {
	int width, height;
};

class IUnit
{
public:
	IUnit(const Position & p, int h, const int c);
	virtual ~IUnit() = 0;

	virtual const Size & GetSize() const = 0;
	virtual const wchar_t * GetFilename() const = 0;
	virtual const int & GetColour() const = 0;

	virtual const Position & GetPosition() const;
	virtual const int & GetHealth() const;

	void SetPosition(int x, int y);
	void SetHealth(int changeHealth);

protected:
	Position position;
	int health, colour;
};