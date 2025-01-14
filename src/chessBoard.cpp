#include "chessBoard.hpp"
#include <imgui.h>
#include <cstddef>
#include <iostream>
#include "quick_imgui/quick_imgui.hpp"

void ChessBoard::draw_board()
{
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
            if (ImGui::Button("Vide", ImVec2{50.f, 50.f}))
                std::cout << "Clicked button (" << x << "," << y << ") \n";
            if (y != 7)
            {
                ImGui::SameLine();
            }
            ImGui::PopStyleColor();
        }
    }
}