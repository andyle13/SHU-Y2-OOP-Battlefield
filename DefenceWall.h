#pragma once
#include "Defence.h"
class DefenceWall :
	public Defence
{
public:
	DefenceWall(const wchar_t *f, const Position &p, const int c);
	~DefenceWall();


	const int GetMaxHealth() const;
	const std::string GetName() const;
	const std::string GetOption() const;
	const Size & GetSize() const;
	const wchar_t * GetFilename() const;
	const int & GetColour() const;

private:
	const wchar_t* filename;
	const int maxhealth = 200;
	const std::string name = "Defence Wall";
	const std::string option = "";
};

