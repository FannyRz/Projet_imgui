#include "king.hpp"

std::vector<std::pair<int, int>> King::all_possible_move()
{
    std::vector<std::pair<int, int>> all_theoriq_moves{};
    for (int x{0}; x < 8; x++)
    {
        for (int y{0}; y < 8; y++)
        {
            if ((this->m_x == x && (this->m_y == y + 1 || this->m_y == y - 1)) || (this->m_y == y && (this->m_x == x + 1 || this->m_x == x - 1)) || ((this->m_y == y + 1 || this->m_y == y - 1) && (this->m_x == x + 1 || this->m_x == x - 1)))
            {
                all_theoriq_moves.emplace_back(x, y);
            }
        }
    }
    return all_theoriq_moves;
}