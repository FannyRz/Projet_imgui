#pragma once
#include <imgui.h>
#include <array>
#include <cstddef>
#include <iostream>
#include <memory>
#include <optional>
#include <pieces.hpp>
#include "quick_imgui/quick_imgui.hpp"

struct SelectedPiece {
    Piece*                           piece;
    int                              position_x;
    int                              position_y;
    std::vector<std::pair<int, int>> all_possible_move{}; //->pour savoir les déplacements possibles
};

class ChessBoard {
private:
    std::array<std::array<std::unique_ptr<Piece>, 8>, 8> position_pieces{}; // tableau de positions initiales des pièces.
    std::optional<SelectedPiece>                         _selected;

public:
    ImFont* font;
    void    draw_board();
    void    set_position();
    void    select(int x, int y);
    void    deselect();
};

//_selected.has_value()