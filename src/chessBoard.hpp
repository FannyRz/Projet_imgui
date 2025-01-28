#pragma once
#include <imgui.h>
#include <cstddef>
#include <iostream>
#include "quick_imgui/quick_imgui.hpp"

class ChessBoard {
private:
public:
    ImFont* font;
    void    draw_board();
};