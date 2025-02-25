#pragma once
#include "pieces.hpp"

class Rook : public Piece {
public:
    Rook(Rook&&)                 = delete;
    Rook& operator=(const Rook&) = delete;
    Rook& operator=(Rook&&)      = delete;
    Rook(PieceColor color, int x, int y)
        : Piece(PieceType::ROOK, color, x, y) {};
    Rook(const Rook& tour);
    ~Rook() override = default;
    std::vector<std::pair<int, int>> all_possible_move() override;
};