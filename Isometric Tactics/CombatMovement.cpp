#include "CombatMovement.h"


CombatMovement::CombatMovement()
{}

void CombatMovement::update()
{
	//LOG("cm update begins");
	Entity* e = combatManager->getUnitsTurn();
	if (e->getComponent<StatsComponent>().currentMove == 0)
		combatManager->state = CombatManager::menu;

	//showMoveRange();
	if (e->getComponent<TransformComponent>().tile == nullptr)
		LOG("cm update tile == nullptr");
	pathFinding(&e->getComponent<TransformComponent>().tile->getComponent<TileComponent>(), e->getComponent<StatsComponent>().currentMove);
	if (Keyboard_Mouse::leftClick())
	{
		move();
		LOG("combat move left click\n");
	}
	//LOG("cm update ends");
}

void CombatMovement::move()
{
	auto& cmTiles = combatManager->entityManager.getGroup(EntityManager::groupTiles);
	auto& cmPath = combatManager->entityManager.getGroup(EntityManager::groupPath);
	auto& eTransComp = combatManager->getUnitsTurn()->getComponent<TransformComponent>();
	if (unitCanMoveHere())
	{
		for (auto& t : cmTiles)
		{
			if (eTransComp.grid == t->getComponent<TileComponent>().getGrid())
				t->getComponent<TileComponent>().blocked = false;
			if (Keyboard_Mouse::getGrid() == t->getComponent<TileComponent>().getGrid())
				t->getComponent<TileComponent>().blocked = true;
		}
		eTransComp.moveByGrid(Keyboard_Mouse::getGrid());
		LOG("entity grid: " << combatManager->getUnitsTurn()->getComponent<TransformComponent>().grid);
		combatManager->state = CombatManager::menu;
		for (auto& e : cmPath)
		{
			e->delGroup(EntityManager::groupPath);
		}

	}
}

bool CombatMovement::unitCanMoveHere()
{
	auto& cmTiles = combatManager->entityManager.getGroup(EntityManager::groupPath);

	Vector2D unitPos = combatManager->getUnitsTurn()->getComponent<TransformComponent>().grid;
	Vector2D mousePos = Keyboard_Mouse::getGrid();
	Entity* tPtr = nullptr;
	TileComponent* tileC = nullptr;
	for (auto& t : cmTiles)
	{
		if (t->getComponent<TileComponent>().getGrid() == mousePos)
		{
			tileC = &t->getComponent<TileComponent>();
			tPtr = t;
		}
	}
	if (tileC == nullptr)
		return false;

	int xDist = abs(unitPos.x - mousePos.x);
	int yDist = abs(unitPos.y - mousePos.y);

	if (combatManager->getUnitsTurn()->getComponent<StatsComponent>().currentMove >= xDist + yDist && !tileC->blocked)
	{
		combatManager->getUnitsTurn()->getComponent<StatsComponent>().currentMove -= xDist + yDist;
		LOG("move left: " << combatManager->getUnitsTurn()->getComponent<StatsComponent>().currentMove);
		combatManager->getUnitsTurn()->getComponent<TransformComponent>().tile = tPtr;
		LOG("tile in transComp: " << tPtr->getComponent<TileComponent>().getGrid());
		tPtr = nullptr;
		return true;
	}
	else
	{
		LOG("unit can't move\n");
		tPtr = nullptr;
		return false;
	}
}



void CombatMovement::showMoveRange()//alter for attack component targeting
{
	auto& cmTiles = combatManager->entityManager.getGroup(EntityManager::groupTiles);

	int moveRange = combatManager->getUnitsTurn()->getComponent<StatsComponent>().currentMove;
	Vector2D unitPos = combatManager->getUnitsTurn()->getComponent<TransformComponent>().grid;
	Entity* baseTile = combatManager->getUnitsTurn()->getComponent<TransformComponent>().tile;

	for (auto& t : cmTiles)
	{
		Vector2D tilePos = t->getComponent<TileComponent>().getGrid();
		
		int xDist = abs(unitPos.x - tilePos.x);
		int yDist = abs(unitPos.y - tilePos.y);

		if (combatManager->getUnitsTurn()->getComponent<StatsComponent>().currentMove >= xDist + yDist && t->getComponent<TileComponent>().blocked == false)
			t->addGroup(EntityManager::groupRange);
		else
			t->delGroup(EntityManager::groupRange);
	}	
}


void CombatMovement::pathFinding(TileComponent* tileComp, int move)
{

	//LOG(move);
	if (move == 0)
	{
		//LOG("move = 0 so return (start)");
		return;
	}
		
	int comparison;

	for (int i = 0; i < 4; i++)
	{
		if (tileComp->tileDir[i] != nullptr)
		{
			bool add = true;
			auto& tempTC = tileComp->tileDir[i]->getComponent<TileComponent>();
			comparison = abs(tileComp->height - tempTC.height);
			//LOG("comparison: " << comparison);
			if (move > 0 && comparison < combatManager->getUnitsTurn()->getComponent<StatsComponent>().jump && tempTC.blocked == false)
			{
				auto& cmRange = combatManager->entityManager.getGroup(EntityManager::groupPath);
				for (auto t : cmRange)
				{
					if (t->getComponent<TileComponent>().getGrid() == tempTC.getGrid())
					{
						//LOG("tile wont be added, it is in group range");
						add = false;
					}
				}
				if (add)
				{
					//LOG("tile added to range");
					tempTC.entity->addGroup(EntityManager::groupPath);
				}
			}
		}
	}

	move--;
	if (move == 0)
	{
		//LOG("move = 0 so return (end)");
		return;
	}

	for (int j = 0; j < 4; j++)
	{
		if (tileComp->tileDir[j] != nullptr && !tileComp->tileDir[j]->getComponent<TileComponent>().blocked)
			pathFinding(&tileComp->tileDir[j]->getComponent<TileComponent>(), move);
	}
}