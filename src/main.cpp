#include <imgui.h>
#include <iostream>
#include "App.hpp"
#include "chessBoard.hpp"
#include "glad/glad.h"
#include "quick_imgui/quick_imgui.hpp"
#include "maths/maths.hpp"

int main()
{
    float value{0.f};

    App app{};

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    // Charger la police par défaut avec une taille plus grande (EX: 40px)
    ImFont* bigDefaultFont = io.Fonts->AddFontDefault();
    bigDefaultFont->Scale  = 1.5f;

    // Font
    app.get_chessboard().set_font(load_font_based_on_bernoulli(io));
    app.get_chessboard().set_position();

    quick_imgui::loop(
        "Quick ImGui",
        {
            // .init = []() { std::cout << "Init\n"; },

            .loop = [&]() {
                ImGui::Begin("Le jeu d'echec de la mort qui tue !!");

                // Afficher l'échiquier en premier
                ImGui::BeginGroup();
                app.update();
                ImGui::EndGroup();

                // Garder les boutons sur la même ligne
                ImGui::SameLine();

                // Ajouter un espace pour pousser les boutons à droite
                ImGui::Dummy(ImVec2(20, 0));
                ImGui::SameLine();
                ImGui::BeginGroup();
                ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 10)); // Augmente l'espacement interne du bouton
                ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(20, 20));  // Espacement entre les boutons
                ImGui::PushFont(bigDefaultFont);
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.8f, 0.4f, 0.0f, 1.0f});
                ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 0, 0, 255));
                if (ImGui::Button("Recommencer une partie !", ImVec2(250, 50)))
                {
                    app.get_chessboard().reset_board();
                }
                if (ImGui::Button("Quitter la partie !", ImVec2(250, 50)))
                {
                    exit(0);
                }
                ImGui::PopStyleColor(2);
                ImGui::PopStyleVar(2);
                ImGui::PopFont();
                ImGui::EndGroup();

                

                ImGui::End();
            },

            // .key_callback             = [](int key, int scancode, int action, int mods) { std::cout << "Key: " << key << " Scancode: " << scancode << " Action: " << action << " Mods: " << mods << '\n'; },
            // .mouse_button_callback    = [](int button, int action, int mods) { std::cout << "Button: " << button << " Action: " << action << " Mods: " << mods << '\n'; },
            // .cursor_position_callback = [](double xpos, double ypos) { std::cout << "Position: " << xpos << ' ' << ypos << '\n'; },
            // .scroll_callback          = [](double xoffset, double yoffset) { std::cout << "Scroll: " << xoffset << ' ' << yoffset << '\n'; },
            // .window_size_callback     = [](int width, int height) { std::cout << "Resized: " << width << ' ' << height << '\n'; },
        }
    );
}