#include "CombatMovement.h"

Entity* CombatMovement::unitsTurn;
extern EntityManager entityManager;

auto& tileRange = entityManager.getGroup(Game::groupTiles);
//auto& tileRange(entityManager.getGroup(Game::groupTiles));

CombatMovement::CombatMovement(EntityManager& eManager, CombatManager& cManager) : entityManager(eManager), combatManager(cManager)
{}

void CombatMovement::update()
{
	if (Keyboard_Mouse::leftClick())
		move();
}

void CombatMovement::move()
{
	if (unitCanMoveHere())
	{
		unitsTurn->getComponent<TransformComponent>().moveByGrid(Keyboard_Mouse::getGridPos());
		showMoveRange();
	}
	
}

bool CombatMovement::unitCanMoveHere()
{
	Vector2D unitPos = unitsTurn->getComponent<TransformComponent>().gridPos;
	Vector2D mousePos = Keyboard_Mouse::getGridPos();

	int xDist = abs(unitPos.x - mousePos.x);
	int yDist = abs(unitPos.y - mousePos.y);

	if (unitsTurn->getComponent<StatsComponent>().currentMove >= xDist + yDist)/* && isnt blocked*/
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

	

	for (auto& t : tileRange)
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