#pragma once
#include <imgui.h>
#include "OpenGLutils/object/object.hpp"
#include "chessBoard.hpp"


class Renderer3D {
private:
    std::vector<Object> listOfObjects;

public:
    void render_board(ChessBoard& _chessboard);
};