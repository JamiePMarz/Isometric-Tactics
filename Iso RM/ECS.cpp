#include "ECS.h"


//Entity definitions
Entity::Entity(EntityManager& manager) : entityManager(manager)
{}

Entity::~Entity()
{}


void Entity::lmbClicked()
{
	
	std::cout << "entity clicked";
	for (auto& c : components) c->lmbClicked();
}


void Entity::update()
{
	for (auto& c : components) c->update();
}

void Entity::draw()
{
	for (auto& c : components) c->draw();
}


//groups
bool Entity::hasGroup(Group group)
{
	return groupBitSet[group];
}

void Entity::addGroup(Group group)
{
	groupBitSet[group] = true;
	entityManager.AddToGroup(this, group);
}

void Entity::delGroup(Group group)
{
	groupBitSet[group] = false;
}


//EntityManager definitions

void EntityManager::lmbClicked()
{
	for (auto& e : entities)
	{
		//if (Keyboard_Mouse::mouseHovers(e)//checks grid only uses transform
			e->lmbClicked();
	}
}


void EntityManager::update()
{
	for (auto& e : entities) e->update();
}

void EntityManager::draw()
{
	for (auto& e : entities) e->draw();
}

void EntityManager::refresh()
{
	//deconstructs entities when !active and removes from vector
	entities.erase(std::remove_if(std::begin(entities), std::end(entities),
		[](const std::unique_ptr<Entity>& entity)
		{
			return !entity->isActive();
		}
		), std::end(entities));

	for (auto i(0u); i < maxGroups; i++)
	{
		//same as above but creates v(vector from groupedEntities) to go through the array of vectors (groupedEntities)
		auto& vector(groupedEntities[i]);
		vector.erase(std::remove_if(std::begin(vector), std::end(vector),
			[i](Entity* entity)
			{
				return !entity->isActive() || !entity->hasGroup(i);
			}
			),std::end(vector));
	}
}

Entity& EntityManager::addEntity()
{
	Entity* e = new Entity(*this);
	std::unique_ptr<Entity> uPtr{ e };
	entities.emplace_back(std::move(uPtr));
	return *e;
}

//groups
void EntityManager::AddToGroup(Entity* entity, Group group)
{
	groupedEntities[group].emplace_back(entity);
}

std::vector<Entity*>& EntityManager::getGroup(Group group)
{
	return groupedEntities[group];
}