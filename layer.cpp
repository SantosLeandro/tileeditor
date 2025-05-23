#include "layer.h"
#include "global.h"
#include "level.h"

GameObject::GameObject()
{
}

GameObject::GameObject(std::string name)
{
    this->name = name;
}

GameObject::GameObject(std::string name, int x, int y)
{
    this->name = name;
    this->x = x;
    this->y = y;
}

Layer::Layer()
{
}

Layer::~Layer()
{
}

int Layer::Width()
{
    return data[0].size();
}

int Layer::Height()
{
    return data.size();
}

void Layer::insertTile(int x, int y, int id)
{
    rollback.push_back(data);
    if (rollback.size() > 100)
    {
        rollback.pop_front();
    }
    data[y][x] = id;
}

std::string Layer::getDataStr()
{
    std::string tmp = "";
    for (int i = 0; i < data.size(); i++)
    {
        for (int j = 0; j < data[0].size(); j++)
        {
            tmp += std::to_string(data[i][j]) + ",";
        }
    }
    tmp.pop_back();
    return tmp;
}

void Layer::undo()
{
    if (rollback.size() > 0)
    {
        data = rollback.back();
        rollback.pop_back();
    }
}

void Layer::update(int w, int h, const char *name, const char *texture)
{
    data.resize(h);
    for (int i = 0; i < h; i++)
    {
        data[i].resize(w);
    }
    this->name = name;
    this->texture->filename = texture;
}

void Layer::removeGameObject(int x, int y)
{
    for (size_t i = 0; i < gameObjects.size();)
    {
        int w = TileSelector::sprites[gameObjects[i].name].w;
        int h = TileSelector::sprites[gameObjects[i].name].h;
        if (
            (x >= gameObjects[i].x && x <= (gameObjects[i].x + w)) &&
            (y >= gameObjects[i].y && y <= (gameObjects[i].y + h)))
        {

            gameObjects[i] = std::move(gameObjects.back());
            gameObjects.pop_back();
        }
        else
        {
            ++i;
        }
    }
}

void Layer::copyTiles(int x1, int y1, int x2, int y2, const Level *level)
{
    copyData.clear();
    int endW = x1 / level->tileSize;
    int endH = y1 / level->tileSize;
    int startW = x2 / level->tileSize;
    int startH = y2 / level->tileSize;

    int yv = 0;
    for (int i = y1; i <= endH; i++)
    {
        int xv = 0;
        for (int j = startW; j <= endW; j++)
        {
            if (i >= level->layer[TileSelector::layerId].data.size() || j >= level->layer[TileSelector::layerId].data[0].size())
            {
                continue;
            }
            copyData.push_back(TileBlock(xv * level->tileSize, yv * level->tileSize, level->layer[TileSelector::layerId].data[i][j]));
            xv += 1;
        }
        yv += 1;
    }
}
