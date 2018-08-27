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
#include "Factory.h"

// the index of each asset must align with the constant used to identify that particular unit, 
// e.g. static const int DEFENCE_TURRET=3; means that the asset for the defence turret must be in index 3
const wchar_t* BattleField::UNIT_ASSETS[NO_OF_UNITS] =
{
	L"artwork\\ConstructionYard.bmp",
	L"artwork\\Armoury.bmp",
	L"artwork\\DefenceWall.bmp",
	L"artwork\\DefenceTurret.bmp",
	L"artwork\\Soldier.bmp",
	L"artwork\\Medic.bmp",
	L"artwork\\Mechanic.bmp",
	L"artwork\\Saboteur.bmp",
	L"artwork\\Truck.bmp",
	L"artwork\\Factory.bmp",
	L"artwork\\Tank.bmp"
};

BattleField::BattleField(HINSTANCE hInstance) : selectedunit(NULL), toplaceunit(NULL), isMoved(false), isToPlace(false)
{
	currentcell = { -1, -1 }; // out of bounds

	// create two initial construction yard structures
	turn = 0;
	noofunits = 2;

	p1 = new Player(L'Player 1', PLAYER_ONE_COLOUR);
	p2 = new Player(L'Player 2', PLAYER_TWO_COLOUR);
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
	create(hInstance, (CELLS_ACROSS*CELL_SIZE) + 16, (CELLS_DOWN*CELL_SIZE) + 8 * CELL_SIZE, 120, true);
}

BattleField::~BattleField()
{
	std::list<IUnit*>::iterator it;
	for (it = units.begin(); it != units.end(); it++) {
		delete *it;
		(*it) = NULL;
	}

	std::list<IUnit*>::iterator unitIT;
	for (unitIT = units.begin(); unitIT != units.end(); unitIT++)
	{
		delete (*unitIT);
	}

	if (p1 != NULL) {
		delete p1;
	}
	if (p2 != NULL) {
		delete p2;
	}
	if (player) {
		player = NULL;
		delete player;
	}
	if (selectedunit) {
		selectedunit = NULL;
		delete selectedunit;
	}
	if (tomoveunit)
	{
		tomoveunit = NULL;
		delete tomoveunit;
	}

	if (toplaceunit) {
		toplaceunit = NULL;
		delete toplaceunit;
	}
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
	if (currentcell.x >= 0 && currentcell.y >= 0)
	{
		setPenColour(clWhite, 2);
		drawRectangle(currentcell.x*CELL_SIZE, currentcell.y*CELL_SIZE, CELL_SIZE, CELL_SIZE, false);
		if (playarea[currentcell.x][currentcell.y]) {
			IUnit *mydetails = playarea[currentcell.x][currentcell.y];
			int colourx;
			if (mydetails->GetColour() == player->GetColour())
				colourx = 3;
			else
				colourx = -3;

			selectBackColour(mydetails->GetColour());
			selectTextColour(clWhite);
			gotoxy((currentcell.x + colourx) * (CELL_SIZE / getPixelsPerColumn()), (currentcell.y + 2) * (CELL_SIZE / getPixelsPerRow()));
			(*this) << "Unit: " << mydetails->GetName();
			gotoxy((currentcell.x + colourx) * (CELL_SIZE / getPixelsPerColumn()), (currentcell.y + 3) * (CELL_SIZE / getPixelsPerRow()));
			(*this) << "HP: " << mydetails->GetHealth() << "/" << mydetails->GetMaxHealth();
			if (mydetails == dynamic_cast<Attacker*>(mydetails)) {
				gotoxy((currentcell.x + colourx) * (CELL_SIZE / getPixelsPerColumn()), (currentcell.y + 4) * (CELL_SIZE / getPixelsPerRow()));
				(*this) << "Rank: " << dynamic_cast<Attacker*>(mydetails)->GetRank();
				gotoxy((currentcell.x + colourx) * (CELL_SIZE / getPixelsPerColumn()), (currentcell.y + 5) * (CELL_SIZE / getPixelsPerRow()));
				(*this) << "Kills: " << dynamic_cast<Attacker*>(mydetails)->GetKills();
			}
		}
	}

	if (selectedunit && selectedunit == dynamic_cast<Infantry*>(selectedunit))
	{
		int dx = selectedunit->GetPosition().x - currentcell.x;
		int dy = selectedunit->GetPosition().y - currentcell.y;

		bool valid = true;
		if (dx == 0 && dy == 0)
			valid = false;
		else
			valid = true;

		if (!valid)
			drawRedCross(currentcell.x, currentcell.y, selectedunit->GetSize().width, selectedunit->GetSize().height);
	}

	// draw the toplaceunit if there is one and the location is valid
	if (toplaceunit && currentcell.x != -1 && currentcell.x + toplaceunit->GetSize().width <= CELLS_ACROSS && currentcell.y + toplaceunit->GetSize().height <= CELLS_DOWN)
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
	}

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
			if (isDistanceValid(*it, structure))
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
	const int x = unit->GetPosition().x*CELL_SIZE;
	const int y = unit->GetPosition().y*CELL_SIZE;
	const int width = unit->GetSize().width*CELL_SIZE;
	const int height = unit->GetSize().height*CELL_SIZE;
	if (unit == selectedunit)
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
	gotoxy(0, 1 + (CELLS_DOWN*CELL_SIZE) / getPixelsPerRow());
	selectTextColour(clWhite);
	selectBackColour(clBlack);

	if (selectedunit) {
		(*this) << "Player " << (selectedunit->GetColour() == PLAYER_ONE_COLOUR ? "1" : "2") << ": " << selectedunit->GetName() << "\n";
		(*this) << "Health: " << selectedunit->GetHealth() << " of " << selectedunit->GetMaxHealth() << "\n";
		if (isPlayerTurn(selectedunit))	(*this) << selectedunit->GetOption() << "\n";
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
					if (selectedunit->GetFilename() == UNIT_ASSETS[CONSTRUCTION_YARD])
						createStructure(nChar);
					else if (selectedunit->GetFilename() == UNIT_ASSETS[ARMOURY])
						createInfantry(nChar);
					else if (selectedunit->GetFilename() == UNIT_ASSETS[FACTORY])
						createVehicle(nChar);
					else if (selectedunit == dynamic_cast<Infantry*>(selectedunit) || selectedunit == dynamic_cast<Vehicle*>(selectedunit))
						moveUnit(nChar);
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
}

