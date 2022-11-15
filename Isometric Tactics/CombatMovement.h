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
	void pathFinding(TileComponent* tileComp, int move, int* directions);
	
	//getters and setters

	//pub vars
	static int cntPF;
	static bool showPath;


private:

};