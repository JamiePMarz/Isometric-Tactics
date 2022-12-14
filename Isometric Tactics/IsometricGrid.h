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

	void loadGrid(std::string path);
	void addTile(int srcX, int srcY, int xpos, int ypos, int index, int i, int j);

	void tilePtrs(int width, int mapSize);

	//getters and setters

	static void screenFromGrid(Vector2D& screen, Vector2D& grid);
	static void gridFromScreen(Vector2D& grid, Vector2D& screen);
	//static void gridFromScreen(Vector2D& grid, Vector2D& screen, int height);
	static Vector2D& gridFromScreen(Vector2D& grid, Vector2D& screen, int height);

	static const std::vector<Entity*> getGridTiles() { return gridTiles; }

	static int getScaledSize() { return scaledSize; }
	//public vars

private:
	std::string tileSetID;
	int mapScale;
	int tileSize;
	static int scaledSize;
	static int xOffSet;
	static int yOffSet;
	int mapWidth;
	int mapHeight;
	static std::vector<Entity*> gridTiles;

};