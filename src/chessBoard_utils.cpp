#include <imgui.h>
#include <iostream>
#include <memory>
#include <optional>
#include "chessBoard.hpp"
#include "pieces/bishop.hpp"
#include "pieces/king.hpp"
#include "pieces/knight.hpp"
#include "pieces/pawn.hpp"
#include "pieces/pieces.hpp"
#include "pieces/queen.hpp"
#include "pieces/rook.hpp"
#include "utils.hpp"
#include "maths/maths.hpp"

/* ------------------------------ font ------------------------------ */
std::string ChessBoard::from_type_to_char(int x, int y) const
{
    switch (this->position_pieces[x][y]->get_type())
    {
    case PieceType::PAWN:
        return (this->position_pieces[x][y]->get_color() == PieceColor::WHITE) ? "P" : "O";
        break;
    case PieceType::ROOK:
        return (this->position_pieces[x][y]->get_color() == PieceColor::WHITE) ? "R" : "T";
        break;
    case PieceType::KNIGHT:
        return (this->position_pieces[x][y]->get_color() == PieceColor::WHITE) ? "H" : "J";
        break;
    case PieceType::BISHOP:
        return (this->position_pieces[x][y]->get_color() == PieceColor::WHITE) ? "B" : "N";
        break;
    case PieceType::QUEEN:
        return (this->position_pieces[x][y]->get_color() == PieceColor::WHITE) ? "Q" : "W";
        break;
    case PieceType::KING:
        return (this->position_pieces[x][y]->get_color() == PieceColor::WHITE) ? "K" : "L";
        break;
    default:
        std::cerr << "Erreur: type de pièce inconnu /n";
        return "";
    }
}

/* ------------------------------ initialisation ------------------------------ */
void ChessBoard::set_position()
{
    // tour
    this->position_pieces[0][0] = std::make_unique<Rook>(PieceColor::BLACK, 0, 0);
    this->position_pieces[0][7] = std::make_unique<Rook>(PieceColor::BLACK, 0, 7);
    this->position_pieces[7][0] = std::make_unique<Rook>(PieceColor::WHITE, 7, 0);
    this->position_pieces[7][7] = std::make_unique<Rook>(PieceColor::WHITE, 7, 7);

    // cavalier
    this->position_pieces[0][1] = std::make_unique<Knight>(PieceColor::BLACK, 0, 1);
    this->position_pieces[0][6] = std::make_unique<Knight>(PieceColor::BLACK, 0, 6);
    this->position_pieces[7][1] = std::make_unique<Knight>(PieceColor::WHITE, 7, 1);
    this->position_pieces[7][6] = std::make_unique<Knight>(PieceColor::WHITE, 7, 6);

    // fou
    this->position_pieces[0][2] = std::make_unique<Bishop>(PieceColor::BLACK, 0, 2);
    this->position_pieces[0][5] = std::make_unique<Bishop>(PieceColor::BLACK, 0, 5);
    this->position_pieces[7][2] = std::make_unique<Bishop>(PieceColor::WHITE, 7, 2);
    this->position_pieces[7][5] = std::make_unique<Bishop>(PieceColor::WHITE, 7, 5);

    // dame
    this->position_pieces[0][3] = std::make_unique<Queen>(PieceColor::BLACK, 0, 3);
    this->position_pieces[7][3] = std::make_unique<Queen>(PieceColor::WHITE, 7, 3);

    // roi
    this->position_pieces[0][4] = std::make_unique<King>(PieceColor::BLACK, 0, 4);
    this->position_pieces[7][4] = std::make_unique<King>(PieceColor::WHITE, 7, 4);

    // pion
    for (int i{0}; i < 8; i++)
    {
        this->position_pieces[1][i] = std::make_unique<Pawn>(PieceColor::WHITE, 1, i);
        this->position_pieces[6][i] = std::make_unique<Pawn>(PieceColor::BLACK, 6, i);
    }
}

