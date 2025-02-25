#include "pieces.hpp"
#include <imgui.h>

bool Piece::isOnTheChessboard(int x, int y)
{
    return x < 8 && x >= 0 && y < 8 && y >= 0;
}