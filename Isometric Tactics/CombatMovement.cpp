#include "CombatMovement.h"


CombatMovement::CombatMovement()
{}

void CombatMovement::update()
{
	if (combatManager->getUnitsTurn()->getComponent<StatsComponent>().currentMove == 0)
		combatManager->state = CombatManager::menu;

	//showMoveRange();
	checkRange(combatManager->getUnitsTurn()->getComponent<TransformComponent>().tile, combatManager->getUnitsTurn()->getComponent<StatsComponent>().currentMove);
	if (Keyboard_Mouse::leftClick())
	{
		move();
		LOG("combat move left click\n");
	}
}

void CombatMovement::move()
{
	auto& cmTiles = combatManager->entityManager.getGroup(EntityManager::groupTiles);
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
	}
}

bool CombatMovement::unitCanMoveHere()
{
	auto& cmTiles = combatManager->entityManager.getGroup(EntityManager::groupTiles);

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




void CombatMovement::checkRange(Entity* tilePtr, int move)
{
	if (tilePtr == nullptr)
	{
		LOG("nullptr tile in check range");
		return;
	}
		
	if (move == 0)
		return;

	auto& tileComp = tilePtr->getComponent<TileComponent>();
	auto& leftTC = tileComp.left->getComponent<TileComponent>();
	auto& rightTC = tileComp.right->getComponent<TileComponent>();
	auto& upTC = tileComp.up->getComponent<TileComponent>();
	auto& downTC = tileComp.down->getComponent<TileComponent>();

	int leftHDiff = abs(tileComp.height - leftTC.height);
	if (move > 0 &&
		leftHDiff < combatManager->getUnitsTurn()->getComponent<StatsComponent>().jump &&
		tilePtr->getComponent<TileComponent>().blocked == false)
	{
		tileComp.left->addGroup(EntityManager::groupRange);
	}

	int rightHDiff = abs(tileComp.height - rightTC.height);
	if (move > 0 &&
		rightHDiff < combatManager->getUnitsTurn()->getComponent<StatsComponent>().jump &&
		tilePtr->getComponent<TileComponent>().blocked == false)
	{
		tileComp.right->addGroup(EntityManager::groupRange);
	}

	int upHDiff = abs(tileComp.height - upTC.height);
	if (move > 0 &&
		upHDiff < combatManager->getUnitsTurn()->getComponent<StatsComponent>().jump &&
		tilePtr->getComponent<TileComponent>().blocked == false)
	{
		tileComp.up->addGroup(EntityManager::groupRange);
	}


	int downHDiff = abs(tileComp.height - downTC.height);
	if (move > 0 &&
		downHDiff < combatManager->getUnitsTurn()->getComponent<StatsComponent>().jump &&
		tilePtr->getComponent<TileComponent>().blocked == false)
	{
		tileComp.down->addGroup(EntityManager::groupRange);
	}

	move--;

	if (move == 0)
		return;

	checkRange(tileComp.left, move);
	checkRange(tileComp.right, move);
	checkRange(tileComp.up, move);
	checkRange(tileComp.down, move);
}