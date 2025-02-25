#pragma once
#include "pieces.hpp"

class Queen : public Piece {
public:
    Queen(Queen&&)                 = delete;
    Queen& operator=(const Queen&) = delete;
    Queen& operator=(Queen&&)      = delete;
    Queen(PieceColor color, int x, int y)
        : Piece(PieceType::QUEEN, color, x, y) {};
    Queen(const Queen& dame);
    ~Queen() override = default;
    std::vector<std::pair<int, int>> all_possible_move() override;
};