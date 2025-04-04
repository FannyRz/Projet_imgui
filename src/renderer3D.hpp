#pragma once
#include <imgui.h>
#include "OpenGLutils/object/object.hpp"
#include "chessBoard.hpp"
#include "openGl/skybox.hpp"

class Renderer3D {
private:
    std::vector<Object> listOfObjects;
    Skybox                         _skybox{};
    

public:
    void render_board(ChessBoard& _chessboard);
    // void render_skybox();
    Skybox& get_skybox(){ return this->_skybox; }

    void setup_obj();
    void draw_obj();
    void draw_pieces(int x, int y);
};