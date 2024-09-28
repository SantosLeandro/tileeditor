#pragma once

#include <GL/gl.h>
#include <string>

class Texture
{
protected:
    int w, h;
    GLuint textureID;
public:
    Texture();
    ~Texture();
    const GLuint Id();
    void LoadFromFile(const char* name);
    int Width();
    int Height();
    std::string filename;
};