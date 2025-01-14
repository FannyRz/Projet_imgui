#pragma once

#include <imgui.h>
#include <cstddef>
#include <iostream>
#include "chessBoard.hpp"
#include "quick_imgui/quick_imgui.hpp"

class App {
private:
    ChessBoard _chessboard{};

public:
    void update()
    {
        _chessboard.draw_board();
    }
};