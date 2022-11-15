#include "CombatMovement.h"
int CombatMovement::cntPF = 0;
bool CombatMovement::showPath = false;

CombatMovement::CombatMovement()
{}

void CombatMovement::update()
{
	Entity* e = combatManager->getUnitsTurn();
	if (e->getC<StatsComponent>().currentMove == 0) {
		combatManager->state = CombatManager::menu;
		LOG("No movement");
	}
	
	if (showPath) {
		size_t timestart = SDL_GetTicks();
		cntPF = 0;
		int directions[] = { -1,-1 };
		pathFinding(&e->getC<TransformComponent>().tile->getC<TileComponent>(), e->getC<StatsComponent>().currentMove, directions);
		LOG(SDL_GetTicks() - timestart);
		showPath = false;
		LOG("paths calc'd: " << cntPF);
	}

	if (Keyboard_Mouse::leftClick()) {
		move();
	}
}

void CombatMovement::move()
{
	auto& groupTiles = combatManager->entityManager.getGroup(EntityManager::groupTiles);
	auto& groupPath = combatManager->entityManager.getGroup(EntityManager::groupPath);
	Entity* e = combatManager->getUnitsTurn();
	Entity* eTile = e->getC<TransformComponent>().tile;

	if (unitCanMoveHere()) {
		eTile->getC<TileComponent>().blocked = false;
		for (auto& t : groupTiles) {
			Vector2D mGrid = IsometricGrid::gridFromScreen(Keyboard_Mouse::getGrid(), Keyboard_Mouse::getScreen(), t->getC<TileComponent>().height);

			if (mGrid == t->getC<TileComponent>().getGrid()) {
				t->getC<TileComponent>().blocked = true;
			}
			e->getC<TransformComponent>().moveByGrid(mGrid);
		}
		combatManager->state = CombatManager::menu;
		for (auto& e : groupPath) {
			e->delGroup(EntityManager::groupPath);
		}
	}
}

bool CombatMovement::unitCanMoveHere()
{
	auto& groupPath = combatManager->entityManager.getGroup(EntityManager::groupPath);
	Entity* e = combatManager->getUnitsTurn();
	Vector2D eGrid = e->getC<TransformComponent>().grid;
	Vector2D mGrid;

	for (Entity* t : groupPath) {
		mGrid = IsometricGrid::gridFromScreen(Keyboard_Mouse::getGrid(), Keyboard_Mouse::getScreen(), t->getC<TileComponent>().height);
		if (t->getC<TileComponent>().getGrid() == mGrid) {
			e->getC<TransformComponent>().tile = t;

			int xDist = abs(eGrid.x - mGrid.x);
			int yDist = abs(eGrid.y - mGrid.y);
			e->getC<StatsComponent>().currentMove -= xDist + yDist;

			LOG("move left: " << e->getC<StatsComponent>().currentMove);
			return true;
		}
	}

	LOG("unit can't move\n");
	return false;
}


void CombatMovement::showMoveRange()//alter for attack component targeting
{
	auto& cmTiles = combatManager->entityManager.getGroup(EntityManager::groupTiles);

	int moveRange = combatManager->getUnitsTurn()->getC<StatsComponent>().currentMove;
	Vector2D unitPos = combatManager->getUnitsTurn()->getC<TransformComponent>().grid;
	Entity* baseTile = combatManager->getUnitsTurn()->getC<TransformComponent>().tile;

	for (auto& t : cmTiles)
	{
		Vector2D tilePos = t->getC<TileComponent>().getGrid();
		
		int xDist = abs(unitPos.x - tilePos.x);
		int yDist = abs(unitPos.y - tilePos.y);

		if (combatManager->getUnitsTurn()->getC<StatsComponent>().currentMove >= xDist + yDist && t->getC<TileComponent>().blocked == false)
			t->addGroup(EntityManager::groupRange);
		else
			t->delGroup(EntityManager::groupRange);
	}	
}


void CombatMovement::pathFinding(TileComponent* tileComp, int move, int* directions)
{
	if (move == 0) { 
		//LOG("move = 0 so return (start)");
		return; 
	}

	++cntPF;

	auto& cmPath = combatManager->entityManager.getGroup(EntityManager::groupPath);
	auto& cmRoster = combatManager->entityManager.getGroup(EntityManager::groupRoster);
	Entity* e = combatManager->getUnitsTurn();

	move--;

	for (int i = 0; i < 4; i++) {
		if (directions[1] + i == 3) continue;//up+down or right+left
		if (directions[0] + i == 3) continue;//up+right/left+down or right+up/down+left
		if (tileComp->tileDir[i] == nullptr) continue;//edge

		if (tileComp->tileDir[i]->getC<TileComponent>().blocked) continue;

		//if (tileComp->tileDir[i]->getC<TileComponent>().blocked) {
		//	bool stillCalc = false;
		//	for (auto& e : cmRoster) {
		//		if (tileComp->tileDir[i]->getC<TileComponent>().getGrid() == e->getC<TransformComponent>().grid && e->hasGroup(EntityManager::groupRoster)) {
		//			stillCalc = true;
		//		}
		//	}
		//	if (!stillCalc) continue;
		//}

		if (e->getC<StatsComponent>().jump < abs(tileComp->height - tileComp->tileDir[i]->getC<TileComponent>().height)) continue;

		if (!tileComp->tileDir[i]->hasGroup(EntityManager::groupPath)) {
			tileComp->tileDir[i]->addGroup(EntityManager::groupPath);
		}

		int newDirections[] = { directions[1],i };
		pathFinding(&tileComp->tileDir[i]->getC<TileComponent>(), move, newDirections);
	}

	if (move == 0) {
		//LOG("move = 0 so return (end)");
		return;
	}
}