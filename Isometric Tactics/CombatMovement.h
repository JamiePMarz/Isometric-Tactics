#pragma once
#include "CombatComponents.h"


class CombatMovement : public CombatComponent
{
public:

	CombatMovement();
	~CombatMovement() {}

	void update() override;

	void move();

	bool unitCanMoveHere();
	void showMoveRange();
	void checkRange(Entity* tilePtr, int move);
	
	//getters and setters

	//pub vars


private:

};