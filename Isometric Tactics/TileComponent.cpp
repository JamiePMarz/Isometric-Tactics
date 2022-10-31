#include "TileComponent.h"


TileComponent::TileComponent(int srcX, int srcY, int xpos, int ypos, int tileSize, int scale, std::string aTexture, int index, int i, int j)
{
	//std::cout << "tile created\n";
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

	if (Keyboard_Mouse::hover(gridPos) && selectable)
		TextureManager::drawTileTextures("tile_cusor", dest);

	if (entity->hasGroup(Game::groupRange))
		TextureManager::drawTileTextures("tile_highlighted", dest);

}


void TileComponent::update()
{
	//position
	dest.x = static_cast<float>(screenPos.x);
	dest.y = static_cast<float>(screenPos.y);

	if (CombatManager::getCombatState() != CombatManager::combatState::move)
		entity->delGroup(Game::groupRange);

}
