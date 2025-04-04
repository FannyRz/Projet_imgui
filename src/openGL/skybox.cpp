#include "skybox.hpp"
#include <iostream>
#include "OpenGLutils/object/texture.hpp"
#include "stb_image.h"

void Skybox::setup_skybox()
{
    // Créer le VAO, VBO et EBO
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glGenBuffers(1, &skyboxEBO);

    glBindVertexArray(skyboxVAO);

    // VBO pour les coordonnées des vertices
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubemapCoordinates), cubemapCoordinates.data(), GL_STATIC_DRAW);

    // EBO pour les indices des triangles
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubemapIndices), cubemapIndices.data(), GL_STATIC_DRAW);

    // Définir les attributs du vertex (coordonnées)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // Désactiver les buffers pour éviter les erreurs
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
};

void Skybox::setup_shader()
{
    this->shader_skybox.load_shader("shaders/skybox.vs.glsl", "shaders/skybox.fs.glsl");
}

void Skybox::load_cubemap()
{
    glGenTextures(1, &cubeMapTexture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTexture);

    for (unsigned int i = 0; i < cubemapFaces.size(); i++)
    {
        int width      = 0;
        int heigh      = 0;
        int nbChannels = 0;

        unsigned char* imageData = stbi_load(cubemapFaces[i].c_str(), &width, &heigh, &nbChannels, 0);

        if (!imageData)
        {
            std::cerr << "La texture ne peut pas etre load" << '\n';
            exit(0);
        }

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        // stbi_set_flip_vertically_on_load(false);

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, heigh, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
        stbi_image_free(imageData);
    }
}

void Skybox::draw_skybox(const glm::mat4& projection, const glm::mat4& view)
{
    // Utiliser le shader
    this->shader_skybox.use();

    // Ne pas modifier la position de la caméra pour la skybox (supprimer la translation de la vue)
    glm::mat4 viewNoTranslation = glm::mat4(glm::mat3(view)); // Supprimer la translation de la vue

    // Lier la texture de la cubemap
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTexture);

    // Activer le VAO de la skybox
    glBindVertexArray(skyboxVAO);

    // Dessiner la skybox
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(cubemapIndices.size()), GL_UNSIGNED_INT, 0);

    // Désactiver le VAO
    glBindVertexArray(0);
}