#pragma once
#include "Components.h"
#include "ECS.h"
#include <string>

enum random : bool
{
	random = true
};

class UnitComponent : public Component
{
public:
	UnitComponent(Entity* aEntity);
	UnitComponent(Entity* aEntity, bool random);
	~UnitComponent();

	void initialize() override;


	//public vars
	Entity* entity;


private:
	bool randomUnit = false;


};