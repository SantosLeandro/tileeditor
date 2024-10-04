#pragma once

#include <string>
#include <vector>
#include <list>
#include "texture.h"

class GameObject{
public:
    int x, y;
    std::string name;
    GameObject();
    GameObject(std::string name);
};

typedef std::vector<std::vector<int>> TileData;

class TileBlock {
    public:
    std::vector<int> tiles;
    int w,h;
    int layerId;
};

class Layer
{
public:
    Layer();
    ~Layer();
    int Width();
    int Height();
    std::string name;
    std::vector<std::vector<int>> data;
    std::list<TileData> rollback;
    Texture *texture = nullptr;
    void insertTile(int x, int y, int id);
    std::string getDataStr();
    void undo();
    void copyTiles(int x1, int y1, int x2, int y2);
    void update(int w, int h, const char* name, const char* texture); 
    TileBlock tileCopy;
};