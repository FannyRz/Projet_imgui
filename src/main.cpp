#include <imgui.h>
#include <cstddef>
#include <iostream>
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
    ImFont* basicFont = io.Fonts->AddFontFromFileTTF("fonts/CHEQ_TT.TTF", 40.0f);
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

            ImGui::Begin("Example");

            ImGui::SliderFloat("My Value", &value, 0.f, 3.f);

            app.update();

            ImGui::End();
        }
    );
}