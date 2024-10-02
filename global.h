#pragma once
#include <string>
#include <vector>
#include "layer.h"


class TileSelector
{
    public:
    static void registerGameObject(GameObject o);
    static int tileId;
    static int tileSize;
    static int layerId;
    static std::string tileset;
    static std::vector<GameObject> gameObjects;
    
};

