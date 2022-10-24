#include "CombatMenu.h"


void CombatMenu::drawMenu()
{
	if (CombatManager::getCombatState() == menu)
		TextureManager::drawMenu();
}
