#include "UnitComponent.h"



UnitComponent::UnitComponent()
{}
UnitComponent::UnitComponent(bool random) : randomUnit(random)
{}
UnitComponent::~UnitComponent()
{}


void UnitComponent::initialize()
{
	entity->addC<TransformComponent>();
	//if random determine race, class, stats, sprite
	entity->addC<SpriteComponent>("ph_1");//adds these into con
	entity->addC<StatsComponent>();
	entity->addGroup(EntityManager::groupUnits);
}