#pragma once
#include <imgui.h>
#include <array>
#include <string>
#include "shaders/shader.hpp"

class Skybox {
private:
    unsigned int _cubeMapTexture{};

    std::array<GLfloat, 24> _cubemapCoordinates{
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

    std::array<unsigned int, 36> _cubemapIndices{
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

    std::array<std::string, 6> _cubemapFaces{
        "../../assets/texture/skybox/right.png",
        "../../assets/texture/skybox/left.png",
        "../../assets/texture/skybox/top.png",
        "../../assets/texture/skybox/bottom.png",
        "../../assets/texture/skybox/back.png",
        "../../assets/texture/skybox/front.png"
    };

    unsigned int _skyboxVAO;
    unsigned int _skyboxVBO;
    unsigned int _skyboxEBO;

    Shader _shaderSkybox;

public:
    Skybox() = default;

    void    setup_skybox();
    void    setup_shader();
    Shader* get_shader_skybox() { return &this->_shaderSkybox; };

    unsigned int get_VAO_skybox() const { return this->_skyboxVAO; };
    unsigned int get_texture_skybox() const { return this->_cubeMapTexture; };

    void load_cubemap();
};