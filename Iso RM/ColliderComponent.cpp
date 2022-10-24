#include "ColliderComponent.h"


ColliderComponent::ColliderComponent(std::string aTag)
{
	tag = aTag;
}

ColliderComponent::ColliderComponent(std::string aTag, int xpos, int ypos, int size)
{
	tag = aTag;
	collider.x = xpos;
	collider.y = ypos;
	collider.h = collider.w = size;
}

void ColliderComponent::initialize()
{
	if (!entity->hasComponent<TransformComponent>())
		entity->addComponent<TransformComponent>();

	transform = &entity->getComponent<TransformComponent>();

	texture = TextureManager::loadTexture("Assets/collider.png");
	src = { 0, 0, 32, 32 };
	dest = { collider.x, collider.y, collider.w, collider.h };

}

void ColliderComponent::update()
{
	if (tag != "terrain")//redunant
	{
		collider.x = static_cast<int>(transform->position.x);
		collider.y = static_cast<int>(transform->position.y);
		collider.w = transform->scale * transform->width;
		collider.h = transform->scale * transform->height;
	}

	/*dest.x = collider.x - Game::camera.x;
	dest.y = collider.y - Game::camera.y;*/
	dest.x = collider.x;
	dest.y = collider.y;

}

void ColliderComponent::draw()
{
	TextureManager::drawTexture(texture, src, dest, SDL_FLIP_NONE);
}