#pragma once
#include <imgui.h>
#include <array>
#include <cstddef>
#include <filesystem>
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
    ImFont*                                              font;
    char                                                 character;

public:
    void                             set_font(ImFont* font);
    ImFont*                          get_font() const;
    char                             get_char() const { return this->character; };
    std::vector<std::pair<int, int>> get_all_possible_move() { return _selected.has_value() ? _selected->all_possible_move : std::vector<std::pair<int, int>>{}; }

    void draw_board();
    void set_position();
    void select(int x, int y);
    void deselect();
    void typeToFont(int x, int y);
    void move(int x, int y, int new_x, int new_y);
};

//_selected.has_value()
void displaytab(const std::vector<std::pair<int, int>>& all_possible_move);