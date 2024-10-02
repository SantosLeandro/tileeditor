#include "global.h"



void TileSelector::registerGameObject(GameObject o)
{
    gameObjects.push_back(o);
}


int TileSelector::tileId = 0;
int TileSelector::tileSize = 8;
int TileSelector::layerId = 0;
std::string tileset = "";
std::vector<GameObject> TileSelector::gameObjects = std::vector<GameObject>();

