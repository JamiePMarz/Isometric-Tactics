#pragma once
#include "ECS.h"
#include "Keyboard_Mouse.h"
#include "Components.h"


class CombatMovement
{
public:

	CombatMovement(EntityManager& manager);

	void update();

	static void move();

	static bool unitCanMoveHere();
	void showMoveRange();

	

	//getters and setters
	static void setUnitsTurn(Entity* setUnitsTurn) { unitsTurn = setUnitsTurn; }


	EntityManager& entityManager;
	//Entity* baseTile = nullptr;

private:
	static Entity* unitsTurn;
	SDL_Event ev;

};