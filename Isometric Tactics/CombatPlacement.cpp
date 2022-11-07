#include "CombatPlacement.h"

extern EntityManager entityManager;
auto& roster(entityManager.getGroup(Game::groupRoster));
auto& cpTiles(entityManager.getGroup(Game::groupTiles));

extern CombatManager combatManager;

int CombatPlacement::placedCount = 0;//because its the index :/
int CombatPlacement::maxParty = 5;//because its compared to a static
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
	e->getComponent<TransformComponent>().moveByGrid(Keyboard_Mouse::getGrid());//add height offset here?


	if (Keyboard_Mouse::leftClick() && canPlaceHere())
		placeUnits();
		

	if (placedCount == maxParty || placedCount == roster.size())
		finishPlacement();


	if (Keyboard_Mouse::rightClick() && placedCount > 0)
	{
		finishPlacement();
		e->getComponent<SpriteComponent>().inBattleTeam = false;
	}
		
}

bool CombatPlacement::canPlaceHere()
{
	for (auto& t : cpTiles)
	{
		auto& tc = t->getComponent<TileComponent>();
		Vector2D tcGridPos = tc.getGrid();
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
	e->getComponent<TransformComponent>().moveByGrid(Keyboard_Mouse::getGrid());
	placedCount++;
}

void CombatPlacement::finishPlacement()
{
	LOG("placement finished\n");

	if (placedCount < maxParty && roster.size() < placedCount)
		Entity* e = roster[placedCount];

	CombatManager::state = CombatManager::combatState::menu;
	LOG("state is menu\n");
	placedCount = 0;
	finPlace = true;
	for (auto& t : cpTiles)
	{
		t->getComponent<TileComponent>().placeHere = false;
	}
}