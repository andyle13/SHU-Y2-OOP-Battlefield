#include "BattleField.h"
//#include "Player.h"
#include "ConstructionYard.h"
#include "Armoury.h"
#include "Attacker.h"
#include "Saboteur.h"
#include "Healer.h"
#include "Medic.h"
#include "Mechanic.h"
#include "Structure.h"
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

BattleField::BattleField(HINSTANCE hInstance) : selectedunit(NULL), toplaceunit(NULL), isMoved(false)
{
	currentcell = {-1, -1}; // out of bounds

	// create two initial construction yard structures - I am using colour to determine which unit belongs to which player... a little bit of a fudge
	turn = 1;
	noofunits = 2;
	int thisx, thisy;
	
	p1 = new Player("Player 1", PLAYER_ONE_COLOUR);
	p2 = new Player("Player 2", PLAYER_TWO_COLOUR);
	player = p1;

	units.push_back(
		new ConstructionYard(
			UNIT_ASSETS[CONSTRUCTION_YARD],
			{ 2, (CELLS_DOWN - 2) / 2 },
			p1->GetColour())
	);
	units.push_back(
		new ConstructionYard(
			UNIT_ASSETS[CONSTRUCTION_YARD], 
			{ CELLS_ACROSS - 4, (CELLS_DOWN - 2) / 2 }, 
			p2->GetColour())
	);
	updatePlayArea();
	setImmediateDrawMode(false);

	// remember to call this method last as it goes modal and doesn't return until the window is closed
	create(hInstance, (CELLS_ACROSS*CELL_SIZE)+16, (CELLS_DOWN*CELL_SIZE)+8*CELL_SIZE, 120, true);
}

BattleField::~BattleField()
{
	std::list<IUnit*>::iterator unitIT;
	for (unitIT = units.begin(); unitIT != units.end(); unitIT++)
		delete (*unitIT);
	

	// This keeps crashing the program when it closes
	/*
	for (unitIT = tempunits.begin(); unitIT != tempunits.end(); unitIT++)
		delete (*unitIT);*/
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

	if (selectedunit && selectedunit == dynamic_cast<Infantry*>(selectedunit))
	{
		int dx=selectedunit->GetPosition().x-currentcell.x;
		int dy=selectedunit->GetPosition().y-currentcell.y;
    
		bool valid=true;
		if (dx == 0 && dy == 0)
			valid = false;
		else{
			valid = true;
		}
    
		if (!valid)
			drawRedCross(currentcell.x, currentcell.y, selectedunit->GetSize().width, selectedunit->GetSize().height);
	}

	// draw the toplaceunit if there is one and the location is valid
	if (toplaceunit && currentcell.x != -1 && currentcell.x+toplaceunit->GetSize().width <= CELLS_ACROSS && currentcell.y+toplaceunit->GetSize().height <= CELLS_DOWN)
	{
		toplaceunit->SetPosition(currentcell.x, currentcell.y);
		drawUnit(toplaceunit);
		canPlaceStructure(toplaceunit);
		
		// check if the unit is not a healer type - healer units can be placed on occupied areas
		//if (!(selectedunit == dynamic_cast<Healer*>(selectedunit)))
		//{
			// check to see if the unit can be placed here (i.e the play area is free)
			if (!canPlaceUnit(toplaceunit))
				drawRedCross(toplaceunit->GetPosition().x,
					toplaceunit->GetPosition().y,
					toplaceunit->GetSize().width,
					toplaceunit->GetSize().height
				);
			else // check if location rules are valid
			{
				if (!canPlaceStructure(toplaceunit))
				{
					// draw a white cross through the unit to indicate it cannot be placed here
					drawRedCross(toplaceunit->GetPosition().x,
						toplaceunit->GetPosition().y,
						toplaceunit->GetSize().width,
						toplaceunit->GetSize().height
					);
				}
			}
		/*}
		else
		{
			std::list<IUnit*>::iterator loop;
			// place healer type
			if (selectedunit == dynamic_cast<Medic*>(selectedunit))
			{
				for (loop = units.begin(); loop != units.end(); loop++)
				{
					if (((*loop)->GetPosition().x == currentcell.x) && ((*loop)->GetPosition().y == currentcell.y))
					{
						if (*loop != selectedunit)
						{
							if (!(existInList(*loop)))
							{
								tempunits.push_back(*loop);
							}
						}
					}
				}
			}
			else if (selectedunit == dynamic_cast<Mechanic*>(selectedunit))
			{
				for (loop = units.begin(); loop != units.end(); loop++)
				{
					if (((*loop)->GetPosition().x == currentcell.x) && ((*loop)->GetPosition().y == currentcell.y))
					{
						if (*loop != selectedunit)
						{
							if (!(existInList(*loop)))
							{
								tempunits.push_back(*loop);
							}
						}
					}
				}
			}
		}*/
	}

	drawStatus();

	// immediate graphics draw has been disabled so we need to call the onDraw method in the EasyGraphics base-class to flush the updates to the screen
	EasyGraphics::onDraw();
}

