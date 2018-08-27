#include "Vehicle.h"

Vehicle::Vehicle(const Position &p, const int & c, int h, const int & cost) 
	: IUnit(p, { 1,1 }, c, h, cost) {}
Vehicle::~Vehicle() {}
