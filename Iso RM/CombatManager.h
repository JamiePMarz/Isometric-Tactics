#pragma once
#include "ECS.h"
#include "CombatMovement.h"
#include "Components.h"

enum combatState
{
	menu,
	move

};

class CombatMovement;


class CombatManager
{
public:
	
	CombatManager(EntityManager& manager);
	~CombatManager() {}


	void update();

	static void combatLMB();

	void endTurn();

	//getters and setters
	void setCombatState(combatState setCombatState) { state = setCombatState; }
	static combatState getCombatState() { return state; }

	void setUnitsTurn(Entity* setUnitsTurn);

	//public vars
	

private:
	EntityManager& entityManager;
	Entity* unitsTurn;
	CombatMovement* combatMove;
	static combatState state;


};