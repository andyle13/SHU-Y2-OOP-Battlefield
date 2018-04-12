#include "Infantry.h"

Infantry::Infantry(const Position &p, int h, const int c, int m)
	: IUnit(p, h, c), moves(m), size({ 1,1 }) {}

Infantry::~Infantry() {}
