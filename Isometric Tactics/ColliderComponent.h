#pragma once
#include <string>
#include <SDL.h>
#include "Components.h"
#include "TextureManager.h"

class TransformComponent;


class ColliderComponent : public Component
{
public:
	SDL_Rect collider;
	std::string tag;

	SDL_Texture* texture;
	SDL_Rect src, dest;

	TransformComponent* transform;

	ColliderComponent(std::string aTag);
	ColliderComponent(std::string aTag, int xpos, int ypos, int size);

	void initialize() override;
	void update() override;
	void draw() override;

};