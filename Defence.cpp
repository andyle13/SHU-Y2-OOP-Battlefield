#include "Defence.h"

Defence::Defence(const Position &p, const int & c, int h, const int & cost) :
	Structure(p, { 1,1 }, c, h, cost), size({ 1,1 }) {}

Defence::~Defence() {}
