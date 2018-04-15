#pragma once
#include "Defence.h"
class DefenceWall :
	public Defence
{
public:
	DefenceWall(const Position &p, const int c);
	~DefenceWall();
};

