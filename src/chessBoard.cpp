#include "chessBoard.hpp"
#include <imgui.h>
#include <iostream>
#include <memory>
#include <optional>
#include "pieces.hpp"

void set_position(std::vector<std::vector<std::unique_ptr<Piece>>>& position_pieces)
{
    // tour
    position_pieces[0][0] = std::make_unique<Rook>(PieceColor::BLACK, 0, 0);
    position_pieces[0][7] = std::make_unique<Rook>(PieceColor::BLACK, 0, 7);
    position_pieces[7][0] = std::make_unique<Rook>(PieceColor::WHITE, 7, 0);
    position_pieces[7][7] = std::make_unique<Rook>(PieceColor::WHITE, 7, 7);

    // cavalier
    position_pieces[0][1] = std::make_unique<Knight>(PieceColor::BLACK, 0, 1);
    position_pieces[0][6] = std::make_unique<Knight>(PieceColor::BLACK, 0, 6);
    position_pieces[7][1] = std::make_unique<Knight>(PieceColor::WHITE, 7, 1);
    position_pieces[7][6] = std::make_unique<Knight>(PieceColor::WHITE, 7, 6);

    // fou
    position_pieces[0][2] = std::make_unique<Bishop>(PieceColor::BLACK, 0, 2);
    position_pieces[0][5] = std::make_unique<Bishop>(PieceColor::BLACK, 0, 5);
    position_pieces[7][2] = std::make_unique<Bishop>(PieceColor::WHITE, 7, 2);
    position_pieces[7][5] = std::make_unique<Bishop>(PieceColor::WHITE, 7, 5);

    // dame
    position_pieces[0][3] = std::make_unique<Queen>(PieceColor::BLACK, 0, 3);
    position_pieces[7][3] = std::make_unique<Queen>(PieceColor::WHITE, 7, 3);

    // roi
    position_pieces[0][4] = std::make_unique<King>(PieceColor::BLACK, 0, 4);
    position_pieces[7][4] = std::make_unique<King>(PieceColor::WHITE, 7, 4);

    // pion
    for (int i{0}; i < 8; i++)
    {
        position_pieces[1][i] = std::make_unique<Pawn>(PieceColor::BLACK, 1, i);
        position_pieces[7][i] = std::make_unique<Pawn>(PieceColor::WHITE, 7, i);
    }
}

void ChessBoard::deselect()
{
    _selected = std::nullopt;
}

void ChessBoard::select(int x, int y)
{
    SelectedPiece selectedPiece{};
    selectedPiece.position_x = x;
    selectedPiece.position_y = y;
    _selected                = selectedPiece;

    // std::cout << this->_selected->position_x << " , " << this->_selected->position_y << '\n';
}

void ChessBoard::draw_board()
{
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{0.f, 0.f}); // Bordure entre les cases à zéro.
    for (int x{0}; x < 8; x++)
    {
        for (int y{0}; y < 8; y++)
        {
            bool borderActivate = false;

            if ((x + y) % 2 == 0)
            {
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.f, 0.f, 0.f, 1.f});
            }
            else
            {
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{1.f, 1.f, 1.f, 1.f});
            }

            if (_selected.has_value() && x == _selected->position_x && y == _selected->position_y)
            {
                ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 3.0f); // Bordure plus épaisse
                ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
                borderActivate = true;
            }

            ImGui::PushFont(this->font);
            //  Piece* piece = board.get_pîece(x, y);  Code fait par Jules qui demande si sur une case il y a une piece ou non

            // determiner la piece sur la case
            std::string piece_label          = position_pieces[x][y];
            std::string piece_label_position = position_pieces[x][y] + std::to_string(x) + "_" + std::to_string(y);

            if (ImGui::Button((piece_label != "V" ? piece_label_position : "Vide##" + std::to_string(x) + "_" + std::to_string(y)).c_str(), ImVec2{50.f, 50.f})) // Le "##" permet d'ajouter un identifiant unique sur chaque bouton sans qu'il apparaisse sur le bouton.
            {
                if (_selected.has_value() && x == _selected->position_x && y == _selected->position_y)
                {
                    this->deselect();
                }
                else
                {
                    // std::cout << "Clicked button (" << x << "," << y << ") \n";
                    this->select(x, y);
                    // std::cout << _selected.has_value() << '\n';
                }
            }

            if (borderActivate)
            {
                ImGui::PopStyleColor();
                ImGui::PopStyleVar();
            }

            if (y != 7)
            {
                ImGui::SameLine();
            }

            ImGui::PopFont();
            ImGui::PopStyleColor();
        }
    }
    ImGui::PopStyleVar();
}