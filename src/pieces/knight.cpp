#include "knight.hpp"

std::vector<std::pair<int, int>> Knight::all_possible_move()
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