#pragma once
#include "CombatComponents.h"
#include "Keyboard_Mouse.h"


class CombatMenu : public CombatComponent
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

	CombatMenu();
	~CombatMenu() {}

	void update();
	void coutMenu();


private:
	static menuOptions option;

};