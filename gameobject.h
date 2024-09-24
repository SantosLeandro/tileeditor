#pragma once
#include <string>

struct Sprite
{
    int x,y,w,h;
};


class GameObject
{

public:
    int x,y;
    int w,h;
    Sprite sprite;
    std::string name;
};