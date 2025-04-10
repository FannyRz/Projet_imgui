#pragma once

#include <GLFW/glfw3.h>
#include <string>
#include <utility>
#include <vector>
#include "glm/ext/vector_float2.hpp"
#include "glm/ext/vector_float3.hpp"

class Vertex {
public:
    glm::vec3 _position;
    glm::vec3 _normal;
    glm::vec2 _texCoord;
};

class ObjLoader {
private:
    std::string _path;

public:
    ObjLoader() = default;
    explicit ObjLoader(std::string p)
        : _path(std::move(p)) {}
    ~ObjLoader() = default;

    std::vector<Vertex> loaderObj();
};