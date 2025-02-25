#pragma once
#include "pieces.hpp"

class King : public Piece {
public:
    King(King&&)                 = delete;
    King& operator=(const King&) = delete;
    King& operator=(King&&)      = delete;
    King(PieceColor color, int x, int y)
        : Piece(PieceType::KING, color, x, y) {};
    King(const King& roi);
    ~King() override = default;
    std::vector<std::pair<int, int>> all_possible_move() override;
};