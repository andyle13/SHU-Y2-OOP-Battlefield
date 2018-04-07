#include "BattleField.h"
#include "ConstructionYard.h"

// the index of each asset must align with the constant used to identify that particular unit, 
// e.g. static const int DEFENCE_TURRET=3; means that the asset for the defence turret must be in index 3
const wchar_t* BattleField::UNIT_ASSETS[NO_OF_UNITS]=
{
  L"artwork\\ConstructionYard.bmp",
  L"artwork\\Armoury.bmp",
  L"artwork\\DefenceWall.bmp",
  L"artwork\\DefenceTurret.bmp",
  L"artwork\\Soldier.bmp",
  L"artwork\\Medic.bmp",
  L"artwork\\Mechanic.bmp",
  L"artwork\\Saboteur.bmp"
};

BattleField::BattleField(HINSTANCE hInstance) : selectedunit(NULL), toplaceunit(NULL)
{
  currentcell={-1, -1}; // out of bounds

  // create two initial construction yard structures - I am using colour to determine which unit belongs to which player... a little bit of a fudge
  noofunits = 2;
  //units[0]=(IUnit*) malloc(sizeof(IUnit));
  units.push_back(new ConstructionYard(UNIT_ASSETS[CONSTRUCTION_YARD], { 2, (CELLS_DOWN - 2) / 2 }, { 2, 2 }, 1000, PLAYER_ONE_COLOUR));

  //units[1]=(IUnit*) malloc(sizeof(IUnit));
  units.push_back(new ConstructionYard(UNIT_ASSETS[CONSTRUCTION_YARD], { CELLS_ACROSS - 4, (CELLS_DOWN - 2) / 2 }, { 2, 2 }, 1000, PLAYER_TWO_COLOUR));

  updatePlayArea();

  setImmediateDrawMode(false);

  // remember to call this method last as it goes modal and doesn't return until the window is closed
  create(hInstance, (CELLS_ACROSS*CELL_SIZE)+16, (CELLS_DOWN*CELL_SIZE)+8*CELL_SIZE, 120, true);
}


BattleField::~BattleField()
{
	std::list<IUnit*>::iterator it;
	for (it = units.begin(); it != units.end(); it++)
		free(*it);
}

void BattleField::onCreate()
{
  EasyGraphics::onCreate();
  ::SetWindowText(getHWND(), L"Battlefield Strategy Game");
}

void BattleField::onDraw()
{
  clrscr(clBlack);

  // Draw the game area
  drawBitmap(L"artwork\\ground.bmp", 0, 0, CELLS_ACROSS*CELL_SIZE, CELLS_DOWN*CELL_SIZE);

  // Draw all the units
  std::list<IUnit*>::iterator it;
  for (it = units.begin(); it != units.end(); it++)
	  drawUnit(*it);

  // Draw the current cell highlight if the mouse is over the game board
  if (currentcell.x>=0 && currentcell.y>=0)
  {
    setPenColour(clWhite, 2);
    drawRectangle(currentcell.x*CELL_SIZE, currentcell.y*CELL_SIZE, CELL_SIZE, CELL_SIZE, false);
  }

  if (selectedunit && selectedunit->GetFilename()==UNIT_ASSETS[SOLDIER])
  {
    int dx=selectedunit->GetPosition().x-currentcell.x;
    int dy=selectedunit->GetPosition().y-currentcell.y;
    
    bool valid=true;
    if (dx==0 && dy==0)
      valid=false;
    else
    {
      // ...
    }
    
    if (!valid)
      drawWhiteCross(currentcell.x, currentcell.y, selectedunit->GetSize().width, selectedunit->GetSize().height);
  }

  // draw the toplaceunit if there is one and the location is valid
  if (toplaceunit && currentcell.x != -1 
	  && currentcell.x+toplaceunit->GetSize().width <= CELLS_ACROSS
	  && currentcell.y+toplaceunit->GetSize().height <= CELLS_DOWN)
  {
    toplaceunit->SetPosition(currentcell.x, currentcell.y);
    drawUnit(toplaceunit);

    // check to see if the unit can be placed here (i.e the play area is free)
    if (!canPlaceUnit(toplaceunit))
      drawWhiteCross(toplaceunit->GetPosition().x, toplaceunit->GetPosition().y, toplaceunit->GetSize().width, toplaceunit->GetSize().height);
    else // check if location rules are valid
    {
      // some more horrible code, although this demo only allows you to place an armoury so it is valid, but attempt to replace this with cleaner code
      if (toplaceunit->GetFilename() == UNIT_ASSETS[SOLDIER] || (toplaceunit->GetFilename() == UNIT_ASSETS[ARMOURY] && !canPlaceStructure(toplaceunit)))
      {
        // draw a white cross through the unit to indicate it cannot be placed here
        drawWhiteCross(toplaceunit->GetPosition().x, toplaceunit->GetPosition().y, toplaceunit->GetSize().width, toplaceunit->GetSize().height);
      }
    }
  }

  drawStatus();

  // immediate graphics draw has been disabled so we need to call the onDraw method in the EasyGraphics base-class to flush the updates to the screen
  EasyGraphics::onDraw();
}

