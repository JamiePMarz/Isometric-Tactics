#include "CombatManager.h"

IsometricGrid* CombatManager::isoGrid = nullptr;
IsoMap* CombatManager::isoMap = nullptr;
CombatManager::combatState CombatManager::state;


CombatManager::CombatManager(EntityManager& manager) : entityManager(manager)
{
	CombatMovement* combatMove = new CombatMovement(entityManager, *this);
	CombatMenu* combatMenu = new CombatMenu(entityManager, *this);
	CombatPlacement* combatPlacement = new CombatPlacement(entityManager, *this);

}

void CombatManager::startCombat(std::string mapID)
{	
	isoMap = AssetManager::getIsoMap(mapID);
	std::cout << "combat starts\n";
	Game::setGameState(combat);
	isoGrid = new IsometricGrid(isoMap->tileSet, isoMap->mapScale, isoMap->tileSize);//cant i just update it?
	isoGrid->loadGrid(isoMap->mapPath);
	delete isoGrid;

	CombatPlacement::finPlace = false;
	state = placement;
}



void CombatManager::endCombat()
{
	std::cout << "combat ends\n";
	auto& tiles(entityManager.getGroup(Game::groupTiles));
	auto& roster(entityManager.getGroup(Game::groupRoster));

	for (auto& entity : roster)
	{
		entity->getComponent<SpriteComponent>().inBattleTeam = false;
	}

	for (auto& entity : tiles)
	{
		entity->setActive(false);	//leaks
	}
}

void CombatManager::update()
{
	if (Keyboard_Mouse::rightClick() && CombatPlacement::finPlace)
	{
		state = CombatManager::combatState::menu;
		//std::cout << "state is menu" << std::endl;
	}

	switch (state)
	{
	case placement:
		combatPlacement->update();
		break;

	case menu:
		combatMenu->update();
		break;

	case move:
		combatMove->update();
		break;

	case attack:

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
	//next unit func
	state = menu;
}