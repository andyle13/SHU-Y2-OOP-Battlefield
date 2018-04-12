#include "UnitBuilder.h"

UnitBuilder::UnitBuilder(const Position &p, int h, const int c)
	: IUnit(p, c, h), size({ 2, 2 }) {}


UnitBuilder::~UnitBuilder() {}
