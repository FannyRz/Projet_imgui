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
    io.Fonts->AddFontDefault();
    ImFont* basicFont = io.Fonts->AddFontFromFileTTF("fonts/CHEQ_TT.TTF", 70.0f);
    IM_ASSERT(basicFont != nullptr);

    app.get_chessboard().set_font(basicFont);
    app.get_chessboard().set_position();

    quick_imgui::loop(
        "Chess",
        /* init: */
        [&]() {
        },

        /* loop: */
        [&]() {
            // ImGui::ShowDemoWindow(); // This opens a window which shows tons of examples of what you can do with ImGui. You should check it out! Also, you can use the "Item Picker" in the top menu of that demo window: then click on any widget and it will show you the corresponding code directly in your IDE!

            ImGui::Begin("Le jeu d'echec de la mort qui tue !!");

            app.update();

            ImGui::End();
        }
    );
}