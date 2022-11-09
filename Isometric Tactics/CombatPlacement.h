#pragma once
#include "CombatComponents.h"


class CombatPlacement : public CombatComponent
{
public:
	CombatPlacement();
	~CombatPlacement();

	void update() override;

	void placeUnits();
	void finishPlacement();
	bool canPlaceHere();

	//getters and setters
	//public vars
	Entity* placingUnit = nullptr;

private:
	static int placedCount;
	static int maxParty;
	

};