bool BattleField::canPlaceUnit(const IUnit* unit)
{
  for (int i=0; i < unit->GetSize().width; i++)
    for (int j=0; j < unit->GetSize().height; j++)
      if (playarea[unit->GetPosition().x + i][unit->GetPosition().y + j]) // use the pointer as true or false
        return false;
  return true;
}

// This method should be optimised with your OO-base class structure
bool BattleField::canPlaceStructure(const IUnit* structure)
{
  // use centre locations and calculate the tolerance allowed based on width and 5 spaces
  const float tx=structure->GetPosition().x+(structure->GetSize().width/2.0f);
  const float ty=structure->GetPosition().y+(structure->GetSize().height/2.0f);
  const float tolerance=(5.0f+structure->GetSize().width)*(5.0f+structure->GetSize().width);
  
  std::list<IUnit*>::iterator it;
  for (it = units.begin(); it != units.end(); it++)
  {
    if ((*it)->GetColour() == structure->GetColour())
    {
      const float cx=(*it)->GetPosition().x+((*it)->GetSize().width/2.0f);
      const float cy=(*it)->GetPosition().y+((*it)->GetSize().height/2.0f);
      const float dx=tx-cx;
      const float dy=ty-cy;
      const float distsqr=(dx*dx)+(dy*dy);
      if (distsqr<tolerance) // don't bother to sqrt distsqr, just sqr both sides of the equation for speed
        return true;
    }
  }
  return false;
}

void BattleField::drawUnit(const IUnit* unit)
{
  const int x=unit->GetPosition().x*CELL_SIZE;
  const int y=unit->GetPosition().y*CELL_SIZE;
  const int width=unit->GetSize().width*CELL_SIZE;
  const int height=unit->GetSize().height*CELL_SIZE;
  if (unit==selectedunit)
    setPenColour(clGrey, 4);
  else
    setPenColour(unit->GetColour(), 2);
  selectBackColour(unit->GetColour());
  drawRectangle(x, y, width, height, true);
  drawBitmap(unit->GetFilename(), x, y, width, height, 0x0000FF00);  // green is my transparent colour
}