const bool BattleField::existInList(const IUnit* unit)
{
	std::list<IUnit*>::iterator itt;
	for (itt = tempunits.begin(); itt != tempunits.end(); itt++)
		if (*itt == unit)
			return true;
	return false;
}

bool BattleField::canPlaceUnit(const IUnit* unit)
{
	for (int i = 0; i < unit->GetSize().width; i++)
		for (int j = 0; j < unit->GetSize().height; j++)
			if (playarea[unit->GetPosition().x + i][unit->GetPosition().y + j]) { // use the pointer as true or false
				//if (selectedunit != dynamic_cast<Healer*>(selectedunit))
					return false;
				/*else
				{
					if (selectedunit == dynamic_cast<Medic*>(selectedunit))
					{
						if (selectedunit != dynamic_cast<Infantry*>(selectedunit))
							return false;
						else
						{
							Medic* healer = dynamic_cast<Medic*>(selectedunit);

							std::list<IUnit*>::iterator it;
							for (it = units.begin(); it != units.end(); it++)
							{
								if (existInList(*it))
								{
									healer->Heal(*it);
								}
							}
						}
					}
					else if (selectedunit == dynamic_cast<Mechanic*>(selectedunit))
					{
						if (playarea[currentcell.x][currentcell.y] != dynamic_cast<Structure*>(playarea[currentcell.x][currentcell.y]))
							return false;
						else
						{
							Mechanic* healer = dynamic_cast<Mechanic*>(selectedunit);

							std::list<IUnit*>::iterator it;
							for (it = units.begin(); it != units.end(); it++)
							{
								if (existInList(*it))
								{
									healer->Heal(*it);
								}
							}
						}
					}
					else
					{
						return false;
					}
				}*/
			}
	//updatePlayArea();
	return true;
}

// This method should be optimised with your OO-base class structure
bool BattleField::canPlaceStructure(const IUnit* structure)
{
	// use centre locations and calculate the tolerance allowed based on width and allowed spaces
	const float tx = structure->GetPosition().x + (structure->GetSize().width / 2.0f);
	const float ty = structure->GetPosition().y + (structure->GetSize().height / 2.0f);
	const float tolerance = pow((getSpaces(structure) + structure->GetSize().width), 2);
	
	if (!isMoved) {
		std::list<IUnit*>::iterator it;
		for (it = units.begin(); it != units.end(); it++)
		{
			if ((*it)->GetColour() == structure->GetColour())
			{
				const float distsqr = calculateDistanceSqr((*it)->GetPosition(), (*it)->GetSize(), tx, ty);
				if (structure == dynamic_cast<UnitBuilder*>(const_cast<IUnit*>(structure)))
					displayValidMoveGrid({ (*it)->GetPosition().x, (*it)->GetPosition().y }, CELL_SIZE * 2);
				else
					displayValidMoveGrid({ (*it)->GetPosition().x, (*it)->GetPosition().y }, CELL_SIZE);
				if (distsqr < tolerance) // don't bother to sqrt distsqr, just sqr both sides of the equation for speed
					return true;
			}
		} // iterates through the list to determine deployable position near owned units
	} // measures the distances between the structure and other owned unit 
	else {
		const float distsqr = calculateDistanceSqr({ premovepos.x, premovepos.y }, { 1, 1 }, tx, ty);
		displayValidMoveGrid({ premovepos.x, premovepos.y }, CELL_SIZE);
		if (distsqr < tolerance)
			return true;
	} // measure the distance between the moving structure and its previous coordinate
	
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

	if (selectedunit)
	{
		(*this) << "Player " << (selectedunit->GetColour() == PLAYER_ONE_COLOUR? "1" : "2") << ": " << selectedunit->GetName() << "\n";
		(*this) << "Health: " << selectedunit->GetHealth() << " of " << selectedunit->GetMaxHealth() << "\n";
		(*this) << selectedunit->GetOption() << "\n";
	}
	else
	{
		std::string name = (turn % 2 == 0) ? "2" : "1";
		(*this) << "Player " << name << " to create a move... click a unit to do something with it\n";
		(*this) << "\n0.) Finish turn.\n";
	}
}

