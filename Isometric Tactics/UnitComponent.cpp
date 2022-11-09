#include "UnitComponent.h"



UnitComponent::UnitComponent()
{}
UnitComponent::UnitComponent(bool random) : randomUnit(random)
{}
UnitComponent::~UnitComponent()
{}


void UnitComponent::initialize()
{
	entity->addComponent<TransformComponent>();
	//randomUnit ? std::cout << "random unit\n" : std::cout << "not random unit\n";
	//if random determine race, class, stats, sprite
	entity->addComponent<SpriteComponent>("ph_1");//adds these into con
	entity->addComponent<StatsComponent>();
	entity->addGroup(EntityManager::groupUnits);
}