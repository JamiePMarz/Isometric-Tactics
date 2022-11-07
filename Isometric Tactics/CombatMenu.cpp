#include "CombatMenu.h"

CombatMenu::CombatMenu(EntityManager& eManager, CombatManager& cManager) : entityManager(eManager), combatManager(cManager)
{}


void CombatMenu::update()
{
	if (Keyboard_Mouse::keyPress(SDLK_1))
	{
		combatManager.state = CombatManager::combatState::move;
		std::cout << "state is: move" << std::endl;
	}

	if (Keyboard_Mouse::keyPress(SDLK_2))
	{
		combatManager.state = CombatManager::combatState::attack;
		std::cout << "state is: attack" << std::endl;
	}

	if (Keyboard_Mouse::keyPress(SDLK_3))
	{
		//state = placement;
		//std::cout << "state is: placement" << state << std::endl;
	}

	if (Keyboard_Mouse::keyPress(SDLK_4))
	{
		combatManager.state = CombatManager::combatState::end;
		std::cout << "state is: end" << std::endl;
	}
}

void CombatMenu::coutMenu()
{
	std::cout << "CONTROLS\n"
		<< "Move: 1.\n"
		<< "Attack: 2.\n"
		<< "Test pathing: 3.\n"
		<< "End Turn: 4.\n";
}
