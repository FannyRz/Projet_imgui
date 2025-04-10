#include "App.hpp"
#include <imgui.h>

void App::init_renderer2D(ImGuiIO& io)
{
    // Font
    this->_chessboard.set_font(load_font_based_on_bernoulli(io));
    this->_chessboard.get_chronometer().start_chronometer();
    this->_chessboard.set_position();

    // Couleur fenetre
    ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = ImVec4(0.5f, 0.2f, 0.f, 1.0f);
}

void App::init_renderer3D()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH);

    this->_renderer.setup_obj();
    this->_renderer.setup_shader();
    this->_renderer.get_skybox().setup_shader();
    this->_renderer.get_skybox().setup_skybox();
    this->_renderer.get_skybox().load_cubemap();
}

void App::update()
{
    _renderer.render_board(_chessboard);
}

void App::loop(ImFont* bigDefaultFont)
{
    glClearColor(1., 0.5, 0.5, 1.);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->_renderer.draw_chessboard();
    this->_renderer.draw_pieces(this->_chessboard.get_position_pieces());
    this->_renderer.render_skybox();

    ImGui::Begin("Le jeu d'echec de la mort qui tue !!");

    // Afficher l'échiquier en premier
    ImGui::BeginGroup();
    update();
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
        this->_chessboard.reset_board();
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

    this->_renderer.get_camera().handle_camera_input();
}

void App::key_callback(int key, int action)
{
    if (action == GLFW_PRESS)
    {
        this->_renderer.get_camera().get_keysDown().insert(key);
    }
    else if (action == GLFW_RELEASE)
    {
        this->_renderer.get_camera().get_keysDown().erase(key);
    }
}