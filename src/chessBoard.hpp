#pragma once
#include <imgui.h>
#include <cstddef>
#include <iostream>
#include <optional>
#include <pieces.hpp>
#include "quick_imgui/quick_imgui.hpp"

struct SelectedPiece {
    Piece*                           piece;
    int                              color;
    int                              position_x;
    int                              position_y;
    std::vector<std::pair<int, int>> all_possible_move{}; //->pour savoir les déplacements possibles
};

class ChessBoard {
private:
    std::optional<SelectedPiece> _selected;

public:
    ImFont* font;
    void    draw_board();
    void    deselect();
    void    select(int x, int y);
};

//_selected.has_value()