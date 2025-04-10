#pragma once
#include <imgui.h>
#include <array>
#include <memory>
#include <optional>
#include <string>
#include "maths/maths.hpp"
#include "pieces/pieces.hpp"

struct SelectedPiece {
    Piece*                           _piece;
    int                              _position_x;
    int                              _position_y;
    PieceColor                       _piececolor;
    std::vector<std::pair<int, int>> all_possible_move{}; // pour savoir les déplacements possibles
};

struct EnPassantPiece {
    Piece*              _piece;
    std::vector<Piece*> en_passant_piece{}; // pour garder en memoire les cases qui peuvent manger en_passant
};

struct PieceButton {
    PieceType   _type;
    const char* _whiteLabel;
    const char* _blackLabel;
    ImVec4      _color;
};

class ChessBoard {
private:
    std::optional<SelectedPiece>  _selected;
    std::optional<EnPassantPiece> _enPassantPiece;
    std::optional<SelectedPiece>  _selectedPawn;

    LoiDeGamma  _loiDeGamma;
    Chronometer _chronometer;

    std::array<std::array<std::unique_ptr<Piece>, 8>, 8> _positionPieces{}; // tableau des positions initiales des pièces
    ImFont*                                              _font;
    bool                                                 is_piece_moved = false;
    bool                                                 is_white_turn  = true;
    bool                                                 is_game_won    = false;
    PieceColor                                           _winnerColor;

public:
    /* ---------- chessboard_draw.cpp ---------- */
    void draw_board();

    /* ---------- chessboard_game.cpp ---------- */
    void                         deselect_selectedPiece();
    void                         select_selectedPiece(int x, int y);
    std::optional<SelectedPiece> select_pawn_to_upgrade(int x, int y);

    void move(int x, int y, int new_x, int new_y);
    bool can_move(int new_x, int new_y);

    /*gestion de en_passant*/
    void set_en_passant(int x, int y);
    void get_en_passant();
    void attack_en_passant();
    void reset_en_passant();

    /*gestion upgrade*/
    bool piece_at_the_end(int x, int y);
    void change_piece(int x, int y, PieceType nouveau_type, PieceColor color);

    /* ---------- chessboard_utils.cpp ---------- */
    std::string from_type_to_char(int x, int y) const;
    void        set_position();
    bool        get_piece(int x, int y);
    bool        is_my_turn(int x, int y);
    void        print_popup(std::optional<SelectedPiece> selected);
    void        print_popup_win();
    void        reset_board();

    /* ---------- autres ---------- */
    void                                                  set_font(ImFont* font) { this->_font = font; };
    ImFont*                                               get_font() const { return this->_font; };
    std::vector<std::pair<int, int>>                      get_all_possible_move() { return _selected.has_value() ? _selected->all_possible_move : std::vector<std::pair<int, int>>{}; }
    std::array<std::array<std::unique_ptr<Piece>, 8>, 8>* get_position_pieces() { return &this->_positionPieces; };
    void                                                  set_is_white_turn(bool is_white_turn) { this->is_white_turn = is_white_turn; };
    bool                                                  get_is_white_turn() const { return this->is_white_turn; };

    void         set_loiDeGamma(const LoiDeGamma& loiDeGamma) { _loiDeGamma = loiDeGamma; }
    LoiDeGamma   get_loiDeGamma() const { return this->_loiDeGamma; }
    Chronometer& get_chronometer() { return this->_chronometer; }
};
