#pragma once

#include <imgui.h>
#include "chessBoard.hpp"

class Renderer3D {
private:
public:
    void render_board(ChessBoard& _chessboard);
};