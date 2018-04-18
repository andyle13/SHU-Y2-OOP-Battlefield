#include "BattleField.h"
#include "Player.h"
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

BattleField::BattleField(HINSTANCE hInstance) : selectedunit(NULL), toplaceunit(NULL), isMoved(false), isToPlace(false)
{
	currentcell = {-1, -1}; // out of bounds

	// create two initial construction yard structures - I am using colour to determine which unit belongs to which player... a little bit of a fudge
	turn = 0;
	noofunits = 2;
	int thisx, thisy;
	
	p1 = new Player(L'Player 1', PLAYER_ONE_COLOUR);
	p2 = new Player(L'Player 2', PLAYER_TWO_COLOUR);
	player = p1;

	units.push_back(
		new ConstructionYard(
			UNIT_ASSETS[CONSTRUCTION_YARD],
			{ 17, (CELLS_DOWN - 2) / 2 },
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

	if (isToPlace) checkRange();

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
		else
			valid = true;
    
		if (!valid)
			drawRedCross(currentcell.x, currentcell.y, selectedunit->GetSize().width, selectedunit->GetSize().height);
	}

	// draw the toplaceunit if there is one and the location is valid
	if (toplaceunit && currentcell.x != -1 && currentcell.x+toplaceunit->GetSize().width <= CELLS_ACROSS && currentcell.y+toplaceunit->GetSize().height <= CELLS_DOWN)
	{
		toplaceunit->SetPosition({ currentcell.x, currentcell.y });
		drawUnit(toplaceunit);

		if (dynamic_cast<Medic*>(toplaceunit))
			unitType = 1;
		else if (dynamic_cast<Mechanic*>(toplaceunit))
			unitType = 2;
		else if (dynamic_cast<Saboteur*>(toplaceunit))
			unitType = 3;
		else
			unitType = 0;

		// check to see if the unit can be placed here (i.e the play area is free)
		if (!canMoveUnit(toplaceunit))
		{
			drawRedCross(toplaceunit->GetPosition().x,
				toplaceunit->GetPosition().y,
				toplaceunit->GetSize().width,
				toplaceunit->GetSize().height
			);

			if ((unitType == 1) || (unitType == 2) || (unitType == 3))
				updatePlayArea();
		}
		else // check if location rules are valid
		{
			if ((!canPlaceStructure(toplaceunit)) || (playarea[currentcell.x][currentcell.y] != dynamic_cast<Structure*>(playarea[currentcell.x][currentcell.y])))
			{
				// draw a white cross through the unit to indicate it cannot be placed here
				drawRedCross(toplaceunit->GetPosition().x,
					toplaceunit->GetPosition().y,
					toplaceunit->GetSize().width,
					toplaceunit->GetSize().height
				);
				if ((unitType == 1) || (unitType == 2) || (unitType == 3))
					updatePlayArea();
			}
		}
	}

	drawStatus();

	// immediate graphics draw has been disabled so we need to call the onDraw method in the EasyGraphics base-class to flush the updates to the screen
	EasyGraphics::onDraw();
}

bool BattleField::canMoveUnit(const IUnit* unit)
{
	for (int i = 0; i < unit->GetSize().width; i++)
	{
		for (int j = 0; j < unit->GetSize().height; j++)
			if (playarea[unit->GetPosition().x + i][unit->GetPosition().y + j])
				if (unitType == 0)
					return false;
				else
				{
					if (unitType == 1)
					{
						if ((playarea[currentcell.x][currentcell.y] != dynamic_cast<Infantry*>(playarea[currentcell.x][currentcell.y])) || (!(isPlayerTurn(playarea[currentcell.x][currentcell.y]))))
							return false;
					}
					else if (unitType == 2)
					{
						if ((playarea[currentcell.x][currentcell.y] != dynamic_cast<Structure*>(playarea[currentcell.x][currentcell.y])) || (!(isPlayerTurn(playarea[currentcell.x][currentcell.y]))))
							return false;
					}
					else if (unitType == 3)
					{
						if ((playarea[currentcell.x][currentcell.y] != dynamic_cast<Structure*>(playarea[currentcell.x][currentcell.y])) || ((isPlayerTurn(playarea[currentcell.x][currentcell.y]))))
							return false;
					}
					else
					{
						return false;
					}
				}
	}/*
	if ((unitType == 1) || (unitType == 2) || (unitType == 3))
		updatePlayArea();*/
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
			if(isDistanceValid(*it, structure))
			{
				const float distsqr = calculateDistanceSqr((*it)->GetPosition(), (*it)->GetSize(), tx, ty);
				if (distsqr < tolerance) // don't bother to sqrt distsqr, just sqr both sides of the equation for speed
					return true;
			} // check by player colour || check if the new unit is an armoury || check if toplaceunit is an infantry
		} // iterates through the list to determine deployable position near owned units
	} // measures the distances between the structure and other owned unit 
	else {
		const float distsqr = calculateDistanceSqr({ premovepos.x, premovepos.y }, { 1, 1 }, tx, ty);
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
		std::string name = (turn % 2 == 0) ? "1" : "2";
		(*this) << "Player " << name << " | Balance: " << player->GetBalance() << " GBP\n";
		(*this) << "Player " << name << " to create a move... click a unit to do something with it\n";
		(*this) << "\n0.) Finish turn.\n";
	}
}

