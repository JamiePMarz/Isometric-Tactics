#include "CombatMovement.h"

Entity* CombatMovement::unitsTurn;


CombatMovement::CombatMovement(EntityManager& manager) : entityManager(manager)
{}

void CombatMovement::update()
{
	showMoveRange();
	if (Keyboard_Mouse::leftClick())
	{
		move();
	}
}

void CombatMovement::move()
{
	if (unitCanMoveHere())
	{
		unitsTurn->getComponent<TransformComponent>().moveByGrid(Keyboard_Mouse::getGridPos());
	}
}

bool CombatMovement::unitCanMoveHere()
{
	Vector2D unitsPos = unitsTurn->getComponent<TransformComponent>().gridPos;
	Vector2D mousePos = Keyboard_Mouse::getGridPos();

	int xDist = abs(unitsPos.x - mousePos.x);
	int yDist = abs(unitsPos.y - mousePos.y);

	if (unitsTurn->getComponent<StatsComponent>().currentMove >= xDist + yDist/* &&
		tile isnt blocked*/																)
	{
		unitsTurn->getComponent<StatsComponent>().currentMove -= xDist + yDist;
		std::cout << "move left: " << unitsTurn->getComponent<StatsComponent>().currentMove << std::endl;
		return true;
	}
	else
	{
		//std::cout << mousePos << std::endl;
		std::cout << "unit can't move\n";
		return false;
	}
}

void CombatMovement::showMoveRange()
{
	int moveRange = unitsTurn->getComponent<StatsComponent>().currentMove;
	/*if (!entityManager.getGroup(Game::groupSelectedTile).empty())
	{
		for (auto& tile : entityManager.getGroup(Game::groupSelectedTile))
		{
			baseTile = tile;
		}
		std::cout << "base tile capted at gridpos: " << baseTile->getComponent<TileComponent>().getGridPosition() << std::endl;
	}*/
}