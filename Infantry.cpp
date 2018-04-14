#include "Infantry.h"

Infantry::Infantry(const Position &p, const int c, int h, int m)
	: IUnit(p, c, h), moves(m), size({ 1,1 }) {}

Infantry::~Infantry() {}
