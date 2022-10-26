#include "AssetManager.h"

std::map<std::string, SDL_Texture*> AssetManager::textures;


AssetManager::AssetManager()
{}
AssetManager::~AssetManager()
{}

void AssetManager::addTexture(std::string id, const char* path)
{
	textures.emplace(id, TextureManager::loadTexture(path));
}

SDL_Texture* AssetManager::getTexture(std::string id)
{
	return textures[id];
}