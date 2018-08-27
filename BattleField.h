#pragma once
#include "EasyGraphics.h"
#include "IUnit.h"
#include "UnitBuilder.h"
#include "Player.h"
#include "Saboteur.h"
#include "Healer.h"
#include "Medic.h"
#include "Mechanic.h"
#include "Armoury.h"
#include "Vehicle.h"
#include "DefenceTurret.h"
#include "Factory.h"
#include <list>

// this IUnit structure is designed to give you some skeleton code to work with, however it is expected that you
// will replace this with a suitable OO-base class hierarchy

class BattleField : public EasyGraphics
{
public:
	BattleField(HINSTANCE hInstance);
	~BattleField();

protected:
	virtual void onCreate();
	virtual void onDraw();
	virtual void onLButtonDown(UINT nFlags, int x, int y);
	virtual void onRButtonDown(UINT nFlags, int x, int y);
	virtual void onMouseMove(UINT nFlags, int x, int y);
	virtual void onChar(UINT nChar, UINT nRepCnt, UINT nFlags);

private:
	static const int CELL_SIZE=30;  // size of a cell will be 20 pixels
	static const int CELLS_ACROSS=35; // number of cells in the x-direction
	static const int CELLS_DOWN=20; // number of cells in the y-direction
	static const int PLAYER_ONE_COLOUR=clDarkRed;
	static const int PLAYER_TWO_COLOUR=clDarkBlue;
  
	static const int CONSTRUCTION_YARD=0;
	static const int ARMOURY=1;
	static const int DEFENCE_WALL=2;
	static const int DEFENCE_TURRET=3;
	static const int SOLDIER=4;
	static const int MEDIC=5;
	static const int MECHANIC=6;
	static const int SABOTEUR=7;
	static const int WARTHOG = 8;
	static const int FACTORY = 9;
	static const int TANK = 10;
	static const int NO_OF_UNITS = 11;

	static const wchar_t* UNIT_ASSETS[NO_OF_UNITS]; // stores the filenames of the bitmaps used for the different units
	int unitID;

	// Players
	Player *p1, *p2, *player;

	int unitType = 0;

	// player turns
	int turn;
	int winner = 0;

	// hold our battle units
	int noofunits;
	std::list<IUnit*> units;

	// marks an infantry to be moved
	bool isMoved;

	// marks a placing unit
	bool isToPlace;

	// the currently selected unit, or NULL if none is selected
	IUnit* selectedunit;

	//
	IUnit* tomoveunit;

	// a pointer to a unit being placed
	IUnit* toplaceunit;

	// used to hold the currently hovered-over cell (updated in mousemove)
	POINT currentcell;

	// used to save initial coordinate of moving unit
	POINT premovepos;
  
  // playarea is used to store the board state - makes life easy when figuring out whether a space is free - not used for drawing though
  IUnit* playarea[CELLS_ACROSS][CELLS_DOWN];  

  void drawUnit(const IUnit* unit);  // draws a unit
  void drawStatus();  // draw the status text at the bottom of the window
  void drawRedCross(const int & x, const int & y, const int & width, const int & height);
  const int & getDistanceDifference(const Position & source, const Position & destination);
  void updatePlayArea();  // updates the playarea array using the units array (does a complete update)
  void addToPlayArea(IUnit* unit);  // places the unit onto the playarea
  bool canMoveUnit(const IUnit * unit); // checks to make sure the playarea is clear to place the unit
  bool canPlaceStructure(const IUnit* structure);  // checks to make sure a structure is within range of another
  void endTurn();

  const float getSpaces(const IUnit * s);
  void checkRange();
  void findRange(const IUnit * c, Position p, const int & pEnd, const int & nEnd, const int & ux, const int & uy);
  void generateRangeGrid(const IUnit * c, const Position & p, const int & i, const int & j);
  const float calculateDistanceSqr(const Position & p, const Size & s, const float & tx, const float & ty);
  void heal(IUnit * c);
  void fight(IUnit * c);
  void checkUnitOnStructure(IUnit * c);
  void eliminateEnemy(IUnit * killedunit);

	const bool checkIfGameOver();
	const bool isDistanceValid(const IUnit * source, const IUnit * destination);
	Position updatePosition(IUnit * c, const int & i, const int & j);
	void createStructure(UINT nChar);
	void createInfantry(UINT nChar);
	void createVehicle(UINT nChar);
	void moveUnit(UINT nChar);
	void checkBalance();
	const bool isPlayerTurn(const IUnit* u);
	void startTurn();
	void changePlayer();
};

