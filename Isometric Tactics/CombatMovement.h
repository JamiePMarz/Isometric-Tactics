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
	void pathFinding(TileComponent* tileComp, int move);
	
	//getters and setters

	//pub vars


private:

};