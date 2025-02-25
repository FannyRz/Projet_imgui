#pragma once
#include "pieces.hpp"

class Knight : public Piece {
public:
    Knight(Knight&&)                 = delete;
    Knight& operator=(const Knight&) = delete;
    Knight& operator=(Knight&&)      = delete;
    Knight(PieceColor color, int x, int y)
        : Piece(PieceType::KNIGHT, color, x, y) {};
    Knight(const Knight& cavalier);
    ~Knight() override = default;
    std::vector<std::pair<int, int>> all_possible_move() override;
};