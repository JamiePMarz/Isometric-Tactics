#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "WindowManager.h"
#include "Game.h"


class TextureManager
{
public:

	static SDL_Texture* loadTexture(const char* aTexture);
	static void drawTexture(SDL_Texture* aTexture, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip);

	static void drawTileTextures(std::string aTexture, SDL_Rect dest);


private:


};