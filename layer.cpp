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

std::string Layer::getDataStr()
{
    std::string tmp = "";
    for(int i = 0; i < data.size(); i++){
        for(int j = 0; j < data[0].size(); j++){
            tmp += std::to_string(data[i][j])+",";
        }
    }
    tmp.pop_back();
    return tmp;
}
