#pragma once
#include "Structure.h"
class Defence : public Structure
{
public:
	Defence(const Position &p, const int c, int h, int cost);
	~Defence();
	
protected:
	Size size;
};

