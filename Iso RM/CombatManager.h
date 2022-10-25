#pragma once
#include "ECS.h"
#include "CombatMovement.h"
#include "CombatMenu.h"
#include "Components.h"

class CombatMovement;
class CombatMenu;


class CombatManager
{
public:
	
	enum combatState
	{
		neutral,
		menu,
		move,
		attack,
		skill_1,
		skill_2,
		item,
		end

	};


	CombatManager(EntityManager& manager);
	~CombatManager() {}


	void update();

	void endTurn();

	//getters and setters
	void setCombatState(combatState setCombatState) { state = setCombatState; }
	combatState getCombatState() { return state; }

	void setUnitsTurn(Entity* setUnitsTurn);
	Entity* getUnitsTurn() { return unitsTurn; }

	//public vars
	combatState state = neutral;

private:
	EntityManager& entityManager;
	Entity* unitsTurn;
	CombatMovement* combatMove;
	CombatMenu* combatMenu;
	


};