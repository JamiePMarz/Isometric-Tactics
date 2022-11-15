#include "CombatPlacement.h"

int CombatPlacement::placedCount = 0;//because its the index :/
int CombatPlacement::maxParty = 5;//because its compared to a static


CombatPlacement::CombatPlacement()
{}
CombatPlacement::~CombatPlacement()
{}

void CombatPlacement::update()
{
	auto& groupRoster = combatManager->entityManager.getGroup(EntityManager::groupRoster);
	auto& groupTiles = combatManager->entityManager.getGroup(EntityManager::groupTiles);
	Entity* e = groupRoster[placedCount];

	e->getC<SpriteComponent>().drawBool = true;
	for (auto& t : groupTiles)
	{
		Vector2D mouseG = IsometricGrid::gridFromScreen(Keyboard_Mouse::getGrid(), Keyboard_Mouse::getScreen(), t->getC<TileComponent>().height);
		e->getC<TransformComponent>().moveByGrid(mouseG);
	}

	if (Keyboard_Mouse::leftClick() && canPlaceHere()) {
		placeUnits();
		LOG("unit placed");
	}
		
	if (placedCount == maxParty || placedCount == groupRoster.size()) {
		finishPlacement();
	}

	if (Keyboard_Mouse::rightClick() && placedCount > 0) {
		finishPlacement();
		e->getC<SpriteComponent>().drawBool = false;
	}
}


bool CombatPlacement::canPlaceHere()
{
	auto& cpTiles = combatManager->entityManager.getGroup(EntityManager::groupTiles);

	for (auto& t : cpTiles) {
		Vector2D tGrid = t->getC<TileComponent>().getGrid();

		if (t->getC<TileComponent>().placeHere && Keyboard_Mouse::hover(tGrid, t->getC<TileComponent>().height)) {
			combatManager->getUnitsTurn()->getC<TransformComponent>().tile = t; 
			t->getC<TileComponent>().blocked = true;
			return true;
		}
	}
	return false;
}

void CombatPlacement::placeUnits()
{
	auto& groupRoster = combatManager->entityManager.getGroup(EntityManager::groupRoster);
	auto& groupTiles = combatManager->entityManager.getGroup(EntityManager::groupTiles);
	Entity* e = groupRoster[placedCount];
	//combatManager->setUnitsTurn(e);

	e->getC<SpriteComponent>().drawBool = true;

	for (auto& t : groupTiles)
	{
		Vector2D mouseG = IsometricGrid::gridFromScreen(Keyboard_Mouse::getGrid(), Keyboard_Mouse::getScreen(), t->getC<TileComponent>().height);
		e->getC<TransformComponent>().moveByGrid(mouseG);
	}
	placedCount++;
}

void CombatPlacement::finishPlacement()
{
	auto& groupRoster = combatManager->entityManager.getGroup(EntityManager::groupRoster);
	auto& groupTiles = combatManager->entityManager.getGroup(EntityManager::groupTiles);

	LOG("placement finished");

	if (placedCount < maxParty && groupRoster.size() < placedCount) {
		Entity* e = groupRoster[placedCount];
	}

	combatManager->state = CombatManager::menu;
	placedCount = 0;
	for (auto& t : groupTiles) {
		t->getC<TileComponent>().placeHere = false;
	}
}