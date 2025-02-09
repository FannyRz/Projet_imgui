#include "renderer3D.hpp"
#include <imgui.h>
#include "chessBoard.hpp"


void Renderer3D::render_board(ChessBoard& _chessboard)
{
    _chessboard.draw_board();
}