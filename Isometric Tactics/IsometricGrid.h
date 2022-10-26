#pragma once
#include <fstream>
#include <vector>
#include <string>
#include "ECS.h"
#include "Components.h"
#include "Vector2D.h"


class IsometricGrid
{
public:
	IsometricGrid(std::string tID, int ms, int ts);
	~IsometricGrid();

	void loadGrid(std::string path, int width, int height);
	void addTile(int srcX, int srcY, int xpos, int ypos, int index, int i, int j);

	void tilePtrs(int width, int mapSize);

	//getters and setters
	int getMapScale() { return mapScale; }
	static int getScaledSize() { return scaledSize; }
	static int getXOffSet() { return xOffSet; }
	static int getMapWidth() { return mapWidth; }
	static int getMapHeight() { return mapHeight; }

	int getTileSize() const { return tileSize; }

	//to do list
	//grid
	//tile map
	//collision map
	//height map

	static void screenFromGrid(Vector2D& screen, Vector2D& grid);
	static void gridFromScreen(Vector2D& grid, Vector2D& screen);


private:
	std::string tileSetID;
	int mapScale;
	int tileSize;
	static int scaledSize;
	static int xOffSet;
	static int mapWidth;
	static int mapHeight;
	std::vector<Entity*> gridTiles;

};