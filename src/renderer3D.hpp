#pragma once
#include <imgui.h>
#include "OpenGLutils/TrackBall.hpp"
#include "OpenGLutils/object/object.hpp"
#include "chessBoard.hpp"
#include "openGL/shaders/shader.hpp"
#include "openGLutils/TrackBall.hpp"
#include "openGl/skybox.hpp"

class Renderer3D {
private:
    std::vector<Object> listOfObjects;
    Skybox              _skybox{};
    Shader              _shader{};
    TrackballCamera     _trackballCamera{50., 20., 0.};

public:
    void             render_board(ChessBoard& _chessboard);
    void             render_skybox();
    Skybox&          get_skybox() { return this->_skybox; }
    TrackballCamera& get_camera() { return this->_trackballCamera; };

    void setup_obj();
    void setup_shader();
    void button_action();
    void draw_obj();
    void draw_chessboard();
    int  from_type_to_obj(PieceType type);
    void draw_pieces(std::array<std::array<std::unique_ptr<Piece>, 8>, 8>* position_pieces);
};