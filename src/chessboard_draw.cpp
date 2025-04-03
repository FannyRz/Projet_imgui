#include <imgui.h>
#include <chrono>
#include <iostream>
#include <memory>
#include <optional>
#include <thread>
#include "chessBoard.hpp"
#include "maths/maths.hpp"
#include "pieces/pawn.hpp"
#include "pieces/pieces.hpp"

void ChessBoard::draw_board()
{
    static double exponentielle_time = 0.0;   // Temps de la fonction exponentielle
    static double elapsed_time       = 0.0;   // Temps écoulé pour comparaison avec exponentielle_time
    static bool   pion_placed        = false; // Variable pour vérifier si "Pion ajouté" a déjà été affiché

    // Calcul du délai d'attente (en secondes) à partir de la fonction exponentielle
    double lambda = 1.0 / 60.0; // Paramètre de la loi exponentielle
    double min    = 0.0;        // Valeur minimale pour éviter des délais trop courts
    double max    = 10.0;       // Valeur maximale pour limiter la durée d'attente

    // Ne calculer l'exponentielle que lors de la première itération
    if (exponentielle_time == 0.0)
    {
        exponentielle_time = exponentielle(lambda, min, max);
        std::cout << "Exponentielle Time Calculé: " << exponentielle_time << " secondes." << '\n';
    }

    // Récupérer le temps écoulé (en secondes)
    double current_time = ImGui::GetTime(); // Récupère le temps actuel (en secondes)

    if (elapsed_time == 0.0)
    {
        // Initialisation du temps au début
        elapsed_time = current_time;
        //std::cout << "Temps initialisé à: " << elapsed_time << std::endl;
    }

    // Calculer le temps écoulé depuis la dernière mise à jour
    double delta_time = current_time - elapsed_time;

    // Debug : afficher le temps écoulé et vérifier la logique
    //std::cout << "Temps actuel: " << current_time << ", Elapsed Time: " << elapsed_time << ", Delta Time: " << delta_time << std::endl;
    //std::cout << "Ajout d'un pion après " << 2 * exponentielle_time << " secondes." << std::endl;

    if (delta_time >= 2*exponentielle_time && !pion_placed)
    {
        // Réinitialiser elapsed_time après le calcul du delta_time
        elapsed_time = current_time; // Mettre à jour elapsed_time pour le prochain cycle
        std::cout << "Ajout d'un pion après " << 2 * exponentielle_time << " secondes." << '\n';

        for (int x = 0; x < 8; ++x)
        {
            for (int y = 0; y < 8; ++y)
            {
                // Vérifier si la case est vide (aucune pièce présente)
                if (position_pieces[x][y] == nullptr)
                {
                    // Attendre le temps généré par exponentielle_time
                    std::this_thread::sleep_for(std::chrono::duration<double>(exponentielle_time)); // Attendre avant d'ajouter le pion
                    std::cout << "Événement après " << exponentielle_time << " secondes." << '\n';

                    // Ajouter un pion à cette case
                    position_pieces[x][y] = std::make_unique<Pawn>(PieceColor::WHITE, x, y); // Ajouter un pion blanc
                    pion_placed           = true;                                            // Marquer que le pion a été placé
                    break;                                                                   // Sortir de la boucle une fois qu'un pion est placé
                }
            }
            if (pion_placed)
            {
                break; // Sortir de la boucle externe une fois que le pion est placé
            }
        }
    }

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{0.f, 0.f}); // Bordure entre les cases à zéro.
    for (int x{0}; x < 8; x++)
    {
        for (int y{0}; y < 8; y++)
        {
            bool FontActive = false;
            if (position_pieces[x][y] != nullptr)
            {
                ImGui::PushFont(this->get_font());
                ImGui::PushStyleColor(ImGuiCol_Text, (position_pieces[x][y]->get_color() == PieceColor::BLACK) ? IM_COL32(25, 25, 25, 255) : IM_COL32(250, 250, 250, 255));
                FontActive = true;
            }

            bool borderActivate = false;
            if ((x + y) % 2 == 0)
            {
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.8f, 0.4f, 0.0f, 1.0f}); // Orange foncé
            }
            else
            {
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{1.0f, 0.7f, 0.0f, 1.0f}); // Orange clair
            }

            if (_selected.has_value())
            {
                auto all_possible_move = this->get_all_possible_move();
                if (this->_enPassantPiece.has_value() && this->_selected->piece->get_type() == PieceType::PAWN)
                {
                    get_en_passant();
                }

                if (x == _selected->position_x && y == _selected->position_y) // case selectionne
                {
                    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 8.0f); // Bordure plus épaisse
                    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.5f, 0.0f, 0.5f, 1.0f));
                    borderActivate = true;
                }
                else if (std::find(all_possible_move.begin(), all_possible_move.end(), std::pair<int, int>{x, y}) != all_possible_move.end()) // cases possibles
                {
                    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 8.0f);
                    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.5f, 0.0f, 0.5f, 1.0f));
                    borderActivate = true;
                }
            }

            if (ImGui::Button((position_pieces[x][y] != nullptr ? from_type_to_char(x, y) + "##" + std::to_string(x) + "_" + std::to_string(y) : "##" + std::to_string(x) + "_" + std::to_string(y)).c_str(), ImVec2{80.f, 80.f}))
            {
                if (_selected.has_value() && x == _selected->position_x && y == _selected->position_y)
                {
                    this->deselect_selectedPiece();
                }
                else if (_selected.has_value() && can_move(x, y))
                {
                    move(_selected->position_x, _selected->position_y, x, y);
                    if (!_loiDeGamma.isDisplayChronometer)
                    {
                        this->_loiDeGamma.increment_moveTimeChronometer();
                    }
                    if (this->position_pieces[x][y]->get_type() == PieceType::PAWN && piece_at_the_end(x, y))
                    {
                        _selectedPawn              = this->select_pawn_to_upgrade(x, y);
                        bool is_random_upgrate_pawn = bernoulli(0.7);
                        std::cout << is_random_upgrate_pawn << '\n';

                        if (is_random_upgrate_pawn)
                        {
                            ImGui::OpenPopup("NEW PIECE");
                        }
                        else
                        {
                            change_piece(x, y, select_piece_promotion(), _selectedPawn->piece->get_color());
                        }
                    }
                    if (game_won)
                    {
                        ImGui::OpenPopup("WIN");
                    }
                    this->deselect_selectedPiece();
                }
                else if (get_piece(x, y) && is_my_turn(x, y))
                {
                    this->select_selectedPiece(x, y);
                }
            }

            if (borderActivate)
            {
                ImGui::PopStyleColor();
                ImGui::PopStyleVar();
            }

            if (y != 7)
            {
                ImGui::SameLine();
            }

            ImGui::PopStyleColor();

            if (FontActive)
            {
                ImGui::PopStyleColor();
                ImGui::PopFont();
            }
        }
    }

    if (_loiDeGamma.isDisplayChronometer)
    {
        _chronometer.display_game_time();
    }

    // Affichage de la popup pour upgrade un pion
    print_popup(_selectedPawn);
    // Affichage de la popup quand on a manger un roi
    print_popup_win();

    ImGui::PopStyleVar();
}
