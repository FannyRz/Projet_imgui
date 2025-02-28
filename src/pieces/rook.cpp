#include "rook.hpp"

// std::vector<std::pair<int, int>> Rook::all_possible_move([[maybe_unused]]std::array<std::array<std::unique_ptr<Piece>, 8>, 8>& position_pieces)
// {
//     std::vector<std::pair<int, int>> all_theoriq_moves{};
//     for (int x{0}; x < 8; x++)
//     {
//         for (int y{0}; y < 8; y++)
//         {
//             if ((this->m_x == x || this->m_y == y) && (this->m_x != x || this->m_y != y))
//             {
//                 all_theoriq_moves.emplace_back(x, y);
//             }
//         }
//     }
//     return all_theoriq_moves;
// }

std::vector<std::pair<int, int>> Rook::all_possible_move([[maybe_unused]] std::array<std::array<std::unique_ptr<Piece>, 8>, 8>& position_pieces)
{
    std::vector<std::pair<int, int>> all_theoriq_moves{};

    for (int x = this->m_x + 1; x < 8; x++)
    {
        if (!isOnTheChessboard(x, this->m_y))
        {
            break;
        }
        if (position_pieces[x][this->m_y] != nullptr)
        {
            if (position_pieces[x][this->m_y]->get_color() == this->get_color())
            {
                break;
            }
            else
            {
                all_theoriq_moves.emplace_back(x, m_y);
                break;
            }
        }
        all_theoriq_moves.emplace_back(x, m_y);
    }

    for (int x = this->m_x - 1; x >= 0; x--)
    {
        if (!isOnTheChessboard(x, this->m_y))
        {
            break;
        }
        if (position_pieces[x][this->m_y] != nullptr)
        {
            if (position_pieces[x][this->m_y]->get_color() == this->get_color())
            {
                break;
            }
            else
            {
                all_theoriq_moves.emplace_back(x, m_y);
                break;
            }
        }
        all_theoriq_moves.emplace_back(x, m_y);
    }

    for (int y = this->m_y + 1; y < 8; y++)
    {
        if (!isOnTheChessboard(this->m_x, y))
        {
            break;
        }
        if (position_pieces[this->m_x][y] != nullptr)
        {
            if (position_pieces[this->m_x][y]->get_color() == this->get_color())
            {
                break;
            }
            else
            {
                all_theoriq_moves.emplace_back(m_x, y);
                break;
            }
        }
        all_theoriq_moves.emplace_back(m_x, y);
    }

    for (int y = this->m_y - 1; y >= 0; y--)
    {
        if (!isOnTheChessboard(this->m_x, y))
        {
            break;
        }
        if (position_pieces[this->m_x][y] != nullptr)
        {
            if (position_pieces[this->m_x][y]->get_color() == this->get_color())
            {
                break;
            }
            else
            {
                all_theoriq_moves.emplace_back(m_x, y);
                break;
            }
        }
        all_theoriq_moves.emplace_back(m_x, y);
    }

    return all_theoriq_moves;
}