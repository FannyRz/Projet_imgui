#include "chessBoard.hpp"
#include <imgui.h>
#include <iostream>
#include <optional>
#include "pieces.hpp"

void ChessBoard::deselect()
{
    _selected = std::nullopt;
};

void ChessBoard::select(int x, int y)
{
    SelectedPiece selectedPiece{};
    selectedPiece.position_x = x;
    selectedPiece.position_y = y;
    _selected                = selectedPiece;

    // std::cout << this->_selected->position_x << " , " << this->_selected->position_y << '\n';
};

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