/* ------------------------------ some utils functions ------------------------------ */
bool ChessBoard::get_piece(int x, int y)
{
    return is_on_the_chessboard(x, y) && this->position_pieces[x][y] != nullptr;
}

bool ChessBoard::is_my_turn(int x, int y)
{
    return (this->position_pieces[x][y]->get_color() == PieceColor::WHITE && get_is_white_turn()) || (this->position_pieces[x][y]->get_color() == PieceColor::BLACK && !get_is_white_turn());
}

/* ------------------------------ popup ------------------------------ */
void ChessBoard::print_popup(std::optional<SelectedPiece> selected)
{
    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    ImGui::SetNextWindowSize(ImVec2(500, 140));

    if (ImGui::BeginPopupModal("NEW PIECE", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("Choisis ta pièce !");
        ImGui::Separator();

        ImGui::PushFont(this->get_font());

        std::vector<PieceButton> buttons = {
            {.type = PieceType::QUEEN, .white_label = "Q", .black_label = "W", .color = ImVec4{0.8f, 0.4f, 0.0f, 1.0f}},
            {.type = PieceType::ROOK, .white_label = "R", .black_label = "T", .color = ImVec4{1.0f, 0.7f, 0.0f, 1.0f}},
            {.type = PieceType::BISHOP, .white_label = "B", .black_label = "N", .color = ImVec4{0.8f, 0.4f, 0.0f, 1.0f}},
            {.type = PieceType::KNIGHT, .white_label = "H", .black_label = "J", .color = ImVec4{1.0f, 0.7f, 0.0f, 1.0f}}
        };

        ImGui::PushStyleColor(ImGuiCol_Text, (selected->piececolor == PieceColor::BLACK) ? IM_COL32(25, 25, 25, 255) : IM_COL32(250, 250, 250, 255));

        for (size_t i{}; i < buttons.size(); i++)
        {
            const auto& btn = buttons[i];

            ImGui::PushStyleColor(ImGuiCol_Button, btn.color);
            if (ImGui::Button(selected->piececolor == PieceColor::WHITE ? btn.white_label : btn.black_label, ImVec2(120, 0)))
            {
                // changer la piece en fonction de la case sur laquelle on clique
                change_piece(selected->position_x, selected->position_y, btn.type, selected->piececolor);
                ImGui::CloseCurrentPopup();
            }
            ImGui::PopStyleColor();

            if (i < buttons.size() - 1)
                ImGui::SameLine();
        }

        ImGui::PopStyleColor();
        ImGui::PopFont();
        ImGui::EndPopup();
    }
}

void ChessBoard::print_popup_win()
{
    // Affichage de la popup WIN
    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    ImGui::SetNextWindowSize(ImVec2(370, 170));

    if (ImGui::BeginPopupModal("WIN", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text((winner_color == PieceColor::WHITE) ? "Bravo, les Blancs ont gagné !" : "Bravo, les Noirs ont gagné !");
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(20, 20));
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.8f, 0.4f, 0.0f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));

        if (ImGui::Button("Recommencer une partie !", ImVec2(250, 40)))
        {
            game_won = false; // Fermer la popup
            ImGui::CloseCurrentPopup();
            reset_board();
        }
        if (ImGui::Button("Quitter la partie !", ImVec2(250, 40)))
        {
            exit(0);
        }

        ImGui::PopStyleVar();
        ImGui::PopStyleColor(2);
        ImGui::EndPopup();
    }
}

/* ------------------------------ reset du jeu ------------------------------ */
void ChessBoard::reset_board()
{
    // Réinitialiser l'état du jeu
    game_won       = false;
    is_white_turn  = true;
    _selected      = std::nullopt;
    _selected_pawn = std::nullopt;

    // Effacer toutes les pièces
    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            position_pieces[x][y] = nullptr;
        }
    }

    set_position();
}