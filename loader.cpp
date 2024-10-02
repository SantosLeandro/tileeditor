#include "loader.h"
#include "texture.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream> 
#include <unordered_map>
#include <vector>
#include <string>

using json = nlohmann::ordered_json;

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
    //level->layer.resize(jLayers.size());
    level->layer.clear();
    for (const auto &layer : jLayers)
    {
        level->layer.push_back(Layer());
        int index = level->layer.size() - 1;
        level->layer[index].name = layer["name"].get<std::string>();
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

    //std::cout << root.dump() << "\n";

    return level;
}

bool SaveLevel(Level *level, const char *filename)
{
    json root;
    root["tilesize"] = level->tileSize;
    root["width"] = level->w;
    root["height"] = level->h;
    root["name"] = level->name;
    for(int i=0; i < level->layer.size();i++){
        root["layer"][i]["name"] = level->layer[i].name;
        root["layer"][i]["width"] = level->layer[i].Width();
        root["layer"][i]["height"] = level->layer[i].Height();
        root["layer"][i]["texture"] = level->layer[i].texture->filename;
        root["layer"][i]["data"] = level->layer[i].getDataStr();
    }

    std::ofstream file(filename);

    // Check if the file opened successfully
    if (!file) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    // Write the JSON object to the file
    file << root.dump(2);  // '4' means pretty print with 4 spaces for indentation

    // Close the file
    file.close();

    return false;
}

Level *LoadLevelFile(const char *filename)
{
    std::ifstream file(filename);
    std::string str;
    std::string levelName;
    std::string layerName;
    std::string textureName;
    int lw, lh;
    int w, h, tileSize;
    std::getline(file, str);
    if(str != "levelmap"){
        return nullptr;
    }
    while (std::getline(file, str))
    {
       if(str == "#levelname"){
            std::getline(file, levelName);
       } else if (str == "#leveldefs"){
            //Get level w h tileSize
            std::getline(file, str,' ');
            w = std::stoi(str);
            std::getline(file, str,' ');
            h = std::stoi(str);
            std::getline(file, str,' ');
            tileSize = std::stoi(str);
       } else if (str == "#layer") {
            std::getline(file, str,' ');
            layerName = str;
            std::getline(file, str,' ');
            lw = std::stoi(str);
            std::getline(file, str,' ');
            lh = std::stoi(str);
            std::getline(file, str,' ');
            textureName = str;
       }
    }
    DebugVal("level Name",levelName.c_str());
    DebugVal("w",w);
    DebugVal("h",h);
    DebugVal("tileSize",tileSize);
    DebugVal("layerName",layerName.c_str());
    DebugVal("lw",lw);
    DebugVal("lh",lh);
    DebugVal("texture",textureName.c_str());

    
    return nullptr;
}

void DebugVal(const char *n, int v)
{
    std::cout<<n<<": "<<v<<"\n"; 
}

void DebugVal(const char *n, float v)
{
    std::cout<<n<<": "<<v<<"\n"; 
}

void DebugVal(const char *n, const char* v)
{
   std::cout<<n<<": "<<v<<"\n"; 
}
