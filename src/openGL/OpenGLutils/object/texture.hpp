#pragma once

#include <glad/glad.h>
#include <glfw/src/internal.h>
#include <iostream>
#include <string>
#include "../../../openGL/stb_image.h"

class Texture {
private:
    GLuint _texture{};

public:
    Texture() = default;
    Texture(const std::string& path)
    {
        glGenTextures(1, &_texture);
        glBindTexture(GL_TEXTURE_2D, _texture);

        int            width{};
        int            height{};
        int            nrChannels{};
        unsigned char* data =
            stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            stbi_set_flip_vertically_on_load(false);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Failed to load texture: " << path << '\n';
            stbi_image_free(data);
        }

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);
    };
    ~Texture() { glDeleteTextures(1, &_texture); };
};