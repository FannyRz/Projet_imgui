#pragma once
#include <imgui.h>
#include "OpenGLutils/TrackBall.hpp"
#include "OpenGLutils/object/object.hpp"
#include "chessBoard.hpp"
#include "openGl/skybox.hpp"
#include "openGL/shaders/shader.hpp"
#include "openGLutils/TrackBall.hpp"

class Renderer3D {
private:
    std::vector<Object> listOfObjects;
    Skybox              _skybox{};
    Shader              _shader{};
    TrackballCamera _trackballCamera{50., 20., 0.};

public:
    void render_board(ChessBoard& _chessboard);
    // void render_skybox();
    Skybox& get_skybox() { return this->_skybox; }

    void setup_obj();
    void setup_shader();
    void button_action();
    void draw_obj();
    void draw_pieces(int x, int y);
};