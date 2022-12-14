#pragma once
#include <map>
#include "Components.h"
#include "ECS.h"
#include "Animation.h"
#include <string>
#include <SDL.h>

class TransformComponent;
enum animated { animated = 1 };


class SpriteComponent : public Component
{
public:

	std::map<const char*, Animation> animations;
	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent() = default;
	SpriteComponent(std::string id);
	SpriteComponent(std::string id, bool isAnimated);
	~SpriteComponent();

	

	void initialize() override;
	void update() override;
	void draw() override;
	void play(const char* animationName);

	//public vars
	bool drawBool = false;

	//getters and setters
	void setTexture(std::string id);
	SDL_Texture* getTexture() { return texture; }
	SDL_Rect getSrc() { return src; }
	SDL_Rect getDest() { return dest; }//in use?


private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect src, dest;

	bool animated = false;
	int spriteIndex = 0;
	int spriteFrames = 0;
	int spriteSpeed = 100;

};
