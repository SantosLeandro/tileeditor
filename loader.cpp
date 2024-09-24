#include "loader.h"
#include "texture.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream> 

using json = nlohmann::json;

Level *LoadLevel(const char *filename)
{
    Level *level = new Level();

    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return nullptr;
    }

    json root;
    file >> root;

    level->name = root["name"].get<std::string>();
    level->w = root["width"].get<int>();
    level->h = root["height"].get<int>();

    const json &jLayers = root["layer"];

    for (const auto &layer : jLayers)
    {
        level->layer.push_back(Layer());
        int index = level->layer.size() - 1;
        std::string name = layer["name"].get<std::string>();
        int width = layer["width"].get<int>();
        int height = layer["height"].get<int>();

        std::string textureFilename = layer["texture"].get<std::string>();

        level->layer[index].texture = new Texture();
        level->layer[index].texture->LoadFromFile(textureFilename.c_str());
        
        std::string eData = layer["data"].get<std::string>();
        std::stringstream ss(eData);
        std::string token;
        std::vector<std::string> temp;
        while (std::getline(ss, token, ','))
        {
            temp.push_back(token);
        }

        for (int i = 0; i < height; i++)
        {
            level->layer[index].data.push_back(std::vector<int>());
            for (int j = 0; j < width; j++)
            {
                level->layer[index].data[i].push_back(std::stoi(temp[(i * width) + j]));
            }
        }
    }

    std::cout << root.dump() << "\n";

    return level;
}