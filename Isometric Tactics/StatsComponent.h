#pragma once
#include <iostream>
#include "Components.h"
#include "Macros.h"


struct StatsComponent : public Component
{
	//movement
	int maxMove = 4;
	int currentMove = maxMove;
	void moveReset() 
	{ 
		currentMove = maxMove; 
		//LOG(currentMove);
	}

};