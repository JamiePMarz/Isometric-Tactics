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

	enum TilePtrs
	{
		right,
		down,
		up,
		left,

	};


	 Entity* tileDir[4];


	//getters and setter
	Vector2D getScreen() const { return screen; }
	void addHeight(int aHeight, int scaledSize);

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