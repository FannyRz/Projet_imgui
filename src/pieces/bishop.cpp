#include "bishop.hpp"

std::vector<std::pair<int, int>> Bishop::all_possible_move()
{
    std::vector<std::pair<int, int>> all_theoriq_moves{};
    for (int x{0}; x < 8; x++)
    {
        for (int y{0}; y < 8; y++)
        {
            int sum_x_y = (this->m_x)+(this->m_y) ;
            int subtraction_x_y = (this->m_x)-(this->m_y);
            if ((sum_x_y == x+y || subtraction_x_y == x-y))
            {
                all_theoriq_moves.emplace_back(x, y);
            } 
        }
    }
    return all_theoriq_moves;
}