inline void BattleField::addToPlayArea(IUnit* unit)
{
	for (int i = 0; i < unit->GetSize().width; i++)
		for (int j = 0; j < unit->GetSize().height; j++)
			playarea[unit->GetPosition().x + i][unit->GetPosition().y + j] = unit;
}

inline void BattleField::drawRedCross(const int & x, const int & y, const int & width, const int & height)
{
	setPenColour(clRed, 2);
	const int left=x*CELL_SIZE;
	const int right=(x+width)*CELL_SIZE;
	const int top=y*CELL_SIZE;
	const int bottom=(y+height)*CELL_SIZE;
	drawLine(left, top, right, bottom);
	drawLine(right, top, left, bottom);
}

inline const int & BattleField::getDistanceDifference(const Position & source, const Position & destination) {
	return (int)sqrt((destination.x - source.x) * (destination.x - source.x)
		+ (destination.y - source.y) * (destination.y - source.y)
	);
}

inline const bool BattleField::isDistanceValid(const IUnit* source, const IUnit* destination) {
	if (destination != nullptr)
		if (// check if unit belongs to player
			source->GetColour() == destination->GetColour() &&
			// check if the structure placed is an armoury and other units are structures
			(destination == dynamic_cast<Structure*>(const_cast<IUnit*>(destination)) && source == dynamic_cast<UnitBuilder*>(const_cast<IUnit*>(source)) ||
			// check if the structure placed is a vehicle
			(destination == dynamic_cast<Vehicle*>(const_cast<IUnit*>(destination)) && source == dynamic_cast<Factory*>(const_cast<IUnit*>(source)) ||
			// check if the unit placed is an infantry and other units are armouries
			(destination == dynamic_cast<Infantry*>(const_cast<IUnit*>(destination)) && source == dynamic_cast<Armoury*>(const_cast<IUnit*>(source))))))
			return true;
	return false;
}

inline Position BattleField::updatePosition(IUnit * c, const int & i, const int & j) {
	return { c->GetPosition().x + i, c->GetPosition().y + j };
}

inline void BattleField::checkBalance() {
	if (toplaceunit->GetCost() < player->GetBalance()) {
		player->Buy(toplaceunit->GetCost());
		isToPlace = true;
	}
	else
	{
		MessageBox(getHWND(), L"Insufficient funds.", L"BattleField", MB_ICONERROR);
		free(toplaceunit);
	}
}

inline void BattleField::checkUnitOnStructure(IUnit * c) {
	std::list<IUnit*>::iterator it;
	for (it = units.begin(); it != units.end(); it++)
		if (c == dynamic_cast<Mechanic*>(c) || c == dynamic_cast<Saboteur*>(c))
			dynamic_cast<Infantry*>(c)->CheckUnitOnStructure(*it);
}

inline void BattleField::eliminateEnemy(IUnit * killedunit) {
	for (int i = 0; i < killedunit->GetSize().width; i++)
		for (int j = 0; j < killedunit->GetSize().height; j++)
			playarea[killedunit->GetPosition().x + i][killedunit->GetPosition().y + j] = NULL;
	
	delete(killedunit);
}

inline const float BattleField::calculateDistanceSqr(const Position & p, const Size & s, const float & tx, const float & ty) {
	const float cx = p.x + (s.width / 2.0f);
	const float cy = p.y + (s.height / 2.0f);
	const float dx = tx - cx;
	const float dy = ty - cy;
	return (dx * dx) + (dy * dy);
}

inline const float BattleField::getSpaces(const IUnit* s) {
	if (isMoved)
	{
		// determine maximum amount of moves
		if (s == dynamic_cast<Infantry*>(const_cast<IUnit*>(s)))
			return dynamic_cast<Infantry*>(const_cast<IUnit*>(s))->GetMoves();

	}
	else if ((s == dynamic_cast<Infantry*>(const_cast<IUnit*>(s)) && s != dynamic_cast<DefenceTurret*>(const_cast<IUnit*>(s))) || s == dynamic_cast<Vehicle*>(const_cast<IUnit*>(s)))
		// place infantry next to armoury (excluding the multiply inheriting turret)
		return 1.0f;
	else if (s == dynamic_cast<Structure*>(const_cast<IUnit*>(s)))
		// place structure at max. five spaces away from friendly structures
		return 5.0f;
}