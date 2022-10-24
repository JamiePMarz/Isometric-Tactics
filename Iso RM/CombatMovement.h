#pragma once
#include "ECS.h"
#include "Keyboard_Mouse.h"
#include "Components.h"


class CombatMovement
{
public:

	void update();

	static void move();

	static bool unitCanMoveHere();
	static void showMoveRange();

	

	//getters and setters
	static void setUnitsTurn(Entity* setUnitsTurn) { unitsTurn = setUnitsTurn; }



private:
	static Entity* unitsTurn;
	static Entity* selectedTile;
	SDL_Event ev;

};