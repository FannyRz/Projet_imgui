#pragma once
#include <iostream>
#include <vector>

enum class PieceColor {
    WHITE,
    BLACK
};

enum class PieceType {
    KING,
    QUEEN,
    ROOK,   // tour
    KNIGHT, // cavalier
    PAWN,   // pion
    BISHOP  // fou
};

void display_piece_type (PieceType type);

// inline std::vector<std::vector<std::string>> position_pieces{
//     {"Tn", "Cn", "Fn", "Dn", "Rn", "Fn", "Cn", "Tn"},
//     {"Pn", "Pn", "Pn", "Pn", "Pn", "Pn", "Pn", "Pn"},
//     {"V", "V", "V", "V", "V", "V", "V", "V"},
//     {"V", "V", "V", "V", "V", "V", "V", "V"},
//     {"V", "V", "V", "V", "V", "V", "V", "V"},
//     {"V", "V", "V", "V", "V", "V", "V", "V"},
//     {"Pb", "Pb", "Pb", "Pb", "Pb", "Pb", "Pb", "Pb"},
//     {"Tb", "Cb", "Fb", "Db", "Rb", "Fb", "Cb", "Tb"}
// }; // tableau de positions initiales des pièces.

class Piece {
protected:
    // std::string m_label;
    PieceType  m_type;
    PieceColor m_color;
    int        m_x;
    int        m_y;

public:
    Piece(Piece&&)                 = delete;
    Piece& operator=(const Piece&) = delete;
    Piece& operator=(Piece&&)      = delete;
    Piece(PieceType type, PieceColor color, int x, int y);
    Piece(const Piece& piece);
    virtual ~Piece() = default;
    void                                     position();
    void                                     draw_possible_move();
    virtual std::vector<std::pair<int, int>> all_possible_move() = 0;
};

class Rook : public Piece {
public:
    Rook(Rook&&)                 = delete;
    Rook& operator=(const Rook&) = default;
    Rook& operator=(Rook&&)      = delete;
    Rook(PieceColor color, int x, int y)
        : Piece(PieceType::ROOK, color, x, y) {};
    Rook(const Rook& tour);
    ~Rook() override;
    std::vector<std::pair<int, int>> all_possible_move() override;
};

class Knight : public Piece {
public:
    Knight(Knight&&)                 = delete;
    Knight& operator=(const Knight&) = default;
    Knight& operator=(Knight&&)      = delete;
    Knight(PieceColor color, int x, int y)
        : Piece(PieceType::KNIGHT, color, x, y) {};
    Knight(const Knight& cavalier);
    ~Knight() override;
    std::vector<std::pair<int, int>> all_possible_move() override;
};

class Bishop : public Piece {
public:
    Bishop(Bishop&&)                 = delete;
    Bishop& operator=(const Bishop&) = default;
    Bishop& operator=(Bishop&&)      = delete;
    Bishop(PieceColor color, int x, int y)
        : Piece(PieceType::BISHOP, color, x, y) {};
    Bishop(const Bishop& fou);
    ~Bishop() override;
    std::vector<std::pair<int, int>> all_possible_move() override;
};

class Queen : public Piece {
public:
    Queen(Queen&&)                 = delete;
    Queen& operator=(const Queen&) = default;
    Queen& operator=(Queen&&)      = delete;
    Queen(PieceColor color, int x, int y)
        : Piece(PieceType::QUEEN, color, x, y) {};
    Queen(const Queen& dame);
    ~Queen() override;
    std::vector<std::pair<int, int>> all_possible_move() override;
};

class King : public Piece {
public:
    King(King&&)                 = delete;
    King& operator=(const King&) = default;
    King& operator=(King&&)      = delete;
    King(PieceColor color, int x, int y)
        : Piece(PieceType::KING, color, x, y) {};
    King(const King& roi);
    ~King() override;
    std::vector<std::pair<int, int>> all_possible_move() override;
};

class Pawn : public Piece {
public:
    Pawn(Pawn&&)                 = delete;
    Pawn& operator=(const Pawn&) = default;
    Pawn& operator=(Pawn&&)      = delete;
    Pawn(PieceColor color, int x, int y)
        : Piece(PieceType::PAWN, color, x, y) {};
    Pawn(const Pawn& pion);
    ~Pawn() override;
    std::vector<std::pair<int, int>> all_possible_move() override;
};