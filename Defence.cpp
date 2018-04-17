#include "Defence.h"



Defence::Defence(const Position &p, const int c, int h, int cost) :
	Structure(p, c, h, cost), size({ 1,1 })
{

}


Defence::~Defence()
{
}
