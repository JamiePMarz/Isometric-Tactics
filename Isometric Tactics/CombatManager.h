#pragma once
#include "ECS.h"
#include "CombatMovement.h"
#include "CombatMenu.h"
#include "Components.h"
#include "IsometricGrid.h"
#include <string>
#include "AssetManager.h"

class CombatMovement;
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
		end

	};


	CombatManager(EntityManager& manager);
	~CombatManager() {}


	void selectGrid();
	void startCombat(std::string mapID);
	void endCombat();


	void update();

	void endTurn();

	//getters and setters
	void setCombatState(combatState setCombatState) { state = setCombatState; }
	static combatState getCombatState() { return state; }

	void setUnitsTurn(Entity* setUnitsTurn);
	Entity* getUnitsTurn() const { return unitsTurn; }

	//public vars
	static combatState state;
	


private:
	EntityManager& entityManager;
	Entity* unitsTurn;
	CombatMovement* combatMove;
	CombatMenu* combatMenu;
	
	static IsometricGrid* isoGrid;
	static IsoMap* isoMap;

};