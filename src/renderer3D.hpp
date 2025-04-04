#pragma once
#include <imgui.h>
#include "OpenGLutils/object/object.hpp"
#include "chessBoard.hpp"
#include "openGl/skybox.hpp"

class Renderer3D {
private:
    std::vector<Object> listOfObjects;
    // Skybox              skybox;

public:
    void render_board(ChessBoard& _chessboard);
    // void render_skybox();

    void setup_obj();
    void draw_obj();
};