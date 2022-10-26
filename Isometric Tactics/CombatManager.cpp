#include "CombatManager.h"

IsometricGrid* CombatManager::isoGrid = nullptr;
IsoMap* CombatManager::isoMap = nullptr;


CombatManager::CombatManager(EntityManager& manager) : entityManager(manager)
{
	CombatMovement* combatMove = new CombatMovement(entityManager, *this);
	CombatMenu* combatMenu = new CombatMenu(entityManager, *this);
	std::cout << "state is: neutral" << state << std::endl;
}

void CombatManager::selectGrid()
{
	std::cout << "selecting grid\n";
}

void CombatManager::startCombat(std::string mapID)
{
	isoMap = AssetManager::getIsoMap(mapID);
	std::cout << "combat starts\n";
	Game::setGameState(combat);
	selectGrid();
	isoGrid = new IsometricGrid(isoMap->tileSet, isoMap->mapScale, isoMap->tileSize);
	isoGrid->loadGrid(isoMap->mapPath, isoMap->mapWidth, isoMap->mapHeight);
}

void CombatManager::endCombat()
{
	std::cout << "combat ends\n";
	delete isoGrid;
}

void CombatManager::update()
{
	if (Keyboard_Mouse::keyPressed(SDLK_1))
	{
		state = move;
		std::cout << "state is: move" << state << std::endl;
		std::cout << "current move: " << unitsTurn->getComponent<StatsComponent>().currentMove << std::endl;
	}
	if (Keyboard_Mouse::keyPressed(SDLK_4))
	{
		state = end;
		std::cout << "state is: end" << state << std::endl;
	}

	if (Keyboard_Mouse::rightClick())
	{
		state = neutral;
		std::cout << "state is: neutral" << state << std::endl;
	}


	switch (state)
	{
	case move:
		combatMove->update();
		break;

	case end:
		endTurn();
		break;

	default:
		break;
	}
}




void CombatManager::setUnitsTurn(Entity* setUnitsTurn)
{
	unitsTurn = setUnitsTurn;
	CombatMovement::setUnitsTurn(setUnitsTurn);
}

void CombatManager::endTurn()
{
	std::cout << "turn ended\n";
	unitsTurn->getComponent<StatsComponent>().moveReset();
	//unitsTurn = nextUnit;
	state = neutral;
}