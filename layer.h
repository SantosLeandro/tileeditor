#pragma once

#include <string>
#include <vector>
#include <list>
#include "texture.h"

class Level;

class GameObject{
public:
    int x, y;
    std::string name;
    GameObject();
    GameObject(std::string name);
    GameObject(std::string name, int x, int y);
};

typedef std::vector<std::vector<int>> TileData;

class TileBlock {
public:
    int x,y,id;
    TileBlock(){}
    TileBlock(int x, int y, int id){
        this->x = x;
        this->y = y;
        this->id = id;
    }
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
    std::vector<GameObject> gameObjects;
    std::list<TileData> rollback;
    std::list<TileBlock> copyData;
    Texture *texture = nullptr;
    void insertTile(int x, int y, int id);
    std::string getDataStr();
    void undo();
    void copyTiles(int x1, int y1, int x2, int y2, const Level *level);
    void update(int w, int h, const char* name, const char* texture);
    void removeGameObject(int x, int y);
    //TileBlock tileCopy;
};