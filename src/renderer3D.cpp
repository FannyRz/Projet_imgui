#include "renderer3D.hpp"
#include <imgui.h>
#include <cstddef>
#include <iostream>
#include "App.hpp"
#include "chessBoard.hpp"
#include "quick_imgui/quick_imgui.hpp"


void Renderer3D::render_board(ChessBoard& _chessboard)
{
    _chessboard.draw_board();
}