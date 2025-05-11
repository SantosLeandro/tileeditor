#pragma once

#include <vector>
#include "layer.h"

class Level
{
public:
    unsigned int w = 10;
    unsigned int h = 5;
    int tileSize = 16;
    std::string name;
    std::vector<Layer> layer;
    std::string options;
    Level();
    void Init();
};