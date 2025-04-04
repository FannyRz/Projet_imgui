#pragma once
#include <imgui.h>
#include <array>
#include <string>
#include "OpenGLutils/object/object.hpp"
#include "shaders/ShaderLoader.hpp"

class Skybox {
private:
    unsigned int cubeMapTexture{};

    std::array<GLfloat, 24> cubemapCoordinates{
        -1.f,
        -1.f,
        1.f,
        1.f,
        -1.f,
        1.f,
        1.f,
        -1.f,
        -1.f,
        -1.f,
        -1.f,
        -1.f,
        -1.f,
        1.f,
        1.f,
        1.f,
        1.f,
        1.f,
        1.f,
        1.f,
        -1.f,
        -1.f,
        1.f,
        -1.f,
    };

    std::array<unsigned int, 36> cubemapIndices{
        // right
        1, 2, 6,
        6, 5, 1,
        // left
        0, 4, 7,
        7, 3, 0,
        // top
        4, 5, 6,
        6, 7, 4,
        // bottom
        0, 3, 2,
        2, 1, 0,
        // back
        0, 1, 5,
        5, 4, 0,
        // front
        3, 7, 6,
        6, 2, 3
    };

    std::array<std::string, 6> cubemapFaces{
        "../../assets/texture/skybox/right.png",
        "../../assets/texture/skybox/left.png",
        "../../assets/texture/skybox/top.png",
        "../../assets/texture/skybox/bottom.png",
        "../../assets/texture/skybox/back.png",
        "../../assets/texture/skybox/front.png",
    };

    unsigned int skyboxVAO;
    unsigned int skyboxVBO;
    unsigned int skyboxEBO;

    ShaderLoader shaderLoader;  // Ajout du gestionnaire de shader

public:
    Skybox() = default;

    void setup_skybox();
    void load_cubemap();
    // void draw_skybox(const glm::mat4& projection, const glm::mat4& view);
};