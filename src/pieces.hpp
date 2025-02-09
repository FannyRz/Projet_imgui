#pragma once
#include <iostream>
#include <vector>

enum class Type {
    KING,
    QUEEN,
    ROOK,   // tour
    KNIGHT, // cavalier
    PAWN,   // pion
    BISHOP, // fou
    VIDE
};

inline std::vector<std::vector<std::string>> position_pieces{
    {"Tn", "Cn", "Fn", "Dn", "Rn", "Fn", "Cn", "Tn"},
    {"Pn", "Pn", "Pn", "Pn", "Pn", "Pn", "Pn", "Pn"},
    {"V", "V", "V", "V", "V", "V", "V", "V"},
    {"V", "V", "V", "V", "V", "V", "V", "V"},
    {"V", "V", "V", "V", "V", "V", "V", "V"},
    {"V", "V", "V", "V", "V", "V", "V", "V"},
    {"Pb", "Pb", "Pb", "Pb", "Pb", "Pb", "Pb", "Pb"},
    {"Tb", "Cb", "Fb", "Db", "Rb", "Fb", "Cb", "Tb"}
}; // tableau de positions initiales des pièces.

class Piece {
protected:
    std::string m_label;
    int         m_color; // 0:blanc 1:noire
    int         m_x;
    int         m_y;

public:
    Piece(Piece&&)                 = delete;
    Piece& operator=(const Piece&) = default;
    Piece& operator=(Piece&&)      = delete;
    Piece(std::string label, int color, int x, int y);
    Piece(const Piece& piece);
    virtual ~Piece();
    void                                     position();
    void                                     draw_possible_move();
    virtual std::vector<std::pair<int, int>> all_possible_move() = 0;
};

class Tour : public Piece {
public:
    Tour(Tour&&)                 = delete;
    Tour& operator=(const Tour&) = default;
    Tour& operator=(Tour&&)      = delete;
    Tour(int color, int x, int y)
        : Piece("Tour", color, x, y) {};
    Tour(const Tour& tour);
    ~Tour() override;
    std::vector<std::pair<int, int>> all_possible_move() override;
};

class Cavalier : public Piece {
public:
    Cavalier(Cavalier&&)                 = delete;
    Cavalier& operator=(const Cavalier&) = default;
    Cavalier& operator=(Cavalier&&)      = delete;
    Cavalier(int color, int x, int y)
        : Piece("Cavalier", color, x, y) {};
    Cavalier(const Cavalier& cavalier);
    ~Cavalier() override;
    std::vector<std::pair<int, int>> all_possible_move() override;
};

class Fou : public Piece {
public:
    Fou(Fou&&)                 = delete;
    Fou& operator=(const Fou&) = default;
    Fou& operator=(Fou&&)      = delete;
    Fou(int color, int x, int y)
        : Piece("Fou", color, x, y) {};
    Fou(const Fou& fou);
    ~Fou() override;
    std::vector<std::pair<int, int>> all_possible_move() override;
};

class Dame : public Piece {
public:
    Dame(Dame&&)                 = delete;
    Dame& operator=(const Dame&) = default;
    Dame& operator=(Dame&&)      = delete;
    Dame(int color, int x, int y)
        : Piece("Dame", color, x, y) {};
    Dame(const Dame& dame);
    ~Dame() override;
    std::vector<std::pair<int, int>> all_possible_move() override;
};

class Roi : public Piece {
public:
    Roi(Roi&&)                 = delete;
    Roi& operator=(const Roi&) = default;
    Roi& operator=(Roi&&)      = delete;
    Roi(int color, int x, int y)
        : Piece("Roi", color, x, y) {};
    Roi(const Roi& roi);
    ~Roi() override;
    std::vector<std::pair<int, int>> all_possible_move() override;
};

class Pion : public Piece {
public:
    Pion(Pion&&)                 = delete;
    Pion& operator=(const Pion&) = default;
    Pion& operator=(Pion&&)      = delete;
    Pion(int color, int x, int y)
        : Piece("Pion", color, x, y) {};
    Pion(const Pion& pion);
    ~Pion() override;
    std::vector<std::pair<int, int>> all_possible_move() override;
};