void BattleField::onChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{

	if (selectedunit)
	{

		//if (isPlayerTurn((selectedunit->GetColour())))
		//{
		int unitID;
		if (selectedunit->GetFilename() == UNIT_ASSETS[CONSTRUCTION_YARD]) // note that his is checking the memory references to the literal string filename and not the contents
		{
			switch (nChar) {
			case '1': // create an armoury
				unitID = ARMOURY;
				break;
			case '2': // create a defence wall
				unitID = DEFENCE_WALL;
				break;
			case '3': // create a defence turret
				unitID = DEFENCE_TURRET;
				break;
			default:
				MessageBox(getHWND(), L"Select a valid structure.", L"BattleField", MB_ICONERROR);
				break;
			}

			if (((char)nChar - '0' > 0) && ((char)nChar - '0' < 4))
				toplaceunit = dynamic_cast<ConstructionYard*>(selectedunit)->GetUnit(
					UNIT_ASSETS[unitID],
					{ currentcell.x, currentcell.y },
					selectedunit->GetColour(),
					(char)nChar
				);
		}
		else if (selectedunit->GetFilename() == UNIT_ASSETS[ARMOURY])
		{
			switch (nChar) {
				case '1': // create a soldier
					unitID = SOLDIER;
					break;
				case '2': // create a medic
					unitID = MEDIC;
					break;
				case '3': // create a mechanic
					unitID = MECHANIC;
					break;
				case '4': // create a saboteur
					unitID = SABOTEUR;
					break;
				default:
					MessageBox(getHWND(), L"Select a valid infantry.", L"BattleField", MB_ICONERROR);
					break;
			}

			if (((char)nChar - '0' > 0) && ((char)nChar - '0' < 5))
				toplaceunit = dynamic_cast<Armoury*>(selectedunit)->GetUnit(
					UNIT_ASSETS[unitID],
					{ currentcell.x, currentcell.y },
					selectedunit->GetColour(),
					(char)nChar
				);
		}
		//}
		else if (selectedunit == dynamic_cast<Infantry*>(selectedunit)) {
			if (selectedunit->GetPosition().x == currentcell.x && selectedunit->GetPosition().y == currentcell.y) {
				switch (nChar) {
				case '1': {
					// deallocate the unit from its position to move
					isMoved = true;
					toplaceunit = selectedunit;
					playarea[currentcell.x][currentcell.y] = NULL;
					premovepos = { currentcell.x, currentcell.y };
					break;
				}
				default:
					break;
				}
			}
		}
		
		//else
		//{
			// DISPLAY ERROR MESSAGE!!
		//}
	onDraw();
	}
	if (nChar == '0') {
		(*this) << "Do you want to end your turn?\n1.) Yes\n2.)\n";
		if (endTurn((char)nChar)) {

		}
		
	}
}

bool BattleField::endTurn(char choice) {
	return (choice == '1');
}

void BattleField::onLButtonDown(UINT nFlags, int x, int y)
{
	if (toplaceunit)
	{
		if (canPlaceUnit(toplaceunit) && canPlaceStructure(toplaceunit)) {
			if (!isMoved) {
				assert(noofunits < units.max_size());
				units.push_back(toplaceunit);
			} // prevent the moving unit from being pushed to the list
			else {
				dynamic_cast<Infantry*>(toplaceunit)->DepleteMoves(
					sqrt(pow((toplaceunit->GetPosition().x - premovepos.x), 2)
						+ pow((toplaceunit->GetPosition().y - premovepos.y), 2)
					)
				);
				if (toplaceunit == dynamic_cast<Attacker*>(toplaceunit)) {
					fight();
				} // inflict damage to opponent units once they are in the attacker's range
				//if (for healer) { insert code }
			} // deplete the unit's number of moves using the distance formular
			addToPlayArea(toplaceunit);
			toplaceunit = NULL;
			isMoved = false;
		}
		else
			MessageBox(getHWND(), L"Cannot place unit there", L"BattleField", MB_ICONERROR);
	}
	else
	{
		if (currentcell.x>=0 && currentcell.y>=0)
			selectedunit = playarea[currentcell.x][currentcell.y];
	}
	onDraw();
}

