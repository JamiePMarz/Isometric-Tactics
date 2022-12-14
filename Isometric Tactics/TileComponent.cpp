#include "TileComponent.h"


TileComponent::TileComponent(int srcX, int srcY, int xpos, int ypos, int tileSize, int scale, std::string aTexture, int index, int i, int j)
{
	//LOG("tile created");
	texture = AssetManager::getTexture(aTexture);

	src.x = srcX;
	src.y = srcY;
	src.w = src.h = tileSize;
	screen.x = xpos;
	screen.y = ypos;
	grid.x = i;
	grid.y = j;

	dest.w = dest.h = tileSize * scale;

	gridIndex = index;

	if (src.x == 0 && src.y == 0) {
		selectable = false;
		blocked = true;
	}
}

TileComponent::~TileComponent()
{
	//LOG("tile destroyed");
}

void TileComponent::draw()
{
	TextureManager::drawTexture(texture, src, dest, SDL_FLIP_NONE);

	//within range
	if (entity->hasGroup(EntityManager::groupRange))
		TextureManager::drawTileTextures("tile_highlighted", dest);

	//path
	if (entity->hasGroup(EntityManager::groupPath))
		TextureManager::drawTileTextures("tile_highlighted", dest);

	//placement indicator
	if (placeHere)
		TextureManager::drawTileTextures("tile_cusor", dest);

	if (Keyboard_Mouse::hover(grid, height) && selectable)
		TextureManager::drawTileTextures("tile_cusor", dest);

#if MY_DEBUG == 1
	//blocked indicator
	if (blocked)
		TextureManager::drawTileTextures("collider", dest);
#endif
}


void TileComponent::update()
{
	//position
	dest.x = static_cast<int>(screen.x);
	dest.y = static_cast<int>(screen.y);

	if (CombatManager::getCombatState() != CombatManager::move)
		entity->delGroup(EntityManager::groupRange);
}

void TileComponent::addHeight(int aHeight, int scaledSize)
{
	height = aHeight; 
	screen.y -= (scaledSize / 4 * height);
}