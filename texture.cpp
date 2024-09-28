#include "texture.h"

#include <iostream>
// Define STB_IMAGE_IMPLEMENTATION before including stb_image.h
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture()
{
    // Generate an OpenGL texture ID
    // glGenTextures(1, &textureID);
}

Texture::~Texture()
{
    glDeleteTextures(1, &textureID);
}

const GLuint Texture::Id()
{
    return textureID;
}

void Texture::LoadFromFile(const char *filename)
{
    this->filename = filename;
    glGenTextures(1, &textureID);

    std::cout<<textureID<<"\n";

    // Bind the texture
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Load image using stb_image
    int width, height, nrChannels;
    unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
    if (data)
    {
        // Determine the image format (e.g., RGB or RGBA)
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;

        w = width;
        h = height;
        // Upload the texture to the GPU
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        //glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture: " << filename << std::endl;
    }

    // Free the image memory
    stbi_image_free(data);
}

int Texture::Width()
{
    return w;
}

int Texture::Height()
{
    return h;
}