void BattleField::onChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!checkIfGameOver())
	{
		if (nChar == '0')
		{
			++turn;
			changePlayer();
		}
		else
			if (selectedunit)
				if (isPlayerTurn(selectedunit))
				{
					int unitID;
					if (selectedunit->GetFilename() == UNIT_ASSETS[CONSTRUCTION_YARD])
						createStructure(nChar);
					else if (selectedunit->GetFilename() == UNIT_ASSETS[ARMOURY])
						createInfantry(nChar);
					else if (selectedunit == dynamic_cast<Infantry*>(selectedunit))
						moveInfantry(nChar);
				}
		onDraw();
	}
	else
	{
		if (winner == 1)
			MessageBox(getHWND(), L"Winner: " + player->GetName(), L"BattleField", MB_ICONERROR);
		else if (winner == 2)
			MessageBox(getHWND(), L"Winner: " + player->GetName(), L"BattleField", MB_ICONERROR);
	}
	/*if (nChar == '0') {
		(*this) << "Do you want to end your turn?\n1.) Yes\n2.)\n";
		if (endTurn((char)nChar)) {

		}
	}*/
}

void BattleField::changePlayer()
{
	// RESET UNITS BUILT IN ARMOURY
	turn = turn % 2;
	if (turn == 0) player = p1;
	else player = p2;

	startTurn();
}

const bool BattleField::isPlayerTurn(const IUnit* u)
{
	return ((*player).GetColour() == (*u).GetColour());
}

void BattleField::startTurn() {
	std::list<IUnit*>::iterator it;
	for (it = units.begin(); it != units.end(); it++)
	{
		(*it)->RestoreActions();

		if ((*it) == dynamic_cast<Infantry*>(*it))
			if ((dynamic_cast<Infantry*>(*it))->UnitOnStructure(*it))
				if (((*it) == dynamic_cast<Mechanic*>(*it)) || ((*it) == dynamic_cast<Saboteur*>(*it)))
				{
					(*it)->SetPosition(dynamic_cast<Infantry*>(*it)->GetOldPosition());
					drawUnit(*it);
					addToPlayArea(*it);
					onDraw();
				}
	}
}

void BattleField::endTurn() {
	if (toplaceunit == dynamic_cast<Attacker*>(toplaceunit))
		fight(); // inflict damage to opponent units once they are in the attacker's range
	if (toplaceunit == dynamic_cast<Healer*>(toplaceunit))
		heal();
}