void BattleField::changePlayer()
{
	endTurn();

	// RESET UNITS BUILT IN ARMOURY
	turn = turn % 2;
	if (turn == 0) player = p1;
	else player = p2;

	startTurn();
}

const bool BattleField::isPlayerTurn(const IUnit* u)
{
	return (player->GetColour() == u->GetColour());
}

void BattleField::startTurn() {
	std::list<IUnit*>::iterator it;
	for (it = units.begin(); it != units.end(); it++) {
		(*it)->RestoreActions();
		if (*it == dynamic_cast<Mechanic*>(*it) || *it == dynamic_cast<Saboteur*>(*it)) {
			drawUnit(*it);
			addToPlayArea(*it);
			onDraw();
		}
	}
}

void BattleField::endTurn() {
	std::list<IUnit*>::iterator it;
	for (it = units.begin(); it != units.end(); it++) {
		if (*it == dynamic_cast<Mechanic*>(*it) || *it == dynamic_cast<Saboteur*>(*it))
			checkUnitOnStructure(*it);
		if (*it == dynamic_cast<Attacker*>(*it))
			fight(*it); // inflict damage to opponent units once they are in the attacker's range
		if (*it == dynamic_cast<Healer*>(*it))
			heal(*it);
	}
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
				getDistanceDifference({ premovepos.x, premovepos.y }, toplaceunit->GetPosition()));
				//dynamic_cast<Infantry*>(toplaceunit).CheckPosition()
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
		if (currentcell.x >= 0 && currentcell.y >= 0)
			selectedunit = playarea[currentcell.x][currentcell.y];
	}
	onDraw();
}

