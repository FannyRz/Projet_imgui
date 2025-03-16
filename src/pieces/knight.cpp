#include "knight.hpp"
#include "utils.hpp"

std::vector<std::pair<int, int>> Knight::all_possible_move([[maybe_unused]] std::array<std::array<std::unique_ptr<Piece>, 8>, 8>& position_pieces)
{
    std::vector<std::pair<int, int>> all_theoriq_moves{};
    std::vector<std::pair<int, int>> moves = {{-2, -1}, {-2, 1}, {2, -1}, {2, 1}, {1, -2}, {-1, -2}, {1, 2}, {-1, 2}};

    for (const std::pair<int, int>& move : moves)
    {
        int new_x = this->m_x + move.first;
        int new_y = this->m_y + move.second;

        if (isOnTheChessboard(new_x, new_y))
        {
            if (position_pieces[new_x][new_y] != nullptr)
            {
                if (position_pieces[new_x][new_y]->get_color() != this->m_color)
                {
                    all_theoriq_moves.emplace_back(new_x, new_y);
                }
            }
            else
            {
                all_theoriq_moves.emplace_back(new_x, new_y);
            }
        }
    }

    return all_theoriq_moves;
}
