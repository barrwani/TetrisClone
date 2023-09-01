
#include "../include/Map.hpp"
#include "../include/Game.hpp"
#include <fstream>
#include <iostream>

extern Manager manager;

Map::Map(std::string tID, int ms, int ts) : texID(tID), mapScale(ms), tileSize(ts)
{
    scaledSize = ms * ts;

}

Map::~Map()
{

}

void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
    char chr;
    std::ifstream mapFile;
    mapFile.open(path);

    int srcX, srcY;

    for(int y = 0; y < sizeY; y++)
    {
        for(int x = 0; x < sizeX; x++)
        {
            mapFile.get(chr);
            srcY = atoi(&chr) * tileSize;
            mapFile.get(chr);
            srcX = atoi(&chr) * tileSize;
            addTile(srcX, srcY, x * scaledSize, y * scaledSize);
            mapFile.ignore();
        }
    }
    mapFile.ignore();

    for(int y = 0; y < sizeY; y++)
    {
        for(int x = 0; x < sizeX; x++)
        {
            mapFile.get(chr);
            if(chr == '1')
            {
                auto& col(manager.addEntity());
                col.addComponent<CollisionComponent>("terrain", x * scaledSize, y * scaledSize, scaledSize);
                col.addGroup(Game::groupColliders);
            }
            mapFile.ignore();
        }
    }
    mapFile.close();
}


void Map::addTile(int srcX, int srcY, int xpos, int ypos)
{
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale, texID);
    tile.addGroup(Game::groupMap);
}