void BattleField::onRButtonDown(UINT nFlags, int x, int y)
{
	if (toplaceunit)
	{
		if (isMoved)  {
			toplaceunit->SetPosition({ premovepos.x, premovepos.y });
			drawUnit(toplaceunit);
			addToPlayArea(toplaceunit);
			isMoved = false;
		} // return unit to previous position
		toplaceunit = NULL;
		free(toplaceunit);
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
	x /= CELL_SIZE;
	y /= CELL_SIZE;
	if (x >= 0 && x<CELLS_ACROSS && y >= 0 && y<CELLS_DOWN)
		currentcell = { x, y };
	else
		currentcell = { -1, -1 };

	// redraw the screen to refresh highlight
	onDraw();
}

void BattleField::updatePlayArea()
{
	// Reset the play area
	for (int i = 0; i<CELLS_ACROSS; i++)
		for (int j = 0; j<CELLS_DOWN; j++)
			playarea[i][j] = NULL;

	// Put the units onto the play area - using memory references to make it easier to manipulate the unit
	std::list<IUnit*>::iterator it;
	for (it = units.begin(); it != units.end(); it++)
		addToPlayArea(*it);
}

void BattleField::checkRange() {
	int posEnd, negEnd, unitx, unity;

	if (toplaceunit == dynamic_cast<UnitBuilder*>(toplaceunit) || toplaceunit == dynamic_cast<Vehicle*>(toplaceunit)) {
		posEnd = (int) getSpaces(toplaceunit) + 1;
		negEnd = (int) -getSpaces(toplaceunit) - 1;
	}
	else {
		posEnd = (int) getSpaces(toplaceunit);
		negEnd = (int) -getSpaces(toplaceunit);
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

void BattleField::findRange(const IUnit * c, Position p, const int & pEnd, const int & nEnd, const int & ux, const int & uy) {
	int i = 0, j = 0;

	for (int ax = 0; ax >= nEnd; ax--)
		for (int ay = 0; ay >= nEnd; ay--)
			if (!playarea[ux + ax][uy + ay])
				generateRangeGrid(c, p, ax, ay);

	if (c == dynamic_cast<UnitBuilder*>(const_cast<IUnit*>(c)) || c == dynamic_cast<Vehicle*>(const_cast<IUnit*>(c))) {
		i++;
		p = updatePosition(const_cast<IUnit*>(c), i, j);
	}

	for (int bx = 0; bx <= pEnd; bx++)
		for (int by = 0; by >= nEnd; by--)
			if (!playarea[ux + i + bx][uy + by])
				generateRangeGrid(c, p, bx, by);

	if (c == dynamic_cast<UnitBuilder*>(const_cast<IUnit*>(c)) || c == dynamic_cast<Vehicle*>(const_cast<IUnit*>(c))) {
		i--;
		j++;
		p = updatePosition(const_cast<IUnit*>(c), i, j);
	}

	for (int cx = 0; cx >= nEnd; cx--)
		for (int cy = 0; cy <= pEnd; cy++)
			if (!playarea[ux + cx][uy + j + cy])
				generateRangeGrid(c, p, cx, cy);

	if (c == dynamic_cast<UnitBuilder*>(const_cast<IUnit*>(c)) || c == dynamic_cast<Vehicle*>(const_cast<IUnit*>(c))) {
		i++;
		p = updatePosition(const_cast<IUnit*>(c), i, j);
	}

	for (int dx = 0; dx <= pEnd; dx++)
		for (int dy = 0; dy <= pEnd; dy++)
			if (!playarea[ux + i + dx][uy + j + dy])
				generateRangeGrid(c, p, dx, dy);
}

void BattleField::generateRangeGrid(const IUnit * c, const Position & p, const int & i, const int & j) {
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
	const float tolerance = (getSpaces(c) + c->GetSize().width) * (getSpaces(c) + c->GetSize().width);

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

void BattleField::heal(IUnit * c) {
	std::list<IUnit*>::iterator it;
	for (it = units.begin(); it != units.end(); it++)
	{
		if ((dynamic_cast<Healer*>(c)->CanHeal(*it)) && (dynamic_cast<Healer*>(c) != dynamic_cast<Healer*>(*it)))
			dynamic_cast<Healer*>(c)->Heal(*it);
	}
}

void BattleField::fight(IUnit * c) {
	if (!dynamic_cast<Attacker*>(c)->CanAttack()) {
		IUnit *targetEnemy = *units.begin();
		std::list<IUnit*>::iterator it;
		for (it = units.begin(); it != units.end(); it++) {
			if (dynamic_cast<Attacker*>(c)->DetermineWeakestEnemy(*it)) {
				if ((targetEnemy->GetHealth()) >= ((*it)->GetHealth())) {
					targetEnemy = (*it);
				}
			}
		}
		if ((getDistanceDifference(c->GetPosition(), targetEnemy->GetPosition())) > (dynamic_cast<Attacker*>(c)->GetRange())) {
			targetEnemy = NULL;
			free(targetEnemy);
		} // release first element if not in range to prevent damage through own units
		else {
			if (c != dynamic_cast<Saboteur*>(c))
				dynamic_cast<Attacker*>(c)->Attack(targetEnemy);
			else if (c == dynamic_cast<Saboteur*>(c) && targetEnemy != dynamic_cast<Structure*>(targetEnemy))
				dynamic_cast<Attacker*>(c)->Attack(targetEnemy);
			else if (dynamic_cast<Saboteur*>(c)->CanAttackStruc(targetEnemy) && targetEnemy == dynamic_cast<Structure*>(targetEnemy))
				dynamic_cast<Saboteur*>(c)->Attack(targetEnemy);

			if (targetEnemy->GetHealth() <= 0) {
				player->AddWarTrophy(targetEnemy->GetCost());
				eliminateEnemy(targetEnemy);
				units.remove(targetEnemy);
			} // delete unit if dead
		}
		targetEnemy = NULL;
		free(targetEnemy);
	}	
} // damage infantries and structures

const bool BattleField::checkIfGameOver()
{
	std::list<IUnit*>::iterator it;
	for (it = units.begin(); it != units.end(); it++) {
		if ((*it) == dynamic_cast<ConstructionYard*>(*it))
		{
			if ((*it)->GetColour() == p1->GetColour() && (*it)->GetHealth() <= 0)
				winner = 1;
			else if ((*it)->GetColour() == p2->GetColour() && (*it)->GetHealth() <= 0)
				winner = 2;

			if(winner == 1 || winner == 2) return true;
		}
	}
	return false;
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
	case '4': // create a factory
		unitID = FACTORY;
		break;
	default:
		MessageBox(getHWND(), L"Select a valid structure.", L"BattleField", MB_ICONERROR);
		break;
	}
	bool setupStage = false;

	if (((char)nChar - '0' > 0) && ((char)nChar - '0' < 5) && !dynamic_cast<UnitBuilder*>(selectedunit)->CanPlaceUnit()) {
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

void BattleField::createVehicle(UINT nChar) {
	switch (nChar) {
	case '1': // create a wathog
		unitID = WARTHOG;
		break;
	case '2': // create a tank
		unitID = TANK;
		break;
	default:
		MessageBox(getHWND(), L"Select a valid infantry.", L"BattleField", MB_ICONERROR);
		break;
	}

	if (((char)nChar - '0' > 0) && ((char)nChar - '0' < 3) && !dynamic_cast<UnitBuilder*>(selectedunit)->CanPlaceUnit()) {
		toplaceunit = dynamic_cast<Factory*>(selectedunit)->GetUnit(
			UNIT_ASSETS[unitID],
			{ currentcell.x, currentcell.y },
			selectedunit->GetColour(),
			(char)nChar
		);
		checkBalance();
	}
}

void BattleField::moveUnit(UINT nChar) {
	if (!isMoved && nChar == '1' && selectedunit->GetPosition().x == currentcell.x && selectedunit->GetPosition().y == currentcell.y) {
		// deallocate the unit from its position to move
		isMoved = true;
		isToPlace = true;
		dynamic_cast<Infantry*>(selectedunit)->Move();
		toplaceunit = selectedunit;
		playarea[currentcell.x][currentcell.y] = NULL;
		premovepos = { currentcell.x, currentcell.y };
	}
}