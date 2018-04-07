#pragma once
#include "EasyGraphics.h"
#include "IUnit.h"
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
  static const int NO_OF_UNITS=8;

  static const wchar_t* UNIT_ASSETS[NO_OF_UNITS]; // stores the filenames of the bitmaps used for the different units


  // hold our battle units
  int noofunits;
  /*
	  static const int DEMO_MAX_UINTS=10; // you shouldn't have a limit on the number of units
	  IUnit* units[DEMO_MAX_UINTS];
  */

  std::list<IUnit*> units;

  // the currently selected unit, or NULL if none is selected
  IUnit* selectedunit;

  // a pointer to a unit being placed
  IUnit* toplaceunit;

  // used to hold the currently hovered-over cell (updated in mousemove)
  POINT currentcell;
  
  // playarea is used to store the board state - makes life easy when figuring out whether a space is free - not used for drawing though
  IUnit* playarea[CELLS_ACROSS][CELLS_DOWN];  

  void drawUnit(const IUnit* unit);  // draws a unit
  void drawStatus();  // draw the status text at the bottom of the window
  void drawWhiteCross(const int x, const int y, const int width, const int height);
  void updatePlayArea();  // updates the playarea array using the units array (does a complete update)
  void addToPlayArea(IUnit* unit);  // places the unit onto the playarea
  bool canPlaceUnit(const IUnit* unit);  // checks to make sure the playarea is clear to place the unit
  bool canPlaceStructure(const IUnit* structure);  // checks to make sure a structure is within range of another
};

inline void BattleField::addToPlayArea(IUnit* unit)
{
  for (int i = 0; i < unit->GetSize().width; i++)
    for (int j = 0; j < unit->GetSize().height; j++)
      playarea[unit->GetPosition().x + i][unit->GetPosition().y + j] = unit;
}

inline void BattleField::drawWhiteCross(const int x, const int y, const int width, const int height)
{
  setPenColour(clWhite, 2);
  const int left=x*CELL_SIZE;
  const int right=(x+width)*CELL_SIZE;
  const int top=y*CELL_SIZE;
  const int bottom=(y+height)*CELL_SIZE;
  drawLine(left, top, right, bottom);
  drawLine(right, top, left, bottom);
}