#pragma once
#include "pieces.hpp"

class Pawn : public Piece {
private:
    bool enpassant = false;

public:
    Pawn(Pawn&&)                 = delete;
    Pawn& operator=(const Pawn&) = delete;
    Pawn& operator=(Pawn&&)      = delete;
    Pawn(PieceColor color, int x, int y)
        : Piece(PieceType::PAWN, color, x, y) {};
    Pawn(const Pawn& pion);
    ~Pawn() override = default;
    std::vector<std::pair<int, int>> all_possible_move(std::array<std::array<std::unique_ptr<Piece>, 8>, 8>& position_pieces) override;

    bool get_enpassant() const { return this->enpassant; };
    void set_enpassant(bool enpassant) { this->enpassant = enpassant; };
    // bool get_enpassantdroit() const { return this->enpassantdroit; };
    // void set_enpassantdroit(bool enpassantdroit) { this->enpassantdroit = enpassantdroit; };

    void first_move(std::array<std::array<std::unique_ptr<Piece>, 8>, 8>& position_pieces, std::vector<std::pair<int, int>>& all_theoriq_moves, int direction);
    void en_passant(std::array<std::array<std::unique_ptr<Piece>, 8>, 8>& position_pieces);
};