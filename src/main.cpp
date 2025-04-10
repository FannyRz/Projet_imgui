#include <glad/glad.h>
#include <imgui.h>
#include "App.hpp"
#include "quick_imgui/quick_imgui.hpp"

int main(int argc, char* argv[])
{
    float value{0.f};

    App app{};

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    // Charger la police par défaut avec une taille plus grande (EX: 40px)
    ImFont* bigDefaultFont = io.Fonts->AddFontDefault();
    bigDefaultFont->Scale  = 1.5f;

    /*=============================================================*/
    quick_imgui::loop(

        "Quick ImGui",
        {

            .init =
                [&]() {
                    app.init_renderer2D(io);
                    app.init_renderer3D();
                },

            .loop = [&]() { app.loop(bigDefaultFont); },

            .key_callback = [&](int key, int scancode, int action, int mods) {
                app.key_callback(key, action);
            }

            // .mouse_button_callback    = [](int button, int action, int mods) { std::cout << "Button: " << button << " Action: " << action << " Mods: " << mods << '\n'; },
            // .cursor_position_callback = [](double xpos, double ypos) { std::cout << "Position: " << xpos << ' ' << ypos << '\n'; },
            // .scroll_callback          = [](double xoffset, double yoffset) { std::cout << "Scroll: " << xoffset << ' ' << yoffset << '\n'; },
            // .window_size_callback     = [](int width, int height) { std::cout << "Resized: " << width << ' ' << height << '\n'; },
        }
    );
}
