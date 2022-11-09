#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include <iostream>

class Component;
class Entity;
class EntityManager;

using ComponentID = std::size_t;
using Group = std::size_t;

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

//Entity private namespaces
using ComponentVectorUptr = std::vector<std::unique_ptr<Component>>;
using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArrayPtr = std::array<Component*, maxComponents>;
using GroupBitSet = std::bitset<maxGroups>;

//EntityManager private namespaces
using EntityVectorUptr = std::vector<std::unique_ptr<Entity>>;
using EntityArrayVectorPtr = std::array<std::vector<Entity*>, maxGroups>;

inline ComponentID getNewComponentTypeID()
{
	static ComponentID lastID = 0u;
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	static ComponentID typeID = getNewComponentTypeID();
	return typeID;
}


class Component
{
public:
	Entity* entity;

	virtual ~Component() {}

	virtual void initialize() {}
	virtual void update() {}
	virtual void draw() {}
	
};


class Entity
{
public:
	
	Entity(EntityManager& manager);
	~Entity();

	void update();
	void draw();

	//components
	template <typename T> bool hasComponent() const
	{
		return componentBitSet[getComponentTypeID<T>()];
	}

	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... args)
	{
		T* c(new T(std::forward<TArgs>(args)...));
		c->entity = this;
		std::unique_ptr<Component>uPtr{ c };
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;

		c->initialize();
		return *c;
	}

	template<typename T> T& getComponent() const
	{
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}

	//groups
	bool hasGroup(Group group);
	void addGroup(Group group);
	void delGroup(Group group);

	//getters and setters
	bool isActive() const { return active; }
	void setActive(bool setActive) { active = setActive; }


private:
	EntityManager& entityManager; 
	bool active = true;

	ComponentVectorUptr components;
	ComponentArrayPtr componentArray;
	ComponentBitSet componentBitSet;

	GroupBitSet groupBitSet;

};


class EntityManager
{
public:

	void update();
	void draw();

	void refresh();

	Entity& addEntity();

	void AddToGroup(Entity* entity, Group group);
	std::vector<Entity*>& getGroup(Group group);

	enum groupLabels : std::size_t
	{
		groupTiles,
		groupUnits,
		groupColliders,
		groupClickable,
		groupEnemies,
		groupRange,
		groupRoster

	};

private:
	EntityVectorUptr entities;
	EntityArrayVectorPtr groupedEntities;
};