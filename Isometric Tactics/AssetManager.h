#pragma once
#include <map>
#include <string>
#include <SDL.h>
#include "TextureManager.h"
#include "IsoMap.h"


class AssetManager
{
public:
	AssetManager();
	~AssetManager();

	//void insertMap(std::string name, const char* tsPath, int width, int height, int scale)
	//{
	//	addTexture(name + "_ts", tsPath);
	//	IsoMap* map = new IsoMap(name + "_ts", scale, 32, "Assets/" + name + "_" + char(width) + "x" + char(height) + ".map", width, height);
	//	addIsoMap(name, map);
	//}


	void addTexture(std::string id, const char* path);
	void addIsoMap(std::string id, IsoMap* isoMap);

	static SDL_Texture* getTexture(std::string id);
	static IsoMap* getIsoMap(std::string id);

private:
	static std::map<std::string, SDL_Texture*> textures;
	static std::map<std::string, IsoMap*> isoMaps;

};

