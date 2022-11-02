#include "UnitComponent.h"



UnitComponent::UnitComponent(Entity* aEntity) : entity(aEntity)
{}
UnitComponent::UnitComponent(Entity* aEntity, bool random) : entity(aEntity), randomUnit(random)
{}
UnitComponent::~UnitComponent()
{}


void UnitComponent::initialize()
{
	entity->addComponent<TransformComponent>();
	randomUnit ? std::cout << "random unit\n" : std::cout << " not random unit\n";
	//if random determine race, class, stats, sprite
	entity->addComponent<SpriteComponent>("ph_1");//adds these into con
	entity->addComponent<StatsComponent>();
	entity->addGroup(Game::groupUnits);
}