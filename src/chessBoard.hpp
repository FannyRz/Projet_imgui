#pragma once
#include <imgui.h>
#include <array>
#include <memory>
#include <optional>
#include <string>
#include "pieces/pieces.hpp"

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

public:
    void                             set_font(ImFont* font) { this->font = font; };
    ImFont*                          get_font() const { return this->font; };
    std::vector<std::pair<int, int>> get_all_possible_move() { return _selected.has_value() ? _selected->all_possible_move : std::vector<std::pair<int, int>>{}; }

    void        draw_board();
    void        set_position();
    void        select(int x, int y);
    void        deselect();
    std::string from_type_to_char(int x, int y) const;
    void        move(int x, int y, int new_x, int new_y);
    bool        can_move(int x, int y, int new_x, int new_y);
    bool        get_piece(int x, int y);
};