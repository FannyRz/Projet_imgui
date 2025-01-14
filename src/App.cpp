#include "App.hpp"
#include <imgui.h>
#include <cstddef>
#include <iostream>
#include "quick_imgui/quick_imgui.hpp"

void App::draw_board()
{
    for (int i{1}; i <= 64; i++)
    {
        ImGui::PushID(i);
        if (ImGui::Button("Vide", ImVec2{50.f, 50.f}))
            std::cout << "Clicked button" << i << "\n";
        ImGui::PopID();
        if (i % 8 != 0)
        {
            ImGui::SameLine();
        }
    }

    // ImGui::PushID(1);
    // if (ImGui::Button("Tour", ImVec2{50.f, 50.f}))
    //     std::cout << "Clicked button 1\n";
    // ImGui::PopID();
    // ImGui::SameLine();

    // ImGui::PushID(2);
    // if (ImGui::Button("Cavalier", ImVec2{50.f, 50.f}))
    //     std::cout << "Clicked button 2\n";
    // ImGui::PopID();
    // ImGui::SameLine();

    // ImGui::PushID(3);
    // if (ImGui::Button("Fou", ImVec2{50.f, 50.f}))
    //     std::cout << "Clicked button 3\n";
    // ImGui::PopID();
    // ImGui::SameLine();

    // ImGui::PushID(4);
    // if (ImGui::Button("Dame", ImVec2{50.f, 50.f}))
    //     std::cout << "Clicked button 4\n";
    // ImGui::PopID();
    // ImGui::SameLine();

    // ImGui::PushID(5);
    // if (ImGui::Button("Roi", ImVec2{50.f, 50.f}))
    //     std::cout << "Clicked button 5\n";
    // ImGui::PopID();
    // ImGui::SameLine();

    // ImGui::PushID(6);
    // if (ImGui::Button("Fou", ImVec2{50.f, 50.f}))
    //     std::cout << "Clicked button 6\n";
    // ImGui::PopID();
    // ImGui::SameLine();

    // ImGui::PushID(7);
    // if (ImGui::Button("Cavalier", ImVec2{50.f, 50.f}))
    //     std::cout << "Clicked button 7\n";
    // ImGui::PopID();
    // ImGui::SameLine();

    // ImGui::PushID(8);
    // if (ImGui::Button("Tour", ImVec2{50.f, 50.f}))
    //     std::cout << "Clicked button 8\n";
    // ImGui::PopID();
    // ImGui::SameLine();
}