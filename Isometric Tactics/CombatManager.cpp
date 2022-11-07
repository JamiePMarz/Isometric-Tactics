#include "CombatManager.h"

IsometricGrid* CombatManager::isoGrid = nullptr;
IsoMap* CombatManager::isoMap = nullptr;
CombatManager::combatState CombatManager::state;


CombatManager::CombatManager(EntityManager& eManager) : entityManager(eManager)
{
	CombatMovement* combatMove = new CombatMovement(entityManager, *this);
	CombatMenu* combatMenu = new CombatMenu(entityManager, *this);
	CombatPlacement* combatPlacement = new CombatPlacement(entityManager, *this);

}

void CombatManager::startCombat(std::string mapID)
{	
	LOG("combat starts\n");
	isoMap = AssetManager::getIsoMap(mapID);
	LOG("loading " << mapID << std::endl);
	Game::setGameState(combat);
	LOG("setting grid details\n");
	IsometricGrid isoGrid(isoMap->tileSet, isoMap->mapScale, isoMap->tileSize);
	isoGrid.loadGrid(isoMap->mapPath);//could get map details straigth from isoMap->xyz

	CombatPlacement::finPlace = false;
	state = placement;
}



void CombatManager::endCombat()
{
	LOG("combat ends\n");
	auto& tiles(entityManager.getGroup(Game::groupTiles));
	auto& roster(entityManager.getGroup(Game::groupRoster));

	for (auto& entity : roster)
	{
		entity->getComponent<SpriteComponent>().inBattleTeam = false;
	}

	for (auto& entity : tiles)
	{
		entity->setActive(false);
	}
}

void CombatManager::update()
{
	if (Keyboard_Mouse::rightClick() && CombatPlacement::finPlace)
	{
		state = CombatManager::combatState::menu;
		//LOG("state is menu\n");
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

	/*case test:
		combatTest->update();
		break;*/

	case end:
		endTurn();
		break;

	default:
		break;
	}
}




void CombatManager::setUnitsTurn(Entity* newUnit)
{
	unitsTurn = newUnit;
	CombatMovement::setUnitsTurn(newUnit);
}

void CombatManager::endTurn()
{
	LOG("turn ended\n");
	unitsTurn->getComponent<StatsComponent>().moveReset();
	//select next unit here
	state = menu;
}