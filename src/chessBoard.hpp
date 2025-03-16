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
    PieceColor                       piececolor;
    std::vector<std::pair<int, int>> all_possible_move{}; //->pour savoir les déplacements possibles
};

struct EnPassantPiece {
    Piece*              piece;
    std::vector<Piece*> en_passant_piece{}; // pour garder en memoire les cases qui peuvent manger en_passant
};

struct PieceButton {
    PieceType   type;
    const char* white_label;
    const char* black_label;
    ImVec4      color;
};

class ChessBoard {
private:
    std::array<std::array<std::unique_ptr<Piece>, 8>, 8> position_pieces{}; // tableau de positions initiales des pièces
    std::optional<SelectedPiece>                         _selected;
    std::optional<EnPassantPiece>                        _enPassantPiece;
    std::optional<SelectedPiece>                         _selected_pawn;
    ImFont*                                              font;
    bool                                                 is_white_turn = true;
    bool                                                 game_won      = false;
    PieceColor                                           winner_color;

public:
    void                             set_font(ImFont* font) { this->font = font; };
    ImFont*                          get_font() const { return this->font; };
    std::vector<std::pair<int, int>> get_all_possible_move() { return _selected.has_value() ? _selected->all_possible_move : std::vector<std::pair<int, int>>{}; }

    void                         draw_board();
    void                         set_position();
    void                         select(int x, int y);
    std::optional<SelectedPiece> select_pawn(int x, int y);
    void                         deselect();
    std::string                  from_type_to_char(int x, int y) const;
    void                         move(int x, int y, int new_x, int new_y);
    bool                         can_move(int new_x, int new_y);
    bool                         get_piece(int x, int y);
    void                         set_is_white_turn(bool is_white_turn) { this->is_white_turn = is_white_turn; };
    bool                         get_is_white_turn() const { return this->is_white_turn; };
    bool                         is_my_turn(int x, int y);
    bool                         piece_at_the_end(int x, int y);
    void                         print_popup(std::optional<SelectedPiece> selected);
    void                         print_popup_win();
    void                         change_piece(int x, int y, PieceType nouveau_type, PieceColor color);
    void                         reset_board();
    void                         set_en_passant(int x, int y);
    void                         get_en_passant(int x, int y);
};
