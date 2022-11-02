#include "AssetManager.h"

std::map<std::string, SDL_Texture*> AssetManager::textures;
std::map<std::string, IsoMap*> AssetManager::isoMaps;


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

void AssetManager::addIsoMap(std::string id, IsoMap* isoMap)
{
	isoMaps.emplace(id, isoMap);
}

IsoMap* AssetManager::getIsoMap(std::string id)
{
	return isoMaps[id];
}

