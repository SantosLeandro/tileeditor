#pragma once

#include "layer.h"
#include "sprite.h"
#include "texture.h"

#include <string>
#include <vector>
#include <unordered_map>

class TileSelector
{
    public:
    static void registerGameObject(GameObject o);
    static int tileId;
    static int tileSize;
    static int layerId;
    static Texture* goTex;
    static std::string tileset;
    static std::vector<GameObject> gameObjects;
    static std::unordered_map<std::string, Sprite> sprites;
    
};

