#pragma once
#include "ECS.h"
#include "Keyboard_Mouse.h"
#include "Components.h"
#include "CombatManager.h"
//#include "CombatComponent.h"
#include "Macros.h"

class CombatManager;


class CombatMovement //: public CombatComponent
{
public:

	CombatMovement(EntityManager& eManager, CombatManager& cManager);

	void update(); //override;

	void move();

	bool unitCanMoveHere();
	void showMoveRange();

	
	//getters and setters
	static void setUnitsTurn(Entity* newUnit) { unitsTurn = newUnit; }

	//pub vars


private:
	EntityManager& entityManager;
	CombatManager& combatManager;
	static Entity* unitsTurn;

};