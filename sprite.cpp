
#include "sprite.h"

Sprite::Sprite()
{
    x = 0;
    y = 0;
    w = 16;
    h = 16;
}

Sprite::Sprite(int x, int y, int w, int h)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

std::string Sprite::toString()
{
    return std::string();
}
