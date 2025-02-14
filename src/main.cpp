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
    ImFont* basicFont = io.Fonts->AddFontFromFileTTF("fonts/CHEQ_TT.TTF", 60.0f);
    IM_ASSERT(basicFont != nullptr);

    app._chessboard.set_position();

    quick_imgui::loop(
        "Chess",
        /* init: */
        [&]() {
            // std::vector<std::vector<std::unique_ptr<Piece>>> position_pieces[8][8];
            // set_position(position_pieces);
        },

        /* loop: */
        [&]() {
            // ImGui::ShowDemoWindow(); // This opens a window which shows tons of examples of what you can do with ImGui. You should check it out! Also, you can use the "Item Picker" in the top menu of that demo window: then click on any widget and it will show you the corresponding code directly in your IDE!

            ImGui::Begin("Example");

            ImGui::SliderFloat("My Value", &value, 0.f, 3.f);

            // if (piece != nullptr)
            // {
            //     ImGui::PushFont(main_font);
            //     ImGui::PushStyleColor(ImGuiCol_Text, (piece->get_color() == Color::Black) ? IM_COL32(25, 25, 25, 255) : IM_COL32(250, 250, 250, 255));
            // }
            app.update();

            // if (piece != nullptr)
            // {
            //     ImGui::PopFont();
            //     ImGui::PopStyleColor();
            // }

            ImGui::End();
        }
    );
}