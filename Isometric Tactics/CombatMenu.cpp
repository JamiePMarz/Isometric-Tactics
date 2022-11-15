#include "CombatMenu.h"


CombatMenu::CombatMenu()
{}


void CombatMenu::update()
{
	if (Keyboard_Mouse::keyPress(SDLK_1)) {
		combatManager->state = CombatManager::move;
		LOG("state is: move");
		LOG("current move: " << combatManager->getUnitsTurn()->getC<StatsComponent>().currentMove);
		CombatMovement::showPath = true;
	}

	if (Keyboard_Mouse::keyPress(SDLK_2)) {
		//combatManager->state = CombatManager::attack;
		LOG("state is: attack (dummy)");
	}

	if (Keyboard_Mouse::keyPress(SDLK_3))
	{}

	if (Keyboard_Mouse::keyPress(SDLK_4)) {
		combatManager->state = CombatManager::end;
		LOG("state is: end");
	}
}

void CombatMenu::coutMenu()
{
	LOG("CONTROLS\n"
	 << "Move: 1.\n"
	 << "Attack: 2.\n"
	 << "End Turn: 4.");
}
