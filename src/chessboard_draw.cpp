#include <imgui.h>
#include <iostream>
#include <memory>
#include <optional>
#include "chessBoard.hpp"
#include "pieces/pieces.hpp"

void ChessBoard::draw_board()
{
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{0.f, 0.f}); // Bordure entre les cases à zéro.
    for (int x{0}; x < 8; x++)
    {
        for (int y{0}; y < 8; y++)
        {
            bool FontActive = false;
            if (position_pieces[x][y] != nullptr)
            {
                ImGui::PushFont(this->get_font());
                ImGui::PushStyleColor(ImGuiCol_Text, (position_pieces[x][y]->get_color() == PieceColor::BLACK) ? IM_COL32(25, 25, 25, 255) : IM_COL32(250, 250, 250, 255));
                FontActive = true;
            }

            bool borderActivate = false;
            if ((x + y) % 2 == 0)
            {
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.8f, 0.4f, 0.0f, 1.0f}); // Orange foncé
            }
            else
            {
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{1.0f, 0.7f, 0.0f, 1.0f}); // Orange clair
            }

            if (_selected.has_value())
            {
                auto all_possible_move = this->get_all_possible_move();
                if (this->_enPassantPiece.has_value() && this->_selected->piece->get_type() == PieceType::PAWN)
                {
                    get_en_passant();
                }

                if (x == _selected->position_x && y == _selected->position_y) // case selectionne
                {
                    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 8.0f); // Bordure plus épaisse
                    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.5f, 0.0f, 0.5f, 1.0f));
                    borderActivate = true;
                }
                else if (std::find(all_possible_move.begin(), all_possible_move.end(), std::pair<int, int>{x, y}) != all_possible_move.end()) // cases possibles
                {
                    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 8.0f);
                    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.5f, 0.0f, 0.5f, 1.0f));
                    borderActivate = true;
                }
            }

            if (ImGui::Button((position_pieces[x][y] != nullptr ? from_type_to_char(x, y) + "##" + std::to_string(x) + "_" + std::to_string(y) : "##" + std::to_string(x) + "_" + std::to_string(y)).c_str(), ImVec2{80.f, 80.f}))
            {
                if (_selected.has_value() && x == _selected->position_x && y == _selected->position_y)
                {
                    this->deselect_selectedPiece();
                }
                else if (_selected.has_value() && can_move(x, y))
                {
                    move(_selected->position_x, _selected->position_y, x, y);
                    if (this->position_pieces[x][y]->get_type() == PieceType::PAWN && piece_at_the_end(x, y))
                    {
                        _selected_pawn = this->select_pawn_to_upgrade(x, y);
                        ImGui::OpenPopup("NEW PIECE");
                    }
                    if (game_won)
                    {
                        ImGui::OpenPopup("WIN");
                    }
                    this->deselect_selectedPiece();
                }
                else if (get_piece(x, y) && is_my_turn(x, y))
                {
                    this->select_selectedPiece(x, y);
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

            ImGui::PopStyleColor();

            if (FontActive)
            {
                ImGui::PopStyleColor();
                ImGui::PopFont();
            }
        }
    }

    // Affichage de la popup pour upgrade un pion
    print_popup(_selected_pawn);
    // Affichage de la popup quand on a manger un roi
    print_popup_win();

    ImGui::PopStyleVar();
}
