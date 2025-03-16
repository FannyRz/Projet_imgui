#include "queen.hpp"
#include "bishop.hpp"
#include "rook.hpp"
#include "utils.hpp"

std::vector<std::pair<int, int>> Queen::all_possible_move([[maybe_unused]] std::array<std::array<std::unique_ptr<Piece>, 8>, 8>& position_pieces)
{
    // Bishop bishop(this->m_color, this->m_x,this->m_y );
    // Rook rook(this->m_color, this->m_x, this->m_y);

    // std::vector<std::pair<int, int>> all_theoriq_moves_bishop = bishop.all_possible_move(position_pieces);
    // std::vector<std::pair<int, int>> all_theoriq_moves_rook = rook.all_possible_move(position_pieces);

    // std::vector<std::pair<int, int>> all_theoriq_moves {};

    // for (int i {}; i<all_theoriq_moves_bishop.size(); i++){
    //     all_theoriq_moves.push_back(all_theoriq_moves_bishop[i]);
    // }

    // for (int j {}; j<all_theoriq_moves_rook.size(); j++){
    //     all_theoriq_moves.push_back(all_theoriq_moves_rook[j]);
    // }

    // return all_theoriq_moves;

    std::vector<std::pair<int, int>> all_theoriq_moves;

    // Fonction lambda
    auto add_moves_in_direction = [&](int dx, int dy) {
        int x = this->m_x;
        int y = this->m_y;

        while (isOnTheChessboard(x, y))
        {
            x += dx;
            y += dy;
            if (!isOnTheChessboard(x, y))
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
    add_moves_in_direction(1, -1);  // Haut
    add_moves_in_direction(-1, 1);  // Bas
    add_moves_in_direction(1, 0);   // Droite
    add_moves_in_direction(-1, 0);  // Gauche
    add_moves_in_direction(0, 1);   // Haut
    add_moves_in_direction(0, -1);  // Bas

    return all_theoriq_moves;
}