#include <imgui.h>
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
    selectedPiece._piece            = _positionPieces[x][y].get();
    selectedPiece._position_x       = x;
    selectedPiece._position_y       = y;
    selectedPiece._piececolor       = _positionPieces[x][y]->get_color();
    selectedPiece.all_possible_move = _positionPieces[x][y]->all_possible_move(this->_positionPieces);
    this->_selected                 = selectedPiece;
}

std::optional<SelectedPiece> ChessBoard::select_pawn_to_upgrade(int x, int y)
{
    SelectedPiece selectedPiece{};
    selectedPiece._piece      = _positionPieces[x][y].get();
    selectedPiece._position_x = x;
    selectedPiece._position_y = y;
    selectedPiece._piececolor = _positionPieces[x][y]->get_color();
    this->_selectedPawn       = selectedPiece;
    return {selectedPiece};
}

/* ------------------------------ gestion des moves ------------------------------ */
void ChessBoard::move(int x, int y, int new_x, int new_y)
{
    // Vérifie s'il y a une pièce sur la case d'arrivée
    if (get_piece(new_x, new_y))
    {
        // Vérifie si c'est un roi
        if (this->_positionPieces[new_x][new_y]->get_type() == PieceType::KING)
        {
            is_game_won  = true;
            _winnerColor = this->_positionPieces[x][y]->get_color();
        }
    }
    this->_positionPieces[x][y]->set_positionx(new_x);
    this->_positionPieces[x][y]->set_positiony(new_y);
    this->_positionPieces[new_x][new_y] = std::move(this->_positionPieces[x][y]);
    this->_positionPieces[x][y]         = nullptr;

    if (this->_enPassantPiece.has_value() && this->_positionPieces[new_x][new_y]->get_type() == PieceType::PAWN && std::find(std::begin(this->_enPassantPiece->en_passant_piece), std::end(this->_enPassantPiece->en_passant_piece), this->_selected->_piece) != std::end(this->_enPassantPiece->en_passant_piece))
    {
        int direction = (this->_selected->_piece->get_color() == PieceColor::BLACK) ? 1 : -1;
        if (new_x == this->_enPassantPiece->_piece->get_positionx() + direction && new_y == this->_enPassantPiece->_piece->get_positiony())
        {
            attack_en_passant();
        }
    }

    if (this->_enPassantPiece.has_value() && is_piece_moved)
    {
        this->reset_en_passant();
    }

    if (this->_positionPieces[new_x][new_y]->get_type() == PieceType::PAWN && abs(new_x - x) == 2)
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
        Pawn* pawn = dynamic_cast<Pawn*>(this->_positionPieces[x][y + 1].get());
        if (pawn && pawn->get_color() != this->_positionPieces[x][y]->get_color())
        {
            en_passant_piece.push_back(this->_positionPieces[x][y + 1].get());
        }
    }

    // droite
    if (get_piece(x, y - 1))
    {
        Pawn* pawn = dynamic_cast<Pawn*>(this->_positionPieces[x][y - 1].get());
        if (pawn && pawn->get_color() != this->_positionPieces[x][y]->get_color())
        {
            en_passant_piece.push_back(this->_positionPieces[x][y - 1].get());
        }
    }

    if (!en_passant_piece.empty())
    {
        EnPassantPiece enPassantPiece{};
        Pawn*          pawn             = dynamic_cast<Pawn*>(this->_selected->_piece);
        enPassantPiece._piece           = this->_selected->_piece;
        enPassantPiece.en_passant_piece = en_passant_piece;
        this->_enPassantPiece           = enPassantPiece;

        is_piece_moved = true;
    }
}

void ChessBoard::get_en_passant()
{
    if (std::find(std::begin(this->_enPassantPiece->en_passant_piece), std::end(this->_enPassantPiece->en_passant_piece), this->_selected->_piece) != std::end(this->_enPassantPiece->en_passant_piece))
    {
        int direction = (this->_selected->_piece->get_color() == PieceColor::BLACK) ? 1 : -1;
        this->_selected->all_possible_move.emplace_back(this->_enPassantPiece->_piece->get_positionx() + direction, this->_enPassantPiece->_piece->get_positiony());
        Pawn* pawn = dynamic_cast<Pawn*>(this->_selected->_piece);
    }
}

void ChessBoard::attack_en_passant()
{
    this->_positionPieces[this->_enPassantPiece->_piece->get_positionx()][this->_enPassantPiece->_piece->get_positiony()].reset();
    this->_enPassantPiece->_piece = nullptr;
}

void ChessBoard::reset_en_passant()
{
    is_piece_moved                = false;
    this->_enPassantPiece->_piece = nullptr;
    this->_enPassantPiece->en_passant_piece.clear();
}

/* ------------------------------ gestion de upgrade pawn ------------------------------ */
bool ChessBoard::piece_at_the_end(int x, int y)
{
    return (this->_positionPieces[x][y]->get_positionx() == 0 && this->_positionPieces[x][y]->get_color() == PieceColor::WHITE) || (this->_positionPieces[x][y]->get_positionx() == 7 && this->_positionPieces[x][y]->get_color() == PieceColor::BLACK);
}

void ChessBoard::change_piece(int x, int y, PieceType nouveau_type, PieceColor color)
{
    if (_positionPieces[x][y] == nullptr)
        return;

    switch (nouveau_type)
    {
    case PieceType::QUEEN:
        _positionPieces[x][y] = std::make_unique<Queen>(color, x, y);
        break;
    case PieceType::ROOK:
        _positionPieces[x][y] = std::make_unique<Rook>(color, x, y);
        break;
    case PieceType::BISHOP:
        _positionPieces[x][y] = std::make_unique<Bishop>(color, x, y);
        break;
    case PieceType::KNIGHT:
        _positionPieces[x][y] = std::make_unique<Knight>(color, x, y);
        break;
    default:
        return;
    }
}
