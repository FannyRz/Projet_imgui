#include <imgui.h>
#include "App.hpp"
#include "chessBoard.hpp"
#include "quick_imgui/quick_imgui.hpp"

int main()
{
    float value{0.f};

    App app{};

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    // Charger la police par défaut avec une taille plus grande (EX: 40px)
    ImFont* bigDefaultFont = io.Fonts->AddFontDefault();
    bigDefaultFont->Scale = 1.5f;  
    // Font de l'echiquier
    ImFont* basicFont = io.Fonts->AddFontFromFileTTF("fonts/CHEQ_TT.TTF", 70.0f);
    IM_ASSERT(basicFont != nullptr);

    app._chessboard.set_font(basicFont);
    app._chessboard.set_position();

    quick_imgui::loop(
        "Chess",
        /* init: */
        [&]() {
        },

        /* loop: */
        [&]() {
            // ImGui::ShowDemoWindow(); // This opens a window which shows tons of examples of what you can do with ImGui. You should check it out! Also, you can use the "Item Picker" in the top menu of that demo window: then click on any widget and it will show you the corresponding code directly in your IDE!

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
                app._chessboard.reset_board();
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
        }
    );
}