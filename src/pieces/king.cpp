#include "king.hpp"

std::vector<std::pair<int, int>> King::all_possible_move([[maybe_unused]] std::array<std::array<std::unique_ptr<Piece>, 8>, 8>& position_pieces)
{
    std::vector<std::pair<int, int>> all_theoriq_moves{};
    for (int x{0}; x < 8; x++)
    {
        for (int y{0}; y < 8; y++)
        {
            if ((this->m_x == x && (this->m_y == y + 1 || this->m_y == y - 1)) || (this->m_y == y && (this->m_x == x + 1 || this->m_x == x - 1)) || ((this->m_y == y + 1 || this->m_y == y - 1) && (this->m_x == x + 1 || this->m_x == x - 1)))
            {
                if (position_pieces[x][y] != nullptr)
                {
                    if (position_pieces[x][y]->get_color() != this->m_color)
                    {
                        all_theoriq_moves.emplace_back(x, y);
                    }
                }
                else
                {
                    all_theoriq_moves.emplace_back(x, y);
                }
            }
        }
    }
    return all_theoriq_moves;
}