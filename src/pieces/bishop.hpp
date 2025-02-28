#pragma once
#include "pieces.hpp"

class Bishop : public Piece {
public:
    Bishop(Bishop&&)                 = delete;
    Bishop& operator=(const Bishop&) = delete;
    Bishop& operator=(Bishop&&)      = delete;
    Bishop(PieceColor color, int x, int y)
        : Piece(PieceType::BISHOP, color, x, y) {};
    Bishop(const Bishop& fou);
    ~Bishop() override = default;
    std::vector<std::pair<int, int>> all_possible_move(std::array<std::array<std::unique_ptr<Piece>, 8>, 8>& position_pieces) override;
};