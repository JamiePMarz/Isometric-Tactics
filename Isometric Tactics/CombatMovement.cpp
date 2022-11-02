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
		move();

}

void CombatMovement::move()
{
	if (unitCanMoveHere())
	{
		for (auto& t : cmTiles)
		{
			if (unitsTurn->getComponent<TransformComponent>().gridPos == t->getComponent<TileComponent>().getGridPosition())
				t->getComponent<TileComponent>().blocked = false;
			if (Keyboard_Mouse::getGridPos() == t->getComponent<TileComponent>().getGridPosition())
				t->getComponent<TileComponent>().blocked = true;
		}

		unitsTurn->getComponent<TransformComponent>().moveByGrid(Keyboard_Mouse::getGridPos());

		combatManager.state = CombatManager::combatState::menu;
	}
	
}

bool CombatMovement::unitCanMoveHere()
{
	Vector2D unitPos = unitsTurn->getComponent<TransformComponent>().gridPos;
	Vector2D mousePos = Keyboard_Mouse::getGridPos();

	TileComponent* tileC = nullptr;
	for (auto& t : cmTiles)
	{
		if (t->getComponent<TileComponent>().getGridPosition() == mousePos)
			tileC = &t->getComponent<TileComponent>();
	}

	if (tileC == nullptr)
		return false;


	int xDist = abs(unitPos.x - mousePos.x);
	int yDist = abs(unitPos.y - mousePos.y);

	if (unitsTurn->getComponent<StatsComponent>().currentMove >= xDist + yDist && !tileC->blocked)
	{
		unitsTurn->getComponent<StatsComponent>().currentMove -= xDist + yDist;
		std::cout << "move left: " << unitsTurn->getComponent<StatsComponent>().currentMove << std::endl;
		return true;
	}
	else
	{
		std::cout << "unit can't move\n";
		return false;
	}
}



void CombatMovement::showMoveRange()
{
	int moveRange = unitsTurn->getComponent<StatsComponent>().currentMove;
	Vector2D unitPos = unitsTurn->getComponent<TransformComponent>().gridPos;

	

	for (auto& t : cmTiles)
	{
		Vector2D tilePos = t->getComponent<TileComponent>().getGridPosition();
		
		int xDist = abs(unitPos.x - tilePos.x);
		int yDist = abs(unitPos.y - tilePos.y);

		if (unitsTurn->getComponent<StatsComponent>().currentMove >= xDist + yDist && t->getComponent<TileComponent>().blocked == false)
			t->addGroup(Game::groupRange);
		else
			t->delGroup(Game::groupRange);
	}
}


//void CombatMovement::unitsTurnF()
//{
//	unitsTurn = combatManager.getUnitsTurn();
//} 