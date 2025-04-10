#include <imgui.h>
#include <iostream>
#include <memory>
#include <optional>
#include "chessBoard.hpp"
#include "maths/maths.hpp"
#include "pieces/bishop.hpp"
#include "pieces/king.hpp"
#include "pieces/knight.hpp"
#include "pieces/pawn.hpp"
#include "pieces/pieces.hpp"
#include "pieces/queen.hpp"
#include "pieces/rook.hpp"
#include "utils.hpp"

/* ------------------------------ font ------------------------------ */
std::string ChessBoard::from_type_to_char(int x, int y) const
{
    switch (this->_positionPieces[x][y]->get_type())
    {
    case PieceType::PAWN:
        return (this->_positionPieces[x][y]->get_color() == PieceColor::WHITE) ? "P" : "O";
        break;
    case PieceType::ROOK:
        return (this->_positionPieces[x][y]->get_color() == PieceColor::WHITE) ? "R" : "T";
        break;
    case PieceType::KNIGHT:
        return (this->_positionPieces[x][y]->get_color() == PieceColor::WHITE) ? "H" : "J";
        break;
    case PieceType::BISHOP:
        return (this->_positionPieces[x][y]->get_color() == PieceColor::WHITE) ? "B" : "N";
        break;
    case PieceType::QUEEN:
        return (this->_positionPieces[x][y]->get_color() == PieceColor::WHITE) ? "Q" : "W";
        break;
    case PieceType::KING:
        return (this->_positionPieces[x][y]->get_color() == PieceColor::WHITE) ? "K" : "L";
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
    this->_positionPieces[0][0] = std::make_unique<Rook>(PieceColor::BLACK, 0, 0);
    this->_positionPieces[0][7] = std::make_unique<Rook>(PieceColor::BLACK, 0, 7);
    this->_positionPieces[7][0] = std::make_unique<Rook>(PieceColor::WHITE, 7, 0);
    this->_positionPieces[7][7] = std::make_unique<Rook>(PieceColor::WHITE, 7, 7);

    // cavalier
    this->_positionPieces[0][1] = std::make_unique<Knight>(PieceColor::BLACK, 0, 1);
    this->_positionPieces[0][6] = std::make_unique<Knight>(PieceColor::BLACK, 0, 6);
    this->_positionPieces[7][1] = std::make_unique<Knight>(PieceColor::WHITE, 7, 1);
    this->_positionPieces[7][6] = std::make_unique<Knight>(PieceColor::WHITE, 7, 6);

    // fou
    this->_positionPieces[0][2] = std::make_unique<Bishop>(PieceColor::BLACK, 0, 2);
    this->_positionPieces[0][5] = std::make_unique<Bishop>(PieceColor::BLACK, 0, 5);
    this->_positionPieces[7][2] = std::make_unique<Bishop>(PieceColor::WHITE, 7, 2);
    this->_positionPieces[7][5] = std::make_unique<Bishop>(PieceColor::WHITE, 7, 5);

    // dame
    this->_positionPieces[0][3] = std::make_unique<Queen>(PieceColor::BLACK, 0, 3);
    this->_positionPieces[7][3] = std::make_unique<Queen>(PieceColor::WHITE, 7, 3);

    // roi
    this->_positionPieces[0][4] = std::make_unique<King>(PieceColor::BLACK, 0, 4);
    this->_positionPieces[7][4] = std::make_unique<King>(PieceColor::WHITE, 7, 4);

    // pion
    for (int i{0}; i < 8; i++)
    {
        this->_positionPieces[1][i] = std::make_unique<Pawn>(PieceColor::BLACK, 1, i);
        this->_positionPieces[6][i] = std::make_unique<Pawn>(PieceColor::WHITE, 6, i);
    }
}

/* ------------------------------ some utils functions ------------------------------ */
bool ChessBoard::get_piece(int x, int y)
{
    return is_on_the_chessboard(x, y) && this->_positionPieces[x][y] != nullptr;
}

bool ChessBoard::is_my_turn(int x, int y)
{
    return (this->_positionPieces[x][y]->get_color() == PieceColor::WHITE && get_is_white_turn()) || (this->_positionPieces[x][y]->get_color() == PieceColor::BLACK && !get_is_white_turn());
}

/* ------------------------------ popups ------------------------------ */
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
            {._type = PieceType::QUEEN, ._whiteLabel = "Q", ._blackLabel = "W", ._color = ImVec4{0.8f, 0.4f, 0.0f, 1.0f}},
            {._type = PieceType::ROOK, ._whiteLabel = "R", ._blackLabel = "T", ._color = ImVec4{1.0f, 0.7f, 0.0f, 1.0f}},
            {._type = PieceType::BISHOP, ._whiteLabel = "B", ._blackLabel = "N", ._color = ImVec4{0.8f, 0.4f, 0.0f, 1.0f}},
            {._type = PieceType::KNIGHT, ._whiteLabel = "H", ._blackLabel = "J", ._color = ImVec4{1.0f, 0.7f, 0.0f, 1.0f}}
        };

        ImGui::PushStyleColor(ImGuiCol_Text, (selected->_piececolor == PieceColor::BLACK) ? IM_COL32(25, 25, 25, 255) : IM_COL32(250, 250, 250, 255));

        for (size_t i{}; i < buttons.size(); i++)
        {
            const auto& btn = buttons[i];

            ImGui::PushStyleColor(ImGuiCol_Button, btn._color);
            if (ImGui::Button(selected->_piececolor == PieceColor::WHITE ? btn._whiteLabel : btn._blackLabel, ImVec2(120, 0)))
            {
                // changer la piece en fonction de la case sur laquelle on clique
                change_piece(selected->_position_x, selected->_position_y, btn._type, selected->_piececolor);
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
        ImGui::Text((_winnerColor == PieceColor::WHITE) ? "Bravo, les Blancs ont gagné !" : "Bravo, les Noirs ont gagné !");
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(20, 20));
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.8f, 0.4f, 0.0f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));

        if (ImGui::Button("Recommencer une partie !", ImVec2(250, 40)))
        {
            is_game_won = false; // Fermer la popup
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
    is_game_won   = false;
    is_white_turn = true;
    _selected     = std::nullopt;
    _selectedPawn = std::nullopt;

    // Effacer toutes les pièces
    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            _positionPieces[x][y] = nullptr;
        }
    }

    set_position();
    _chronometer.reset_chronometer();
    _loiDeGamma.reset_loiDeGamma();
}