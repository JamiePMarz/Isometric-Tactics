#include "TileComponent.h"


TileComponent::TileComponent(int srcX, int srcY, int xpos, int ypos, int tileSize, int scale, std::string aTexture, int index, int i, int j)
{
	texture = AssetManager::getTexture(aTexture);

	src.x = srcX;
	src.y = srcY;
	src.w = src.h = tileSize;
	screenPos.x = xpos;
	screenPos.y = ypos;
	gridPos.x = i;
	gridPos.y = j;

	dest.w = dest.h = tileSize * scale;

	gridIndex = index;

	if (src.x == 0 && src.y == 0)
	{
		selectable = false;
		blocked = true;
	}
}


void TileComponent::draw()
{
	TextureManager::drawTexture(texture, src, dest, SDL_FLIP_NONE);


	if (Keyboard_Mouse::mouseHovers(gridPos) && selectable)
	{
		TextureManager::drawTileTextures("tile_cusor", dest);
	}

	if (entity->hasGroup(Game::groupSelectedTile))
		TextureManager::drawTileTextures("tile_highlighted", dest);

}


void TileComponent::update()
{
	//position
	dest.x = static_cast<float>(screenPos.x);
	dest.y = static_cast<float>(screenPos.y);
		
	//left clicked
	if (Keyboard_Mouse::leftClick())
	{
		entity->delGroup(Game::groupSelectedTile);
		if (Keyboard_Mouse::mouseHovers(gridPos) && selectable)
		{
			entity->addGroup(Game::groupSelectedTile);
		}
	}
	

	//right clicked
	if (Keyboard_Mouse::rightClick())
	{
		entity->delGroup(Game::groupSelectedTile);
	}
}