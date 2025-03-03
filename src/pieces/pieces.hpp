#pragma once
#include <array>
#include <memory>
#include <vector>


enum class PieceColor : std::uint8_t {
    WHITE,
    BLACK
};

enum class PieceType : std::uint8_t {
    KING,
    QUEEN,
    ROOK,   // tour
    KNIGHT, // cavalier
    PAWN,   // pion
    BISHOP  // fou
};

class Piece {
protected:
    PieceType  m_type;
    PieceColor m_color;
    int        m_x;
    int        m_y;

public:
    Piece& operator=(const Piece&) = delete;
    Piece(Piece&&)                 = delete;
    Piece& operator=(Piece&&)      = delete;
    Piece(PieceType type, PieceColor color, int x, int y)
        : m_type(type), m_color(color), m_x(x), m_y(y) {};
    Piece(const Piece& piece);
    virtual ~Piece() = default;
    void                                     position();
    void                                     draw_possible_move();
    virtual std::vector<std::pair<int, int>> all_possible_move(std::array<std::array<std::unique_ptr<Piece>, 8>, 8>& position_pieces) = 0;

    PieceType  get_type() const { return this->m_type; };
    PieceColor get_color() const { return this->m_color; };
    int        get_positionx() const { return this->m_x; };
    int        get_positiony() const { return this->m_y; };
    void       set_positionx(int x) { this->m_x = x; };
    void       set_positiony(int y) { this->m_y = y; };

    bool isOnTheChessboard(int x, int y);
};