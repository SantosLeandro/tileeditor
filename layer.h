#pragma once

#include <string>
#include <vector>
#include "texture.h"

class GameObject{
public:
    int x, y;
    std::string name;
    GameObject();
    GameObject(std::string name);
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
    Texture *texture = nullptr;
    void InsertTile(int x, int y, int id);
    std::string getDataStr();
};