void BattleField::onLButtonDown(UINT nFlags, int x, int y)
{
	if (toplaceunit)
	{
		if (dynamic_cast<Medic*>(toplaceunit))
			unitType = 1;
		else if (dynamic_cast<Mechanic*>(toplaceunit))
			unitType = 2;
		else if (dynamic_cast<Saboteur*>(toplaceunit))
			unitType = 3;
		else
			unitType = 0;

		if (canMoveUnit(toplaceunit) && canPlaceStructure(toplaceunit)) {

			if ((unitType == 1) || (unitType == 2) || (unitType == 3))
				updatePlayArea();

			if (!isMoved) {
				assert(noofunits < units.max_size());
				dynamic_cast<UnitBuilder*>(selectedunit)->UnitPlaced();
				units.push_back(toplaceunit);
			} // prevent the moving unit from being pushed to the list
			else {
				isMoved = false;
				dynamic_cast<Infantry*>(toplaceunit)->DepleteMoves(
					sqrt(pow((toplaceunit->GetPosition().x - premovepos.x), 2)
						+ pow((toplaceunit->GetPosition().y - premovepos.y), 2)
					)
				);
			} // deplete the unit's number of moves using the distance formular
			addToPlayArea(toplaceunit);
			toplaceunit = NULL;
			isToPlace = false;
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
		if (!isMoved)
			free(toplaceunit);
		else {
			toplaceunit->SetPosition({ premovepos.x, premovepos.y });
			drawUnit(toplaceunit);
			addToPlayArea(toplaceunit);
			isMoved = false;
		} // return unit to previous position
		toplaceunit = NULL;
	}
	else if (selectedunit) {
		selectedunit = NULL;
	}
	else {
		(*this) << "Do you want to end your turn?\n1.) Yes\n2.) No\n";
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

void BattleField::checkRange() {
	int posEnd, negEnd, unitx, unity;

	if (toplaceunit == dynamic_cast<UnitBuilder*>(toplaceunit)) {
		posEnd = getSpaces(toplaceunit) + 1;
		negEnd = -getSpaces(toplaceunit) - 1;
	}
	else {
		posEnd = getSpaces(toplaceunit);
		negEnd = -getSpaces(toplaceunit);
	}
	if (!isMoved) {
		std::list<IUnit*>::iterator it;
		for (it = units.begin(); it != units.end(); it++)
		{
			unitx = (*it)->GetPosition().x;
			unity = (*it)->GetPosition().y;
			findRange(*it, { unitx, unity }, posEnd, negEnd, unitx, unity);
		}
	}
	else {
		unitx = premovepos.x;
		unity = premovepos.y;
		findRange(selectedunit, { unitx, unity }, posEnd, negEnd, unitx, unity);
	}
}

void BattleField::findRange(IUnit * c, Position p, int pEnd, int nEnd, int ux, int uy) {
	int i = 0, j = 0;

	for (int ax = 0; ax >= nEnd; ax--)
		for (int ay = 0; ay >= nEnd; ay--)
			if (!playarea[ux + ax][uy + ay])
				generateRangeGrid(c, p, ax, ay);

	if (c == dynamic_cast<UnitBuilder*>(c)) {
		i++;
		p = updatePosition(c, i, j);
	}

	for (int bx = 0; bx <= pEnd; bx++)
		for (int by = 0; by >= nEnd; by--)
			if (!playarea[ux + i + bx][uy + by])
				generateRangeGrid(c, p, bx, by);

	if (c == dynamic_cast<UnitBuilder*>(c)) {
		i--;
		j++;
		p = updatePosition(c, i, j);
	}

	for (int cx = 0; cx >= nEnd; cx--)
		for (int cy = 0; cy <= pEnd; cy++)
			if (!playarea[ux + cx][uy + j + cy])
				generateRangeGrid(c, p, cx, cy);

	if (c == dynamic_cast<UnitBuilder*>(c)) {
		i++;
		p = updatePosition(c, i, j);
	}

	for (int dx = 0; dx <= pEnd; dx++)
		for (int dy = 0; dy <= pEnd; dy++)
			if (!playarea[ux + i + dx][uy + j + dy])
				generateRangeGrid(c, p, dx, dy);
}

void BattleField::generateRangeGrid(IUnit * c, Position p, int i, int j) {
	int ux, uy;
	if (!isMoved) {
		ux = c->GetPosition().x;
		uy = c->GetPosition().y;
	}
	else {
		ux = premovepos.x;
		uy = premovepos.y;
	}

	// use centre locations and calculate the tolerance allowed based on width and allowed spaces
	const float tx = ux + (c->GetSize().width / 2.0f);
	const float ty = uy + (c->GetSize().height / 2.0f);
	const float tolerance = pow((getSpaces(c) + c->GetSize().width), 2);

	if (isDistanceValid(c, toplaceunit) || isMoved) {
		const float distsqr = calculateDistanceSqr({ p.x + i, p.y + j }, { 1,1 }, tx, ty);
		if (distsqr < tolerance) {
			setPenColour(clGreen, 4);
			selectBackColour(clGreen);
			drawRectangle((p.x + i) * CELL_SIZE,
				(p.y + j) * CELL_SIZE,
				CELL_SIZE,
				CELL_SIZE,
				false
			);
		} // draw squares
	}
}

const float BattleField::calculateDistanceSqr(Position p, Size s, const float tx, const float ty) {
	const float cx = p.x + (s.width / 2.0f);
	const float cy = p.y + (s.height / 2.0f);
	const float dx = tx - cx;
	const float dy = ty - cy;
	return pow(dx, 2) + pow(dy, 2);
}

void BattleField::heal() {
	std::list<IUnit*>::iterator it;
	for (it = units.begin(); it != units.end(); it++)
	{
		if ((dynamic_cast<Healer*>(toplaceunit)->CanHeal(*it)) && (dynamic_cast<Healer*>(toplaceunit) != dynamic_cast<Healer*>(*it)))
		{
			dynamic_cast<Healer*>(toplaceunit)->Heal(*it);
		}
	}
}

void BattleField::fight() {
	if (!dynamic_cast<Attacker*>(toplaceunit)->CanAttack()) {
		IUnit *targetEnemy;

		//if (dynamic_cast<Saboteur*>(toplaceunit)->CanAttackStruc(*it) && (*it) == dynamic_cast<Structure*>(*it)) {
			targetEnemy = *units.begin();
			std::list<IUnit*>::iterator it;
			for (it = units.begin(); it != units.end(); it++)
			{
				if (dynamic_cast<Attacker*>(toplaceunit)->DetermineWeakestEnemy(*it))
					if (targetEnemy->GetHealth() > (*it)->GetHealth())
						targetEnemy = *it;
			}
			if (toplaceunit != dynamic_cast<Saboteur*>(toplaceunit) && targetEnemy != dynamic_cast<Structure*>(targetEnemy))
				dynamic_cast<Attacker*>(toplaceunit)->Attack(targetEnemy);
			else if (toplaceunit == dynamic_cast<Saboteur*>(toplaceunit) && targetEnemy != dynamic_cast<Structure*>(targetEnemy))
				dynamic_cast<Attacker*>(toplaceunit)->Attack(targetEnemy);
		/*}
		else {
			//targetEnemy = enemy structure;
			dynamic_cast<Saboteur*>(toplaceunit)->Attack(targetEnemy);
		} // damage enemy structure with saboteur
		*/
		if (targetEnemy->GetHealth() <= 0) {
			eliminateEnemy(targetEnemy);
			units.remove(targetEnemy);
		} // delete unit if dead
	}
} // damage infantries and structures

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

const bool BattleField::isDistanceValid(IUnit* source, const IUnit* destination) {
	if(destination != nullptr)
		if (// check if unit belongs to player
			source->GetColour() == destination->GetColour() &&
			// check if the structure placed is an armoury and other units are structures
			(destination == dynamic_cast<Armoury*>(const_cast<IUnit*>(destination)) && source == dynamic_cast<UnitBuilder*>(source) ||
			// check if the unit placed is an infantry and other units are armouries
			(destination == dynamic_cast<Infantry*>(const_cast<IUnit*>(destination)) && source == dynamic_cast<Armoury*>(source))))
			return true;
	return false;
}

Position BattleField::updatePosition(IUnit * c, int i, int j) {
	return { c->GetPosition().x + i, c->GetPosition().y + j };
}

void BattleField::createStructure(UINT nChar) {
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
	bool setupStage = false;

	if (((char)nChar - '0' > 0) && ((char)nChar - '0' < 4) && !dynamic_cast<UnitBuilder*>(selectedunit)->CanPlaceUnit()) {
		toplaceunit = dynamic_cast<ConstructionYard*>(selectedunit)->GetUnit(
			UNIT_ASSETS[unitID],
			{ currentcell.x, currentcell.y },
			selectedunit->GetColour(),
			(char)nChar
		);
		checkBalance();
	}
}

void BattleField::createInfantry(UINT nChar) {
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

	if (((char)nChar - '0' > 0) && ((char)nChar - '0' < 5) && !dynamic_cast<UnitBuilder*>(selectedunit)->CanPlaceUnit()) {
		toplaceunit = dynamic_cast<Armoury*>(selectedunit)->GetUnit(
			UNIT_ASSETS[unitID],
			{ currentcell.x, currentcell.y },
			selectedunit->GetColour(),
			(char)nChar
		);
		checkBalance();
	}
}

void BattleField::moveInfantry(UINT nChar) {
	if (!isMoved && nChar == '1') {
		// deallocate the unit from its position to move
		isMoved = true;
		isToPlace = true;
		toplaceunit = selectedunit;
		playarea[currentcell.x][currentcell.y] = NULL;
		premovepos = { currentcell.x, currentcell.y };
	}
}

void BattleField::checkBalance() {
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