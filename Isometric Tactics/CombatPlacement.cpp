#include "CombatPlacement.h"

int CombatPlacement::placedCount = 0;//because its the index :/
int CombatPlacement::maxParty = 5;//because its compared to a static


CombatPlacement::CombatPlacement()
{}
CombatPlacement::~CombatPlacement()
{}

void CombatPlacement::update()
{
	auto& cpRoster = combatManager->entityManager.getGroup(EntityManager::groupRoster);

	//LOG("in placement");
	//add a way to choose which units to add
	Entity* placingUnit = cpRoster[placedCount];

	placingUnit->getComponent<SpriteComponent>().inBattleTeam = true;
	placingUnit->getComponent<TransformComponent>().moveByGrid(Keyboard_Mouse::getGrid());//add height offset here?

	if (Keyboard_Mouse::leftClick() && canPlaceHere())
	{
		placeUnits();
		LOG("left click + can place");
	}
		
	if (placedCount == maxParty || placedCount == cpRoster.size())
		finishPlacement();

	if (Keyboard_Mouse::rightClick() && placedCount > 0)
	{
		finishPlacement();
		placingUnit->getComponent<SpriteComponent>().inBattleTeam = false;
	}
		
}


bool CombatPlacement::canPlaceHere()
{
	auto& cpTiles = combatManager->entityManager.getGroup(EntityManager::groupTiles);

	for (auto& t : cpTiles)
	{
		Vector2D tGrid = t->getComponent<TileComponent>().getGrid();

		if (t->getComponent<TileComponent>().placeHere && Keyboard_Mouse::hover(tGrid))
		{
			t->getComponent<TileComponent>().blocked = true;
			combatManager->getUnitsTurn()->getComponent<TransformComponent>().tile = t;//need logic condition?
			//need to swap units turn to placing unit??
			return true;
		}
	}
	return false;
}

void CombatPlacement::placeUnits()
{
	auto& cpRoster = combatManager->entityManager.getGroup(EntityManager::groupRoster);

	Entity* placingUnit = cpRoster[placedCount];
	placingUnit->getComponent<SpriteComponent>().inBattleTeam = true;

	placingUnit->getComponent<TransformComponent>().moveByGrid(Keyboard_Mouse::getGrid());
	placedCount++;
}

void CombatPlacement::finishPlacement()
{
	auto& cpRoster = combatManager->entityManager.getGroup(EntityManager::groupRoster);
	auto& cpTiles = combatManager->entityManager.getGroup(EntityManager::groupTiles);

	LOG("placement finished");

	if (placedCount < maxParty && cpRoster.size() < placedCount)
		Entity* placingUnit = cpRoster[placedCount];

	combatManager->state = CombatManager::menu;
	LOG("state is menu");
	placedCount = 0;
	for (auto& t : cpTiles)
	{
		t->getComponent<TileComponent>().placeHere = false;
	}
}