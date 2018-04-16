#include "DefenceWall.h"


DefenceWall::DefenceWall(const wchar_t *f, const Position &p, const int c) 
	: Defence(p, c, 200, 50), filename(f) {}


DefenceWall::~DefenceWall()
{
}

const wchar_t * DefenceWall::GetFilename() const { return filename; }

const int DefenceWall::GetMaxHealth() const { return maxhealth; }
const std::string DefenceWall::GetName() const { return name; }
const std::string DefenceWall::GetOption() const { return option; }
const Size & DefenceWall::GetSize() const { return size; }
const int & DefenceWall::GetColour() const { return colour; }