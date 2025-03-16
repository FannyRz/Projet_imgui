#include "pawn.hpp"
#include <utility>
#include "pieces.hpp"
#include "utils.hpp"

std::vector<std::pair<int, int>> Pawn::all_possible_move([[maybe_unused]] std::array<std::array<std::unique_ptr<Piece>, 8>, 8>& position_pieces)
{
    std::vector<std::pair<int, int>> all_theoriq_moves{};
    int                              direction = (this->get_color() == PieceColor::BLACK) ? 1 : -1;

    int x = this->m_x;
    int y = this->m_y;

    if (position_pieces[this->get_positionx() + direction][this->get_positiony()] == nullptr)
    {
        all_theoriq_moves.emplace_back(this->get_positionx() + direction * 1, this->get_positiony());
        first_move(position_pieces, all_theoriq_moves, direction);
    }

    if (this->get_color() == PieceColor::BLACK)
    {
        if (isOnTheChessboard(x + 1, y - 1) && position_pieces[x + 1][y - 1] != nullptr && position_pieces[x + 1][y - 1]->get_color() == PieceColor::WHITE)
        {
            all_theoriq_moves.emplace_back(x + 1, y - 1);
        }
        if (isOnTheChessboard(x + 1, y + 1) && position_pieces[x + 1][y + 1] != nullptr && position_pieces[x + 1][y + 1]->get_color() == PieceColor::WHITE)
        {
            all_theoriq_moves.emplace_back(x + 1, y + 1);
        }
    }
    else
    {
        if (isOnTheChessboard(x - 1, y - 1) && position_pieces[x - 1][y - 1] != nullptr && position_pieces[x - 1][y - 1]->get_color() == PieceColor::BLACK)
        {
            all_theoriq_moves.emplace_back(x - 1, y - 1);
        }
        if (isOnTheChessboard(x - 1, y + 1) && position_pieces[x - 1][y + 1] != nullptr && position_pieces[x - 1][y + 1]->get_color() == PieceColor::BLACK)
        {
            all_theoriq_moves.emplace_back(x - 1, y + 1);
        }
    }

    return all_theoriq_moves;
}

void Pawn::first_move([[maybe_unused]] std::array<std::array<std::unique_ptr<Piece>, 8>, 8>& position_pieces, std::vector<std::pair<int, int>>& all_theoriq_moves, int direction)
{
    if ((this->get_positionx() == 1 && this->get_color() == PieceColor::BLACK) || (this->get_positionx() == 6 && this->get_color() == PieceColor::WHITE))
    {
        if (position_pieces[this->get_positionx() + direction][this->get_positiony()] == nullptr)
        {
            all_theoriq_moves.emplace_back(this->get_positionx() + direction * 2, this->get_positiony());
        }
    }
}
