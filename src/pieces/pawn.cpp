#include "pawn.hpp"
#include "pieces.hpp"

std::vector<std::pair<int, int>> Pawn::all_possible_move([[maybe_unused]] std::array<std::array<std::unique_ptr<Piece>, 8>, 8>& position_pieces)
{
    std::vector<std::pair<int, int>> all_theoriq_moves{};
    int                              direction{0};

    if (this->get_color() == PieceColor::BLACK)
    {
        direction = 1;
        all_theoriq_moves.emplace_back(this->get_positionx() + direction * 1, this->get_positiony());
    }
    else
    {
        direction = -1;
        all_theoriq_moves.emplace_back(this->get_positionx() + direction * 1, this->get_positiony());
    }

    if (this->get_positionx() == 1 || this->get_positionx() == 6)
    {
        if (position_pieces[this->get_positionx() + direction][this->get_positiony()] == nullptr || position_pieces[this->get_positionx()][this->get_positiony()]->get_color() != this->get_color())
        {
            all_theoriq_moves.emplace_back(this->get_positionx() + direction * 2, this->get_positiony());
        }
    }
    return all_theoriq_moves;
}