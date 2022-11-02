#include "IsometricGrid.h"

extern EntityManager entityManager;
int IsometricGrid::scaledSize;
int IsometricGrid::xOffSet;
std::vector<Entity*> IsometricGrid::gridTiles;


IsometricGrid::IsometricGrid(std::string tID, int ms, int ts) : tileSetID(tID), mapScale(ms), tileSize(ts)
{
	//std::cout << "grid created\n";
	scaledSize = ms * ts;
}

IsometricGrid::~IsometricGrid()
{
	//std::cout << "grid destroyed\n";
}

void IsometricGrid::loadGrid(std::string path)
{
	std::cout << "loading grid\n";
	char c;
	std::string temp;
	std::fstream mapFile;
	mapFile.open(path, std::ios::in);

	//getting dimensions
	std::getline(mapFile, temp, ',');
	mapWidth = stoi(temp);
	std::getline(mapFile, temp);
	mapHeight = stoi(temp);
	mapFile.ignore();

	int mapSize = mapWidth * mapHeight;
	xOffSet = ((mapWidth / 2) + (mapHeight / 4)) * (scaledSize / 2) + scaledSize;

	gridTiles.clear();
	gridTiles.resize(mapSize);

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

	mapFile.ignore();
	index = 0;

	for (int k = 0; k < mapHeight; k++)
	{
		for (int l = 0; l < mapWidth; l++)
		{
			mapFile.get(c);
			if (c == 'p')
			{
				gridTiles[index]->getComponent<TileComponent>().placeHere = true;
				std::cout << gridTiles[index]->getComponent<TileComponent>().getGridPosition() << std::endl;
			}
			index++;
			mapFile.ignore();
		}
	}












	tilePtrs(mapWidth, mapSize);

	mapFile.close();
}

void IsometricGrid::addTile(int srcX, int srcY, int xpos, int ypos, int index, int i, int j)
{
	auto& tile(entityManager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale, tileSetID, index, i, j);
	tile.getComponent<TileComponent>().entity = &tile;
	gridTiles[index] = &tile;
	tile.addGroup(Game::groupTiles);
}


void IsometricGrid::tilePtrs(int width, int mapSize)
{
	for (auto& t : gridTiles)
	{
		int index = t->getComponent<TileComponent>().gridIndex;


		if ((index + 1) % width != 0)
			t->getComponent<TileComponent>().right = gridTiles[index + 1];

		if (index < mapSize - width)
			t->getComponent<TileComponent>().down = gridTiles[index + width];
		
		if (index != 0 || index % width != 0)
			t->getComponent<TileComponent>().left = gridTiles[index - 1];

		if (index >= width)
			t->getComponent<TileComponent>().up = gridTiles[index - width];

	}
}



void IsometricGrid::screenFromGrid(Vector2D& screen, Vector2D& grid)
{
	screen.x = (grid.x - grid.y) * (scaledSize / 2) - (scaledSize / 2) + xOffSet;
	screen.y = (grid.x + grid.y) * (scaledSize / 4) - (scaledSize / 2);
}


void IsometricGrid::gridFromScreen(Vector2D& grid, Vector2D& screen)
{
	grid.x = std::floor(((screen.x - xOffSet) / (scaledSize / 2) + screen.y / (scaledSize / 4)) / 2);
	grid.y = std::floor((screen.y / (scaledSize / 4) - (screen.x - xOffSet) / (scaledSize / 2)) / 2);
}//BOOOM FIXED!!!


