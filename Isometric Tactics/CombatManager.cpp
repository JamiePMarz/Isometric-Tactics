#include "CombatManager.h"

IsometricGrid* CombatManager::isoGrid = nullptr;
IsoMap* CombatManager::isoMap = nullptr;
CombatManager::combatState CombatManager::state = neutral;


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
		combatMove->showMoveRange();

	}
	if (Keyboard_Mouse::keyPressed(SDLK_2))
	{
		state = attack;
		std::cout << "state is: attack" << state << std::endl;
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

	case attack:
		//
		//for (auto& enemey : entityManager.getGroups(groupEnemies))
		// {
		//		if (abs(unitsTurn->getComponent<TransformComponent>().gridPos - enemey->getComponent<TransformComponent>().gridPos) 
		//			<= unitsTurn.getComponent<StatsComponent>().range)
		//		{
		//			//target is in range to do stuff
		//		}
		// 
		// }
		//find targets in range and leftclicked bool
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