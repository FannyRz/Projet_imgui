#include "App.hpp"
#include <imgui.h>
#include <cstddef>
#include <iostream>
#include "pieces.hpp"
#include "quick_imgui/quick_imgui.hpp"

void App::update()
{
    _renderer.render_board(_chessboard);
}
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{0.f, 0.f}); // Bordure entre les cases à zéro.
    for (int x{0}; x < 8; x++)
    {
        for (int y{0}; y < 8; y++)
        {
            if ((x + y) % 2 == 0)
            {
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.f, 0.f, 0.f, 1.f});
            }
            else
            {
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{1.f, 1.f, 1.f, 1.f});
            }

            // Piece* piece = board.get_pîece(x, y);  Code fait par Jules qui demande si sur une case il y a une piece ou non
            std::string piece_label = position_pieces[x][y];

            if (ImGui::Button((piece_label != "V" ? piece_label : "Vide##" + std::to_string(x) + "_" + std::to_string(y)).c_str(), ImVec2{50.f, 50.f})) // Le "##" permet d'ajputer un identifiant unique sur chaque bouton sans qu'il apparaisse sur le bouton.
            {
                std::cout << "Clicked button (" << x << "," << y << ") \n";
            }
            if (y != 7)
            {
                ImGui::SameLine();
            }
            ImGui::PopStyleColor();
        }
    }
    ImGui::PopStyleVar();
}