void BattleField::onRButtonDown(UINT nFlags, int x, int y)
{
	if (toplaceunit)
	{
		free(toplaceunit);
		toplaceunit = NULL;
	}
	else if (selectedunit)
		selectedunit = NULL;
	else {
		(*this) << "Do you want to end your turn?\n1.) Yes\n2.) No\n";
		endTurn(std::cin.get());
	}
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

const float BattleField::getSpaces(const IUnit* s) {
	if (isMoved)
		// determine maximum amount of moves
		return dynamic_cast<Infantry*>(const_cast<IUnit*>(s))->GetMoves();
	else if (s == dynamic_cast<Infantry*>(const_cast<IUnit*>(s)))
		// place infantry next to armoury
		return 1.0f;
	else
		// place armoury at max. five spaces away from construction yard
		return 5.0f;
}

void BattleField::displayValidMoveGrid(Position p, int cSize)
{
	setPenColour(clGreen, 4);
	selectBackColour(clGreen);

	int is;
	int ie;	

	if (cSize == CELL_SIZE) {
		is = -getSpaces(toplaceunit);
		ie = (selectedunit == dynamic_cast<UnitBuilder*>(selectedunit))
			? getSpaces(toplaceunit) + 1: getSpaces(toplaceunit);
	}
	else {
		is = -getSpaces(toplaceunit) - 1;
		ie = getSpaces(toplaceunit) + 1;
	}

	/*structure[][]
	[0][0] 1. check west 2. check north
	[0][1] 1. check north 2. check east
	[1][0] 1. check west 2. check south
	[1][1] 1. check south 2. check east

	for (int i=0; i < unit->GetSize().width; i++)
	for (int j=0; j < unit->GetSize().height; j++)
	if (playarea[unit->GetPosition().x + i][unit->GetPosition().y + j])

	*/
	for(int i = is; i <= ie; i++)
		for(int j = is; j <= ie; j++)
			drawRectangle((p.x + i) * CELL_SIZE,
				(p.y + j) * CELL_SIZE,
				cSize,
				cSize,
				false
			);
}

const float BattleField::calculateDistanceSqr(Position p, Size s, const float tx, const float ty) {
	const float cx = p.x + (s.width / 2.0f);
	const float cy = p.y + (s.height / 2.0f);
	const float dx = tx - cx;
	const float dy = ty - cy;
	return pow(dx, 2) + pow(dy, 2);
}

void BattleField::fight() {
	std::list<IUnit*>::iterator it;
	for (it = units.begin(); it != units.end(); it++)
	{
		if (dynamic_cast<Attacker*>(toplaceunit)->CanAttack(*it)) {
			//signalAttack(*it);
			if (toplaceunit != dynamic_cast<Saboteur*>(toplaceunit) && *it != dynamic_cast<Structure*>(*it))
				dynamic_cast<Attacker*>(toplaceunit)->Attack(*it);
			else if(toplaceunit == dynamic_cast<Saboteur*>(toplaceunit) && *it != dynamic_cast<Structure*>(*it))
				dynamic_cast<Attacker*>(toplaceunit)->Attack(*it);
			//else if( check if saboteur is on enemy structure to damage ) { insert code }
			if ((*it)->GetHealth() <= 0) {
				eliminateEnemy(*it);
				units.erase(it++);
			} // delete unit if dead
		} // damage infantries and structures
	}
}

void BattleField::eliminateEnemy(IUnit * killedunit) {
	for (int i = 0; i < killedunit->GetSize().width; i++)
		for (int j = 0; j < killedunit->GetSize().height; j++)
			playarea[killedunit->GetPosition().x + i][killedunit->GetPosition().y + j] = NULL;
	delete(killedunit);
}

void BattleField::signalAttack(IUnit * enemy) {
	
	setPenColour(clDarkYellow, 8);
	selectBackColour(clDarkYellow);
	drawRectangle(toplaceunit->GetPosition().x * CELL_SIZE,
		toplaceunit->GetPosition().y * CELL_SIZE,
		CELL_SIZE,
		CELL_SIZE,
		true
	);
	//Sleep(1000);
	drawBlackCross(
		enemy->GetPosition().x,
		enemy->GetPosition().y,
		enemy->GetSize().width,
		enemy->GetSize().height
	);
	//Sleep(1000);
}

const bool BattleField::isPlayerTurn(const IUnit* u)
{
	if ((*player).GetColour() == (*u).GetColour())
		return true;
	return false;
}


const bool BattleField::checkIfGameOver()
{
	std::list<IUnit*>::iterator it;
	it = units.begin();
	if ((*it)->GetHealth() <= 0)
	{
		winner = 1;
		return true;
	}
	else
	{
		it++;
		if ((*it)->GetHealth() <= 0)
		{
			winner = 2;
			return true;
		}
		else
		{
			return false;
		}
	}

}