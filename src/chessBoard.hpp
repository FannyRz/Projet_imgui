#pragma once
#include <imgui.h>
#include <cstddef>
#include <iostream>
#include <memory>
#include <optional>
#include <pieces.hpp>
#include "quick_imgui/quick_imgui.hpp"

inline std::vector<std::vector<std::unique_ptr<Piece>>> position_pieces [8][8]; // tableau de positions initiales des pièces.

void set_position(std::vector<std::vector<Piece>>& position_pieces);

struct SelectedPiece {
    std::unique_ptr<Piece>           piece;
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