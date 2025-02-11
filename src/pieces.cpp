#include "pieces.hpp"
#include <utility>
#include <vector>
#include <imgui.h>

//Afficher les labels des pieces
void display_piece_type (PieceType type) {
    if (type == PieceType::KING){
        ImGui::Button("King", ImVec2{50.f, 50.f});
    }
    else if (type == PieceType::ROOK){
        ImGui::Button("Rook", ImVec2{50.f, 50.f});
    }
    else if (type == PieceType::QUEEN){
        ImGui::Button("Queen", ImVec2{50.f, 50.f});
    }
    else if (type == PieceType::BISHOP){
        ImGui::Button("Bishop", ImVec2{50.f, 50.f});
    }
    else if (type == PieceType::PAWN){
        ImGui::Button("Pawn", ImVec2{50.f, 50.f});
    }
    else if (type == PieceType::KNIGHT){
        ImGui::Button("Knight", ImVec2{50.f, 50.f});
    }
};

// Calcul de toutes les positions possibles en fonction du type de piece.
std::vector<std::pair<int, int>> Rook::all_possible_move()
{
    std::vector<std::pair<int, int>> all_theoriq_moves{};
    for (int x{0}; x < 8; x++)
    {
        for (int y{0}; y < 8; y++)
        {
            if ((this->m_x == x || this->m_y == y) && (this->m_x != x || this->m_y != y))
            {
                all_theoriq_moves.emplace_back(x, y);
            }
        }
    }
    return all_theoriq_moves;
}

// std::vector<std::pair<int, int>> Knight::all_possible_move()
// {
//     std::vector<std::pair<int, int>> all_theoriq_moves{};
//     std::vector<std::pair<int, int>> moves = {{-2, -1}, {-2, 1}, {2, -1}, {2, 1}, {1, -2}, {-1, -2}, {1, 2}, {-1, 2}};

//     return all_theoriq_moves;
// }

std::vector<std::pair<int, int>> Bishop::all_possible_move()
{
    std::vector<std::pair<int, int>> all_theoriq_moves{};
    for (int x{0}; x < 8; x++)
    {
        for (int y{0}; y < 8; y++)
        {
            for (int i{1}; i < 7; i++)
            {
                if ((this->m_x == x + i && this->m_y == y + i) || (this->m_x != x - i && this->m_y != y - i) || (this->m_x == x + i && this->m_y == y - i) || (this->m_x != x - i && this->m_y != y + i))
                {
                    all_theoriq_moves.emplace_back(x, y);
                }
            }
        }
    }
    return all_theoriq_moves;
}

std::vector<std::pair<int, int>> Queen::all_possible_move()
{
    std::vector<std::pair<int, int>> all_theoriq_moves{};
    return all_theoriq_moves;
}

std::vector<std::pair<int, int>> King::all_possible_move()
{
    std::vector<std::pair<int, int>> all_theoriq_moves{};
    for (int x{0}; x < 8; x++)
    {
        for (int y{0}; y < 8; y++)
        {
            if ((this->m_x == x && (this->m_y == y + 1 || this->m_y == y - 1)) || (this->m_y == y && (this->m_x == x + 1 || this->m_x == x - 1)) || ((this->m_y == y + 1 || this->m_y == y - 1) && (this->m_x == x + 1 || this->m_x == x - 1)))
            {
                all_theoriq_moves.emplace_back(x, y);
            }
        }
    }
    return all_theoriq_moves;
}

std::vector<std::pair<int, int>> Pawn::all_possible_move()
{
    std::vector<std::pair<int, int>> all_theoriq_moves{};
    return all_theoriq_moves;
}