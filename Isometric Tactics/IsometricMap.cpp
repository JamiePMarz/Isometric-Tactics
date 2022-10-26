#include "IsometricMap.h"

extern EntityManager entityManager;
int IsometricMap::scaledSize;
int IsometricMap::xOffSet;
int IsometricMap::mapWidth;
int IsometricMap::mapHeight;


IsometricMap::IsometricMap(std::string tID, int ms, int ts) : tileSetID(tID), mapScale(ms), tileSize(ts)
{
	scaledSize = ms * ts;
	Vector2D::scaledSize = scaledSize;
	Vector2D::scale = mapScale;
}

IsometricMap::~IsometricMap()
{}

void IsometricMap::loadMap(std::string path, int width, int height)
{
	char c;
	std::fstream mapFile;
	mapFile.open(path);

	mapWidth = width;
	mapHeight = height;
	int mapSize = mapWidth * mapHeight;
	xOffSet = ((mapWidth / 2) + (mapHeight / 4)) * (scaledSize / 2) + scaledSize;
	Vector2D::mapXOffSet = xOffSet;

	grid.clear();
	grid.resize(mapSize);

	int srcX, srcY, xpos, ypos;
	int index = 0;

	for (int j = 0; j < mapHeight; j++)
	{
		for (int i = 0; i < mapWidth; i++)
		{
			mapFile.get(c);
			srcY = atoi(&c) * tileSize;
			mapFile.get(c);
			srcX = atoi(&c) * tileSize;
			xpos = (i - j) * (scaledSize / 2) - scaledSize / 2 + xOffSet;
			ypos = (i + j) * (scaledSize / 4);

			addTile(srcX, srcY, xpos, ypos, index, i, j);
			index++;
			mapFile.ignore();
		}
	}

	tilePtrs(mapWidth, mapSize);

	mapFile.close();
}

void IsometricMap::addTile(int srcX, int srcY, int xpos, int ypos, int index, int i, int j)
{
	auto& tile(entityManager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale, tileSetID, index, i, j);
	tile.getComponent<TileComponent>().entity = &tile;
	grid[index] = &tile;
	tile.addGroup(Game::groupTiles);
}


void IsometricMap::tilePtrs(int width, int mapSize)
{
	for (auto& t : grid)
	{
		int index = t->getComponent<TileComponent>().gridIndex;


		if ((index + 1) % width != 0)
			t->getComponent<TileComponent>().right = grid[index + 1];

		if (index < mapSize - width)
			t->getComponent<TileComponent>().down = grid[index + width];
		
		if (index != 0 || index % width != 0)
			t->getComponent<TileComponent>().left = grid[index - 1];

		if (index >= width)
			t->getComponent<TileComponent>().up = grid[index - width];

	}
}