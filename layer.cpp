#include "layer.h"

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

void Layer::InsertTile(int x, int y, int id)
{
    data[y][x] = id;
}
