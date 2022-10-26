#include "CombatMenu.h"

CombatMenu::menuOptions CombatMenu::option = menu;

CombatMenu::CombatMenu(EntityManager& eManager, CombatManager& cManager) : entityManager(eManager), combatManager(cManager)
{}


void CombatMenu::update()
{
	//std::cout << "menu state is " << option << std::endl;

	/*if (Keyboard_Mouse::_1click())
		option = move;*/

	switch (option)
	{
	case move:
		std::cout << "menu state is " << option << std::endl;
		//combatManager.state = (CombatManager::move);//make static
		//std::cout << "combatState is " << combatManager.state << std::endl;
		break;

	default:
		break;
	}
}


void CombatMenu::drawMenu()
{
	if (combatManager.getCombatState() == menu)
		TextureManager::drawMenu();
}
