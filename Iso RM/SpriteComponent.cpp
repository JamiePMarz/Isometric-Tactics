#include "SpriteComponent.h"


SpriteComponent::SpriteComponent(std::string id)
{
	setTexture(id);
}

SpriteComponent::SpriteComponent(std::string id, bool isAnimated)//frames and speed hardcoded
{
	animated = isAnimated;
	Animation idle = Animation(0, 8, 300);
	Animation walk = Animation(1, 8, 300);

	animations.emplace("idle", idle);
	animations.emplace("walk", walk);


	play("idle");
	setTexture(id);
}

SpriteComponent::~SpriteComponent()
{}

void SpriteComponent::setTexture(std::string id)
{
	texture = AssetManager::getTexture(id);
}

void SpriteComponent::initialize()
{
	transform = &entity->getComponent<TransformComponent>();

	src.x = src.y = 0;
	src.w = transform->width;
	src.h = transform->height;
}

void SpriteComponent::update()
{
	if (animated)
	{
		src.x = src.w * static_cast<int>((SDL_GetTicks() / spriteSpeed) % spriteFrames);
		// % spriteFrames(8) will give any value in multiples of spriteFrames of the result of srcRect.w(32) * GetTicks / 100
	}

	src.y = spriteIndex * transform->height;
	
	//dest.x = static_cast<int>(transform->position.x) - Game::camera.x;
	//dest.y = static_cast<int>(transform->position.y) - Game::camera.y;
	dest.x = static_cast<int>(transform->screenPos.x);
	dest.y = static_cast<int>(transform->screenPos.y);
	dest.w = transform->scale * transform->width;
	dest.h = transform->scale * transform->height;
}

void SpriteComponent::draw()
{
	TextureManager::drawTexture(texture, src, dest, spriteFlip);
}

void SpriteComponent::play(const char* animationName)
{
	spriteFrames = animations[animationName].frames;
	spriteIndex = animations[animationName].index;
	spriteSpeed = animations[animationName].speed;
}
