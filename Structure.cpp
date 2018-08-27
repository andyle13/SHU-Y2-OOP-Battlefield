#include "Structure.h"

Structure::Structure(const Position & p, const Size & s, const int & c, int h, const int & cost)
	: IUnit(p, s, c, h, cost) {}

Structure::~Structure() {}
