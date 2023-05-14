#include "Map.h"
#include "Game.h"
#include <fstream>
#include "ECS/Ecs.h"
#include "ECS/Components.h"

extern Manager manager;


Map::Map(std::string tID, int ms, int ts):texID(tID),mapScale(ms),tileSize(ts)
{
	scaledSize = ms * ts;

}

Map::~Map() {
	
}

void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
	char tile;
	std::fstream mapFile;
	mapFile.open(path);

	int srcX, srcY;


	for (int y = 0;y < sizeY;y++)
	{
		for (int x = 0;x < sizeX;x++)
		{
			mapFile.get(tile);
			srcY = atoi(&tile) * tileSize;
			mapFile.get(tile);
			srcX = atoi(&tile) * tileSize;
			ADDTile(srcX, srcY, x * scaledSize, y * scaledSize);
			mapFile.ignore();

		}

	}

	mapFile.ignore();

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(tile);

			if (tile == '1')
			{
				auto& tcol(manager.addEntity());
				tcol.addComponent<ColliderComponent>("terrain",x * scaledSize,y * scaledSize,scaledSize);
				tcol.addGroup(Game::groupColliders);
			}
			mapFile.ignore();


		}

	}


	mapFile.close();

}

void Map::ADDTile(int srcX, int srcY, int xpos, int ypos) {
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos,tileSize,mapScale,texID);
	tile.addGroup(Game::groupMap);
}