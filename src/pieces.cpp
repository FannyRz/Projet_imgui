#include "pieces.hpp"
#include <utility>
#include <vector>

// Calcul de toutes les positions possibles en fonction du type de piece.
std::vector<std::pair<int, int>> Tour::all_possible_move()
{
    std::vector<std::pair<int, int>> all_theoriq_moves{};
    for (int x{0}; x < 8; x++)
    {
        for (int y{0}; y < 8; y++)
        {
            if ((this->m_x == x || this->m_y == y) && (this->m_x != x || this->m_y != y))
            {
                all_theoriq_moves.emplace_back(x, y);
            }
        }
    }
    return all_theoriq_moves;
}

std::vector<std::pair<int, int>> Cavalier::all_possible_move()
{
    std::vector<std::pair<int, int>> all_theoriq_moves{};
    return all_theoriq_moves;
}

std::vector<std::pair<int, int>> Fou::all_possible_move()
{
    std::vector<std::pair<int, int>> all_theoriq_moves{};
    return all_theoriq_moves;
}

std::vector<std::pair<int, int>> Dame::all_possible_move()
{
    std::vector<std::pair<int, int>> all_theoriq_moves{};
    return all_theoriq_moves;
}

std::vector<std::pair<int, int>> Roi::all_possible_move()
{
    std::vector<std::pair<int, int>> all_theoriq_moves{};
    return all_theoriq_moves;
}

std::vector<std::pair<int, int>> Pion::all_possible_move()
{
    std::vector<std::pair<int, int>> all_theoriq_moves{};
    return all_theoriq_moves;
}