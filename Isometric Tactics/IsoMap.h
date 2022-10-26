#pragma once
#include <string>


struct IsoMap
{
	IsoMap(std::string tsID, int ms, int ts, std::string path, int width, int height) : tileSet(tsID)
	{
		mapScale = ms;
		tileSize = ts;
		mapPath = path;
		mapWidth = width;
		mapHeight = height;
	}

	~IsoMap() {};

	std::string tileSet;
	int mapScale;
	int tileSize;
	std::string mapPath;
	int mapWidth;
	int mapHeight;


};