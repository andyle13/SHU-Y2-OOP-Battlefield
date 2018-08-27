#pragma once
#include "Structure.h"
class Defence : public virtual Structure
{
public:
	Defence(const Position &p, const int & c, int h, const int & cost);
	~Defence();
	
protected:
	Size size;
};

