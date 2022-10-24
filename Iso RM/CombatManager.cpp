#include "CombatManager.h"

combatState CombatManager::state = move;


CombatManager::CombatManager(EntityManager& manager) : entityManager(manager)
{
	CombatMovement* combatMove = new CombatMovement(entityManager);
}


void CombatManager::update()
{
	switch (state)
	{
	case move:
		combatMove->update();
		break;

	default:
		break;
	}
}


void CombatManager::setUnitsTurn(Entity* setUnitsTurn)
{
	unitsTurn = setUnitsTurn;
	CombatMovement::setUnitsTurn(setUnitsTurn);
}

void CombatManager::endTurn()
{
	unitsTurn->getComponent<StatsComponent>().moveReset();
	//unitsTurn = nextUnit;
}