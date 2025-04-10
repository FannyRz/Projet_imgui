#include "skybox.hpp"
#include <iostream>
#include "OpenGLutils/object/texture.hpp"
#include "stb_image.h"

void Skybox::setup_skybox()
{
    // Créer le VAO, VBO et EBO
    glGenVertexArrays(1, &_skyboxVAO);
    glGenBuffers(1, &_skyboxVBO);
    glGenBuffers(1, &_skyboxEBO);

    glBindVertexArray(_skyboxVAO);

    // VBO pour les coordonnées des vertices
    glBindBuffer(GL_ARRAY_BUFFER, _skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * _cubemapCoordinates.size(), _cubemapCoordinates.data(), GL_STATIC_DRAW);

    // EBO pour les indices des triangles
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _skyboxEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * _cubemapIndices.size(), _cubemapIndices.data(), GL_STATIC_DRAW);

    // Définir les attributs du vertex (coordonnées)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // Désactiver les buffers pour éviter les erreurs
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
};

void Skybox::setup_shader()
{
    this->_shaderSkybox.load_shader("../../src/openGL/shaders/skybox.vs.glsl", "../../src/openGL/shaders/skybox.fs.glsl");
}

void Skybox::load_cubemap()
{
    glGenTextures(1, &_cubeMapTexture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _cubeMapTexture);

    for (unsigned int i = 0; i < 6; i++)
    {
        int width      = 0;
        int height     = 0;
        int nbChannels = 0;

        unsigned char* imageData = stbi_load(_cubemapFaces[i].c_str(), &width, &height, &nbChannels, 0);

        if (!imageData)
        {
            std::cerr << "La texture ne peut pas etre load" << '\n';
            exit(0);
        }

        stbi_set_flip_vertically_on_load(false);

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
        stbi_image_free(imageData);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}