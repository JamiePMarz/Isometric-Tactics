#include "CombatMovement.h"

Entity* CombatMovement::unitsTurn;

extern EntityManager entityManager;
auto& cmTiles(entityManager.getGroup(Game::groupTiles));


CombatMovement::CombatMovement(EntityManager& eManager, CombatManager& cManager) : entityManager(eManager), combatManager(cManager)
{}

void CombatMovement::update()
{
	if (unitsTurn->getComponent<StatsComponent>().currentMove == 0)
		combatManager.state = CombatManager::combatState::menu;

	showMoveRange();
	if (Keyboard_Mouse::leftClick())
	{
		move();
		LOG("combat move left click\n");
	}
		

}

void CombatMovement::move()
{
	if (unitCanMoveHere())
	{
		for (auto& t : cmTiles)
		{
			if (unitsTurn->getComponent<TransformComponent>().grid == t->getComponent<TileComponent>().getGrid())
				t->getComponent<TileComponent>().blocked = false;
			if (Keyboard_Mouse::getGrid() == t->getComponent<TileComponent>().getGrid())
				t->getComponent<TileComponent>().blocked = true;
		}

		unitsTurn->getComponent<TransformComponent>().moveByGrid(Keyboard_Mouse::getGrid());

		combatManager.state = CombatManager::combatState::menu;
	}
	
}

bool CombatMovement::unitCanMoveHere()
{
	Vector2D unitPos = unitsTurn->getComponent<TransformComponent>().grid;
	Vector2D mousePos = Keyboard_Mouse::getGrid();

	TileComponent* tileC = nullptr;
	for (auto& t : cmTiles)
	{
		if (t->getComponent<TileComponent>().getGrid() == mousePos)
			tileC = &t->getComponent<TileComponent>();
	}

	if (tileC == nullptr)
		return false;


	int xDist = abs(unitPos.x - mousePos.x);
	int yDist = abs(unitPos.y - mousePos.y);

	if (unitsTurn->getComponent<StatsComponent>().currentMove >= xDist + yDist && !tileC->blocked)
	{
		unitsTurn->getComponent<StatsComponent>().currentMove -= xDist + yDist;
		LOG("move left: " << unitsTurn->getComponent<StatsComponent>().currentMove << std::endl);
		return true;
	}
	else
	{
		LOG("unit can't move\n");
		return false;
	}
}



void CombatMovement::showMoveRange()
{
	int moveRange = unitsTurn->getComponent<StatsComponent>().currentMove;
	Vector2D unitPos = unitsTurn->getComponent<TransformComponent>().grid;

	

	for (auto& t : cmTiles)
	{
		Vector2D tilePos = t->getComponent<TileComponent>().getGrid();
		
		int xDist = abs(unitPos.x - tilePos.x);
		int yDist = abs(unitPos.y - tilePos.y);

		if (unitsTurn->getComponent<StatsComponent>().currentMove >= xDist + yDist && t->getComponent<TileComponent>().blocked == false)
			t->addGroup(Game::groupRange);
		else
			t->delGroup(Game::groupRange);
	}
}
