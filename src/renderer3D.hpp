#pragma once

#include <imgui.h>
#include <cstddef>
#include <iostream>
#include "chessBoard.hpp"
#include "quick_imgui/quick_imgui.hpp"

class Renderer3D {
private:
public:
    void render_board(ChessBoard& _chessboard);
};