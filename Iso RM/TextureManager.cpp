#include "TextureManager.h"


SDL_Texture* TextureManager::loadTexture(const char* aTexture)
{
	SDL_Surface* tempSurface = IMG_Load(aTexture);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(WindowManager::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return texture;
}

void TextureManager::drawTexture(SDL_Texture* aTexture, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(WindowManager::renderer, aTexture, &src, &dest, NULL/*angle*/, NULL/*rotate*/, flip);
}

void TextureManager::drawTileTextures(std::string aTexture, SDL_Rect dest)
{
	SDL_RenderCopy(WindowManager::renderer, AssetManager::getTexture(aTexture), NULL, &dest);
}

