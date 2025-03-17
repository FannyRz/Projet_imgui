#include <imgui.h>
#include <iostream>
#include <memory>
#include <optional>
#include "chessBoard.hpp"
#include "pieces/bishop.hpp"
#include "pieces/knight.hpp"
#include "pieces/pawn.hpp"
#include "pieces/pieces.hpp"
#include "pieces/queen.hpp"
#include "pieces/rook.hpp"

/* ------------------------------ gestion des structs ------------------------------ */
void ChessBoard::deselect_selectedPiece()
{
    _selected = std::nullopt;
}

void ChessBoard::select_selectedPiece(int x, int y)
{
    SelectedPiece selectedPiece{};
    selectedPiece.piece             = position_pieces[x][y].get();
    selectedPiece.position_x        = x;
    selectedPiece.position_y        = y;
    selectedPiece.piececolor        = position_pieces[x][y]->get_color();
    selectedPiece.all_possible_move = position_pieces[x][y]->all_possible_move(this->position_pieces);
    this->_selected                 = selectedPiece;
}

std::optional<SelectedPiece> ChessBoard::select_pawn_to_upgrade(int x, int y)
{
    SelectedPiece selectedPiece{};
    selectedPiece.piece      = position_pieces[x][y].get();
    selectedPiece.position_x = x;
    selectedPiece.position_y = y;
    selectedPiece.piececolor = position_pieces[x][y]->get_color();
    this->_selected_pawn     = selectedPiece;
    return {selectedPiece};
}

/* ------------------------------ gestion des moves ------------------------------ */
void ChessBoard::move(int x, int y, int new_x, int new_y)
{
    // Vérifie s'il y a une pièce sur la case d'arrivée
    if (get_piece(new_x, new_y))
    {
        // Vérifie si c'est un roi
        if (this->position_pieces[new_x][new_y]->get_type() == PieceType::KING)
        {
            game_won     = true;
            winner_color = this->position_pieces[x][y]->get_color();
        }
    }
    this->position_pieces[x][y]->set_positionx(new_x);
    this->position_pieces[x][y]->set_positiony(new_y);
    this->position_pieces[new_x][new_y] = std::move(this->position_pieces[x][y]);
    this->position_pieces[x][y]         = nullptr;

    if (this->_enPassantPiece.has_value() && this->position_pieces[new_x][new_y]->get_type() == PieceType::PAWN && std::find(std::begin(this->_enPassantPiece->en_passant_piece), std::end(this->_enPassantPiece->en_passant_piece), this->_selected->piece) != std::end(this->_enPassantPiece->en_passant_piece))
    {
        int direction = (this->_selected->piece->get_color() == PieceColor::BLACK) ? 1 : -1;
        if (new_x == this->_enPassantPiece->piece->get_positionx() + direction && new_y == this->_enPassantPiece->piece->get_positiony())
        {
            attack_en_passant();
        }
    }

    if (this->_enPassantPiece.has_value() && piece_Moved)
    {
        this->reset_en_passant();
    }

    if (this->position_pieces[new_x][new_y]->get_type() == PieceType::PAWN && abs(new_x - x) == 2)
    {
        set_en_passant(new_x, new_y);
    }

    set_is_white_turn(!is_white_turn);
}

bool ChessBoard::can_move(int new_x, int new_y)
{
    return std::find(this->_selected->all_possible_move.begin(), this->_selected->all_possible_move.end(), std::make_pair(new_x, new_y)) != this->_selected->all_possible_move.end();
}

/* ------------------------------ gestion du en_passant ------------------------------ */
void ChessBoard::set_en_passant(int x, int y)
{
    std::vector<Piece*> en_passant_piece{};

    // gauche
    if (get_piece(x, y + 1))
    {
        Pawn* pawn = dynamic_cast<Pawn*>(this->position_pieces[x][y + 1].get());
        if (pawn && pawn->get_color() != this->position_pieces[x][y]->get_color())
        {
            en_passant_piece.push_back(this->position_pieces[x][y + 1].get());
        }
    }

    // droite
    if (get_piece(x, y - 1))
    {
        Pawn* pawn = dynamic_cast<Pawn*>(this->position_pieces[x][y - 1].get());
        if (pawn && pawn->get_color() != this->position_pieces[x][y]->get_color())
        {
            en_passant_piece.push_back(this->position_pieces[x][y - 1].get());
        }
    }

    if (!en_passant_piece.empty())
    {
        EnPassantPiece enPassantPiece{};
        Pawn*          pawn             = dynamic_cast<Pawn*>(this->_selected->piece);
        enPassantPiece.piece            = this->_selected->piece;
        enPassantPiece.en_passant_piece = en_passant_piece;
        this->_enPassantPiece           = enPassantPiece;

        piece_Moved = true;
    }
}

void ChessBoard::get_en_passant()
{
    if (std::find(std::begin(this->_enPassantPiece->en_passant_piece), std::end(this->_enPassantPiece->en_passant_piece), this->_selected->piece) != std::end(this->_enPassantPiece->en_passant_piece))
    {
        int direction = (this->_selected->piece->get_color() == PieceColor::BLACK) ? 1 : -1;
        this->_selected->all_possible_move.emplace_back(this->_enPassantPiece->piece->get_positionx() + direction, this->_enPassantPiece->piece->get_positiony());
        Pawn* pawn = dynamic_cast<Pawn*>(this->_selected->piece);
    }
}

void ChessBoard::attack_en_passant()
{
    this->position_pieces[this->_enPassantPiece->piece->get_positionx()][this->_enPassantPiece->piece->get_positiony()].reset();
    this->_enPassantPiece->piece = nullptr;
}

void ChessBoard::reset_en_passant()
{
    piece_Moved                  = false;
    this->_enPassantPiece->piece = nullptr;
    this->_enPassantPiece->en_passant_piece.clear();
}

/* ------------------------------ gestion de upgrade pawn ------------------------------ */
bool ChessBoard::piece_at_the_end(int x, int y)
{
    return (this->position_pieces[x][y]->get_positionx() == 0 && this->position_pieces[x][y]->get_color() == PieceColor::WHITE) || (this->position_pieces[x][y]->get_positionx() == 7 && this->position_pieces[x][y]->get_color() == PieceColor::BLACK);
}

void ChessBoard::change_piece(int x, int y, PieceType nouveau_type, PieceColor color)
{
    if (position_pieces[x][y] == nullptr)
        return;

    switch (nouveau_type)
    {
    case PieceType::QUEEN:
        position_pieces[x][y] = std::make_unique<Queen>(color, x, y);
        break;
    case PieceType::ROOK:
        position_pieces[x][y] = std::make_unique<Rook>(color, x, y);
        break;
    case PieceType::BISHOP:
        position_pieces[x][y] = std::make_unique<Bishop>(color, x, y);
        break;
    case PieceType::KNIGHT:
        position_pieces[x][y] = std::make_unique<Knight>(color, x, y);
        break;
    default:
        return;
    }
}
