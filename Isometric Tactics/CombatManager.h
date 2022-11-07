#pragma once
#include "ECS.h"
#include "CombatMovement.h"
#include "CombatMenu.h"
#include "CombatPlacement.h"
#include "Components.h"
#include "IsometricGrid.h"
#include <string>
#include "AssetManager.h"
#include <vector>

class CombatMovement;
class CombatPlacement;
class CombatMenu;
class IsometricGrid;
struct IsoMap;


class CombatManager
{
public:
	
	enum combatState
	{
		neutral,
		menu,
		move,
		attack,
		skill_1,
		skill_2,
		item,
		end,
		placement,
		//test

	};


	CombatManager(EntityManager& eManager);
	~CombatManager() {}

	void startCombat(std::string mapID);
	void endCombat();

	void update();

	void endTurn();

	//getters and setters
	void setCombatState(combatState newState) { state = newState; }
	static combatState getCombatState() { return state; }

	void setUnitsTurn(Entity* newUnit);
	Entity* getUnitsTurn() const { return unitsTurn; }

	//public vars
	static combatState state;


private:
	EntityManager& entityManager;
	Entity* unitsTurn;
	CombatMovement* combatMove;
	CombatMenu* combatMenu;
	CombatPlacement* combatPlacement;
	//CombatTest* combatTest;
	
	static IsometricGrid* isoGrid;
	static IsoMap* isoMap;

};