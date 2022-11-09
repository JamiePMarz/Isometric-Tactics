#pragma once
#include <string>
#include <vector>
#include "Macros.h"
#include "ECS.h"
#include "AssetManager.h"
#include "IsometricGrid.h"

class IsometricGrid;
struct IsoMap;
class CombatManager;


class CombatComponent
{
public:

	virtual ~CombatComponent() = default;
	virtual void update() {}

	CombatManager* combatManager;


private:

};


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
		csCount

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
	std::vector<CombatComponent*> combatComponents;
	const int maxCCSize = csCount;
	EntityManager& entityManager;


private:
	Entity* unitsTurn;
	
	static IsometricGrid* isoGrid;
	static IsoMap* isoMap;


};