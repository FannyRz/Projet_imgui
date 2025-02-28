#include "bishop.hpp"

std::vector<std::pair<int, int>> Bishop::all_possible_move([[maybe_unused]] std::array<std::array<std::unique_ptr<Piece>, 8>, 8>& position_pieces)
{
    std::vector<std::pair<int, int>> all_theoriq_moves{};
    for (int x{0}; x < 8; x++)
    {
        for (int y{0}; y < 8; y++)
        {
            for (int i{1}; i < 7; i++)
            {
                if ((this->m_x == x + i && this->m_y == y + i) || (this->m_x != x - i && this->m_y != y - i) || (this->m_x == x + i && this->m_y == y - i) || (this->m_x != x - i && this->m_y != y + i))
                {
                    all_theoriq_moves.emplace_back(x, y);
                }
            }
        }
    }
    return all_theoriq_moves;
}