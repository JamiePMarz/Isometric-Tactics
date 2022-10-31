#pragma once
#include "ECS.h"
#include "Keyboard_Mouse.h"
#include "Components.h"
#include "CombatManager.h"


class CombatManager;


class CombatMovement
{
public:

	CombatMovement(EntityManager& eManager, CombatManager& cManager);

	void update();

	void move();

	bool unitCanMoveHere();
	void showMoveRange();
	
	void unitsTurnF();

	
	//getters and setters
	static void setUnitsTurn(Entity* setUnitsTurn) { unitsTurn = setUnitsTurn; }


	//pub vars
	


private:
	EntityManager& entityManager;
	CombatManager& combatManager;
	static Entity* unitsTurn;

};