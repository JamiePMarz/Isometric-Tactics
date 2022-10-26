#pragma once
#include "Components.h"
#include <SDL.h>
#include "ECS.h"
#include "AssetManager.h"


class TileComponent : public Component
{
public:
	TileComponent() = default;
	TileComponent(int srcX, int srcY, int xpos, int ypos, int tileSize, int scale, std::string aTexture, int index, int i, int j);

	~TileComponent() override { SDL_DestroyTexture(texture); }

	void draw() override;
	void update() override;

	Entity* entity;
	Entity* right = nullptr;
	Entity* down = nullptr;
	Entity* left = nullptr;
	Entity* up = nullptr;
	int gridIndex;

	Vector2D getPosition() { return screenPos; }
	Vector2D getGridPosition() { return gridPos; }

	SDL_Texture* getTex() { return texture; }

	SDL_Rect getSrc() { return src; }
	SDL_Rect getDest() { return dest; }

	bool selectable = true;
	bool blocked = false;

	//getters and setter


private:
	SDL_Texture* texture;
	SDL_Rect src, dest;
	Vector2D screenPos;
	Vector2D gridPos;

};