void BattleField::drawStatus()
{
  // Draw status information
  gotoxy(0, 1+(CELLS_DOWN*CELL_SIZE)/getPixelsPerRow());
  selectTextColour(clWhite);
  selectBackColour(clBlack);

  // this is getting into some horrible code because OO classes aren't being used in this skeleton project
  // so rework once you have implemented an OO design for the units - note, as it is a skeleton project
  // not all units have values here either
  if (selectedunit)
  {

    int maxhealth;
    const char* name;
    const char* options;
    if (selectedunit->GetFilename() == UNIT_ASSETS[CONSTRUCTION_YARD]) // note that his is checking the memory references to the literal string filename and not the contents
    {
      name="Construction Yard";
      options="1) Create Armoury\n2) Create Defence Wall\n3) Create Defence Turret";
      maxhealth=1000;
    }
    else if (selectedunit->GetFilename() == UNIT_ASSETS[ARMOURY])
    {
      name="Armoury"; 
      options="1) Create Solider\n2) Create Medic\n3) Create Mechanic\n4) Create Saboteur";
      maxhealth=200;
    }
    else if (selectedunit->GetFilename() == UNIT_ASSETS[SOLDIER])
    {
      name="Soldier"; 
      maxhealth=150;
      options="Move soldier or right-click to unselect";
    }
    else
    {
      name="Unknown";
      maxhealth=0;
      options="Unknown";
    }

    (*this) << "Player " << (selectedunit->GetColour() == PLAYER_ONE_COLOUR? "1" : "2") << ": " << name << "\n";
    (*this) << "Health: " << selectedunit->GetHealth() << " of " << maxhealth << "\n";
    (*this) << options;
  }
  else
  {
    (*this) << "Player 1 to create a move... click a unit to do something with it";
  }

}

void BattleField::onChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
  // some more nasty code due to the lack of OO-based classes
  if (selectedunit)
  {
    if (selectedunit->GetFilename() == UNIT_ASSETS[CONSTRUCTION_YARD]) // note that his is checking the memory references to the literal string filename and not the contents
    {
      if (nChar=='1') // create armoury
      {
        // check sufficient funds
        toplaceunit=(IUnit*) malloc(sizeof(IUnit));
		//*toplaceunit = new Armoury(UNIT_ASSETS[ARMOURY], { currentcell.x, currentcell.y }, { 2, 2 }, 200, selectedunit->GetColour());
      }
      else
        MessageBox(getHWND(), L"Creation not currently supported", L"BattleField", MB_ICONERROR);
    }
    else if (selectedunit->GetFilename() == UNIT_ASSETS[ARMOURY])
    {
      if (nChar=='1') // create a soldier
      {
        toplaceunit=(IUnit*) malloc(sizeof(IUnit));
		//*toplaceunit = new Soldier(UNIT_ASSETS[SOLDIER], { currentcell.x, currentcell.y }, { 1, 1 }, 150, selectedunit->GetColour());
      }
      else
        MessageBox(getHWND(), L"Creation not currently supported", L"BattleField", MB_ICONERROR);
    }
    onDraw();
  }
}

void BattleField::onLButtonDown(UINT nFlags, int x, int y)
{
  if (toplaceunit)
  {
    if (canPlaceUnit(toplaceunit) && canPlaceStructure(toplaceunit))
    {
      //assert(noofunits < units.max_size);
      units.push_back(toplaceunit);
      addToPlayArea(toplaceunit);
      toplaceunit=NULL;
    }
    else
      MessageBox(getHWND(), L"Cannot place unit there", L"BattleField", MB_ICONERROR);
  }
  else
  {
    if (currentcell.x>=0 && currentcell.y>=0)
      selectedunit=playarea[currentcell.x][currentcell.y];
  }
  onDraw();
}

void BattleField::onRButtonDown(UINT nFlags, int x, int y)
{
  if (toplaceunit)
  {
    free(toplaceunit);
    toplaceunit=NULL;
  }
  else if (selectedunit)
    selectedunit=NULL;
  onDraw();
}

void BattleField::onMouseMove(UINT nFlags, int x, int y)
{
  x/=CELL_SIZE;
  y/=CELL_SIZE;
  if (x>=0 && x<CELLS_ACROSS && y>=0 && y<CELLS_DOWN)
    currentcell={x, y};
  else
    currentcell={-1, -1};

  // redraw the screen to refresh highlight
  onDraw();
}

void BattleField::updatePlayArea()
{
  // Reset the play area
  for (int i=0; i<CELLS_ACROSS; i++)
    for (int j=0; j<CELLS_DOWN; j++)
      playarea[i][j]=NULL;

  // Put the units onto the play area - using memory references to make it easier to manipulate the unit
  std::list<IUnit*>::iterator it;
  for (it = units.begin(); it != units.end(); it++)
    addToPlayArea(*it);
}
