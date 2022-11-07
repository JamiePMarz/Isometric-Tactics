#pragma once
#include "CombatManager.h"
#include "ECS.h"

class CombatManager;


class CombatComponent
{
public:

	virtual ~CombatComponent() {}
	virtual void update() {}

	EntityManager* entityManager;
	CombatManager* combatManager;


private:
	
};