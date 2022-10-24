#pragma once
#include <map>
#include <string>
#include <SDL.h>
#include "TextureManager.h"


class AssetManager
{
public:
	AssetManager();
	~AssetManager();

	void addTexture(std::string id, const char* path);
	static SDL_Texture* getTexture(std::string id);

private:
	static std::map<std::string, SDL_Texture*> textures;

};

