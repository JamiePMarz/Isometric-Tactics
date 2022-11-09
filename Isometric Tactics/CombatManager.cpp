#include "CombatManager.h"

IsometricGrid* CombatManager::isoGrid = nullptr;
IsoMap* CombatManager::isoMap = nullptr;
CombatManager::combatState CombatManager::state;//tile.cpp in use


CombatManager::CombatManager(EntityManager& eManager) : entityManager(eManager)
{}

void CombatManager::startCombat(std::string mapID)
{	
	LOG("combat starts");
	isoMap = AssetManager::getIsoMap(mapID);
	LOG("loading " << mapID << std::endl);
	LOG("setting grid details");
	IsometricGrid isoGrid(isoMap->tileSet, isoMap->mapScale, isoMap->tileSize);
	isoGrid.loadGrid(isoMap->mapPath);//could get map details straigth from isoMap->xyz

	state = placement;
}



void CombatManager::endCombat()
{
	LOG("combat ends");
	auto& tiles(entityManager.getGroup(EntityManager::groupTiles));
	auto& roster(entityManager.getGroup(EntityManager::groupRoster));

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
	if (Keyboard_Mouse::rightClick() && state != placement)
	{
		state = menu;
		//LOG("state is menu\n");
	}


	if (state != end)
		combatComponents[state]->update();
	else 
		endTurn();
}

void CombatManager::setUnitsTurn(Entity* newUnit)
{
	unitsTurn = newUnit;
}

void CombatManager::endTurn()
{
	LOG("turn ending\n");
	unitsTurn->getComponent<StatsComponent>().moveReset();
	//setUnitsTurn(unitsTurn);//placeholder
	state = menu;
}