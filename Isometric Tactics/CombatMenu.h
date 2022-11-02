#pragma once
#include "TextureManager.h"
#include "CombatManager.h"

class CombatManager;


class CombatMenu
{
public:

	enum menuOptions
	{
		menu,
		move,
		attack,
		skill1,
		skill2,
		item,
		status


	};

	CombatMenu(EntityManager& eManager, CombatManager& cManager);
	~CombatMenu() {}

	void update();
	void coutMenu();

	void drawMenu();

private:
	EntityManager& entityManager;
	CombatManager& combatManager;
	static menuOptions option;

};