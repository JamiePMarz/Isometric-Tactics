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


void AssetManager::createMapAsset(const char* tsPath, int scale, int tileSize, std::string mapPath, int width, int height, std::string mapKey)
{
	std::string tileSet;
	addTexture(tileSet, tsPath);
	IsoMap* map = new IsoMap(tileSet, scale, tileSize, mapPath, width, height);
	addIsoMap(mapKey, map);
}