#pragma once
#include <iostream>
#include "Components.h"


struct StatsComponent : public Component
{
	//movement
	int maxMove = 4;
	int currentMove = maxMove;
	void moveReset() 
	{ 
		currentMove = maxMove; 
		//std::cout << "current move: " << currentMove << std::endl;
	}

};