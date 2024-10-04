#include "global.h"



void TileSelector::registerGameObject(GameObject o)
{
    gameObjects.push_back(o);
}

void TileSelector::Release()
{
}

int TileSelector::tileId = 0;
int TileSelector::tileSize = 8;
int TileSelector::layerId = 0;
std::string tileset = "";
Texture* TileSelector::goTex = nullptr;
std::vector<GameObject> TileSelector::gameObjects = std::vector<GameObject>();
std::unordered_map<std::string, Sprite> TileSelector::sprites;

