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


void AssetManager::createMapAsset(const char* tsPath, int scale, std::string mapPath, std::string mapKey)
{
	std::cout << mapKey << std::endl;
	addTexture(mapKey, tsPath);

	int width, height, tileSize;
	std::string temp;

	std::fstream mapFile;
	mapFile.open(mapPath, std::ios::in);

	std::getline(mapFile, temp, 'x');
	width = stoi(temp);
	std::getline(mapFile, temp);
	height = stoi(temp);

	std::cout << width << "x" << height << std::endl;

	std::getline(mapFile, temp);
	tileSize = stoi(temp);
	std::cout << tileSize << std::endl << std::endl;

	mapFile.close();

	IsoMap* map = new IsoMap(mapKey, scale, tileSize, mapPath, width, height);
	addIsoMap(mapKey, map);
}
