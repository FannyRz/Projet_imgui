#include "knight.hpp"

std::vector<std::pair<int, int>> Knight::all_possible_move([[maybe_unused]]std::array<std::array<std::unique_ptr<Piece>, 8>, 8>& position_pieces)
{
    std::vector<std::pair<int, int>> all_theoriq_moves{};
    std::vector<std::pair<int, int>> moves = {{-2, -1}, {-2, 1}, {2, -1}, {2, 1}, {1, -2}, {-1, -2}, {1, 2}, {-1, 2}};
    for (const std::pair<int, int> move : moves)
    {
        if (isOnTheChessboard(this->m_x + move.first, this->m_y + move.second))
        {
            all_theoriq_moves.emplace_back(this->m_x + move.first, this->m_y + move.second);
        }
    }
    return all_theoriq_moves;
}