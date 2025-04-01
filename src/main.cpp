#include <glad/glad.h>
#include <imgui.h>
#include <iostream>
#include "../lib/glimac/glimac/FilePath.hpp"
#include "../lib/glimac/glimac/Program.hpp"
#include "App.hpp"
#include "GLFW/glfw3.h"
#include "chessBoard.hpp"
#include "maths/maths.hpp"
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

    // Font
    app.get_chessboard().set_font(load_font_based_on_bernoulli(io));
    app.get_chessboard().get_chronometer().startChronometer();
    app.get_chessboard().set_position();

    /*=============================================================*/
    /* Initialize the library */

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    glimac::FilePath applicationPath(argv[0]);
    // glimac::Program  program = glimac::loadProgram("../../../fonts/color.vs.glsl", "../../../fonts/color.fs.glsl");

    // program.use();

    /*=============================================================*/
    GLuint vao{};
    quick_imgui::loop(

        "Quick ImGui",
        {
            .init =
                [&]() {
                    GLuint vbo{};
                    // Le VBO contient les données
                    glGenBuffers(1, &vbo);
                    glBindBuffer(GL_ARRAY_BUFFER, vbo);
                    GLfloat vertices[] = {-0.5f, -0.5f, 0.5f, -0.5f, 0.0f, 0.5f};
                    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
                    glBindBuffer(GL_ARRAY_BUFFER, 0);

                    // Le VAO décrit les données
                    glGenVertexArrays(1, &vao);
                    glBindVertexArray(vao);
                    const GLuint VERTEX_ATTR_POSITION = 0;
                    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
                    glBindBuffer(GL_ARRAY_BUFFER, vbo);
                    glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr);
                    glBindBuffer(GL_ARRAY_BUFFER, 0);
                    glBindVertexArray(0);
                },

            .loop = [&]() {
        glClearColor(1., 0.5, 0.5, 1.);
        glClear(GL_COLOR_BUFFER_BIT);


        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

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

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 2);
        glBindVertexArray(0);

        ImGui::End(); },

            // .key_callback             = [](int key, int scancode, int action, int mods) { std::cout << "Key: " << key << " Scancode: " << scancode << " Action: " << action << " Mods: " << mods << '\n'; },
            // .mouse_button_callback    = [](int button, int action, int mods) { std::cout << "Button: " << button << " Action: " << action << " Mods: " << mods << '\n'; },
            // .cursor_position_callback = [](double xpos, double ypos) { std::cout << "Position: " << xpos << ' ' << ypos << '\n'; },
            // .scroll_callback          = [](double xoffset, double yoffset) { std::cout << "Scroll: " << xoffset << ' ' << yoffset << '\n'; },
            // .window_size_callback     = [](int width, int height) { std::cout << "Resized: " << width << ' ' << height << '\n'; },
        }
    );
}
