#include "bishop.hpp"
#include <cstddef>
#include "utils.hpp"

std::vector<std::pair<int, int>> Bishop::all_possible_move([[maybe_unused]] std::array<std::array<std::unique_ptr<Piece>, 8>, 8>& position_pieces)
{
    std::vector<std::pair<int, int>> all_theoriq_moves;

    // Fonction lambda
    auto add_moves_in_direction = [&](int dx, int dy) {
        int x = this->m_x;
        int y = this->m_y;

        while (is_on_the_chessboard(x, y))
        {
            x += dx;
            y += dy;
            if (!is_on_the_chessboard(x, y))
                break;
            if (position_pieces[x][y] != nullptr)
            {
                if (position_pieces[x][y]->get_color() != this->get_color())
                {
                    all_theoriq_moves.emplace_back(x, y);
                }
                break;
            }
            all_theoriq_moves.emplace_back(x, y);
        }
    };

    // Ajouter les mouvements dans les 4 directions
    add_moves_in_direction(1, 1);   // Droite
    add_moves_in_direction(-1, -1); // Gauche
    add_moves_in_direction(-1, 1);  // Haut
    add_moves_in_direction(1, -1);  // Bas

    return all_theoriq_moves;
}
