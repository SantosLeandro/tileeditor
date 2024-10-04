#pragma once
#include <string>

class Sprite{
public:
    int x, y, w, h;
    Sprite();
    Sprite(int x, int y, int w, int h);
    std::string toString();
};
