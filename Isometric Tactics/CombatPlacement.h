#pragma once
#include <vector>
#include "ECS.h"
#include "CombatManager.h"
#include "TextureManager.h"

class CombatManager;


class CombatPlacement
{
public:
	CombatPlacement(EntityManager& eManager, CombatManager& cManager);
	~CombatPlacement();

	void update();

	void placeUnits();
	void finishPlacement();
	bool canPlaceHere();

	//getters and setters
	//public vars
	static bool finPlace;

private:
	EntityManager& entityManager;
	CombatManager& combatManager;

	static int placedCount;
	

};