#include "level.h"

Level::Level()
{
    Init();
}

void Level::Init()
{
    layer.push_back(Layer());

    for (int i = 0; i < h; i++)
    {
        layer[0].data.push_back(std::vector<int>());
        for (int j = 0; j < w; j++)
        {
            layer[0].data[i].push_back(2);
        }
    }
}
