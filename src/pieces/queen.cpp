#include "queen.hpp"
#include "bishop.hpp"
#include "rook.hpp"

std::vector<std::pair<int, int>> Queen::all_possible_move([[maybe_unused]]std::array<std::array<std::unique_ptr<Piece>, 8>, 8>& position_pieces)
{
    Bishop bishop(this->m_color, this->m_x,this->m_y );
    Rook rook(this->m_color, this->m_x, this->m_y);

    std::vector<std::pair<int, int>> all_theoriq_moves_bishop = bishop.all_possible_move(position_pieces);
    std::vector<std::pair<int, int>> all_theoriq_moves_rook = rook.all_possible_move(position_pieces);
    
    std::vector<std::pair<int, int>> all_theoriq_moves {};

    for (int i {}; i<all_theoriq_moves_bishop.size(); i++){
        all_theoriq_moves.push_back(all_theoriq_moves_bishop[i]);
    }
    
    for (int j {}; j<all_theoriq_moves_rook.size(); j++){
        all_theoriq_moves.push_back(all_theoriq_moves_rook[j]);
    }

    return all_theoriq_moves;
}