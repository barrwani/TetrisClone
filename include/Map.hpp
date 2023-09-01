#ifndef BARWANIENGINE_MAP_HPP
#define BARWANIENGINE_MAP_HPP
#include <string>
#include "Components.hpp"
#include "Game.hpp"
#include "ECS.hpp"


class Map {
public:
    Map(std::string tID, int ms, int ts);
    ~Map();

    void LoadMap(std::string path, int sizeX, int sizeY);
    void addTile(int srcX, int srcY, int xpos, int ypos);

private:
    std::string texID;
    int mapScale;
    int tileSize;
    int scaledSize;

};


#endif //BARWANIENGINE_MAP_HPP
