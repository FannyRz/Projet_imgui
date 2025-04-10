#pragma once
#include <string>
#include "texture.hpp"
#include "vertexUtils.hpp"

class Object {
private:
    VAO     _vao;
    Texture _texture;

public:
    Object()  = default;
    ~Object() = default;

    VAO*     getVAO() { return &_vao; }
    Texture* getTexture() { return &_texture; }

    void obj_loader(std::string const& path_texture, std::string const& path_obj)
    {
        _vao.init_vao(path_obj);
        _texture = Texture(path_texture);
    }
};
