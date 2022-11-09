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
	UnitComponent();
	UnitComponent(bool random);
	~UnitComponent();

	void initialize() override;


	//public vars


private:
	bool randomUnit = false;


};