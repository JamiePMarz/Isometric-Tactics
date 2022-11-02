#include "CombatPlacement.h"

extern EntityManager entityManager;
auto& roster(entityManager.getGroup(Game::groupRoster));
auto& cpTiles(entityManager.getGroup(Game::groupTiles));

extern CombatManager combatManager;

int CombatPlacement::placedCount = 0;
bool CombatPlacement::finPlace = false;


CombatPlacement::CombatPlacement(EntityManager& eManager, CombatManager& cManager) : entityManager(eManager), combatManager(cManager)
{}
CombatPlacement::~CombatPlacement()
{}

void CombatPlacement::update()
{
	//add a way to choose which units to add
	Entity* e = roster[placedCount];

	e->getComponent<SpriteComponent>().inBattleTeam = true;
	e->getComponent<TransformComponent>().moveByGrid(Keyboard_Mouse::getGridPos());


	if (Keyboard_Mouse::leftClick() && canPlaceHere())
		placeUnits();

	if (Keyboard_Mouse::rightClick() && placedCount > 0 || placedCount == 5) //hardcoded
		finishPlacement();
}

bool CombatPlacement::canPlaceHere()
{
	for (auto& t : cpTiles)
	{
		auto& tc = t->getComponent<TileComponent>();
		Vector2D tcGridPos = tc.getGridPosition();
		if (tc.placeHere && Keyboard_Mouse::hover(tcGridPos))
		{
			tc.blocked = true;
			return true;
		}
	}
	return false;
}

void CombatPlacement::placeUnits()
{
	Entity* e = roster[placedCount];
	e->getComponent<SpriteComponent>().inBattleTeam = true;
	e->getComponent<TransformComponent>().moveByGrid(Keyboard_Mouse::getGridPos());
	placedCount++;
}

void CombatPlacement::finishPlacement()
{
	if (placedCount < 5)
	{
		Entity* e = roster[placedCount];
		e->getComponent<SpriteComponent>().inBattleTeam = false;
	}
	CombatManager::state = CombatManager::combatState::menu;
	std::cout << "state is menu" << std::endl;
	placedCount = 0;
	finPlace = true;
	for (auto& t : cpTiles)
	{
		t->getComponent<TileComponent>().placeHere = false;
	}
}