#pragma once
#include "Components.h"
#include <SDL.h>
#include "ECS.h"
#include "AssetManager.h"
#include "CombatManager.h"


class TileComponent : public Component
{
public:
	TileComponent() = default;
	TileComponent(int srcX, int srcY, int xpos, int ypos, int tileSize, int scale, std::string aTexture, int index, int i, int j);

	~TileComponent() override;


	void draw() override;
	void update() override;

	//entity ptrs
	//Entity* entity;//owner
	Entity* right = nullptr;
	Entity* down = nullptr;
	Entity* left = nullptr;
	Entity* up = nullptr;

	//getters and setter
	Vector2D getScreen() const { return screen; }
	void addScreenY(int y) { screen.y += y; }

	Vector2D getGrid() const { return grid; }

	SDL_Texture* getTex() const { return texture; }

	SDL_Rect getSrc() const { return src; }
	SDL_Rect getDest() const { return dest; }

	//public vars
	bool selectable = true;
	bool blocked = false;
	bool placeHere = false;
	int gridIndex;
	int height = 0;

private:
	SDL_Texture* texture;
	SDL_Rect src, dest;
	Vector2D screen, grid;

};