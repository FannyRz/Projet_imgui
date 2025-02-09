#pragma once
#include <iostream>
#include <vector>

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
    Piece(std::string label, int color, int x, int y);
    Piece(const Piece& piece);
    ~Piece();
    void                                     position();
    void                                     draw_possible_move();
    virtual std::vector<std::pair<int, int>> all_possible_move() = 0;
};

class Tour : public Piece {
public:
    Tour(int color, int x, int y)
        : Piece("Tour", color, x, y) {};
    Tour(const Tour& tour);
    ~Tour();
    std::vector<std::pair<int, int>> all_possible_move() override;
};

class Cavalier : public Piece {
public:
    Cavalier(int color, int x, int y)
        : Piece("Cavalier", color, x, y) {};
    Cavalier(const Cavalier& cavalier);
    ~Cavalier();
    std::vector<std::pair<int, int>> all_possible_move() override;
};

class Fou : public Piece {
public:
    Fou(int color, int x, int y)
        : Piece("Fou", color, x, y) {};
    Fou(const Fou& fou);
    ~Fou();
    std::vector<std::pair<int, int>> all_possible_move() override;
};

class Dame : public Piece {
public:
    Dame(int color, int x, int y)
        : Piece("Dame", color, x, y) {};
    Dame(const Dame& dame);
    ~Dame();
    std::vector<std::pair<int, int>> all_possible_move() override;
};

class Roi : public Piece {
public:
    Roi(int color, int x, int y)
        : Piece("Roi", color, x, y) {};
    Roi(const Roi& roi);
    ~Roi();
    std::vector<std::pair<int, int>> all_possible_move() override;
};

class Pion : public Piece {
public:
    Pion(int color, int x, int y)
        : Piece("Pion", color, x, y) {};
    Pion(const Pion& pion);
    ~Pion();
    std::vector<std::pair<int, int>> all_possible_move() override;
};