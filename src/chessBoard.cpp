#include "chessBoard.hpp"
#include <imgui.h>
#include <iostream>
#include <memory>
#include <optional>
#include "pieces/bishop.hpp"
#include "pieces/king.hpp"
#include "pieces/knight.hpp"
#include "pieces/pawn.hpp"
#include "pieces/pieces.hpp"
#include "pieces/queen.hpp"
#include "pieces/rook.hpp"
#include "utils.hpp"

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
        this->position_pieces[1][i] = std::make_unique<Pawn>(PieceColor::BLACK, 1, i);
        this->position_pieces[6][i] = std::make_unique<Pawn>(PieceColor::WHITE, 6, i);
    }
}

void ChessBoard::deselect()
{
    _selected = std::nullopt;
}

void ChessBoard::select(int x, int y)
{
    SelectedPiece selectedPiece{};
    selectedPiece.piece             = position_pieces[x][y].get();
    selectedPiece.position_x        = x;
    selectedPiece.position_y        = y;
    selectedPiece.piececolor        = position_pieces[x][y]->get_color();
    selectedPiece.all_possible_move = position_pieces[x][y]->all_possible_move(this->position_pieces);
    this->_selected                 = selectedPiece;
    // std::cout << from_type_to_char(x, y) << '\n';
    // displaytab(selectedPiece.all_possible_move);
}

std::optional<SelectedPiece> ChessBoard::select_pawn(int x, int y)
{
    SelectedPiece selectedPiece{};
    selectedPiece.piece      = position_pieces[x][y].get();
    selectedPiece.position_x = x;
    selectedPiece.position_y = y;
    selectedPiece.piececolor = position_pieces[x][y]->get_color();
    this->_selected_pawn     = selectedPiece;
    return {selectedPiece};
}

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
    }
}

void ChessBoard::move(int x, int y, int new_x, int new_y)
{
    // Vérifie s'il y a une pièce sur la case d'arrivée
    if (get_piece(new_x, new_y))
    {
        // Vérifie si c'est un roi
        if (this->position_pieces[new_x][new_y]->get_type() == PieceType::KING)
        {
            game_won = true;
            winner_color = this->position_pieces[x][y]->get_color();
        }
    }
    this->position_pieces[x][y]->set_positionx(new_x);
    this->position_pieces[x][y]->set_positiony(new_y);
    this->position_pieces[new_x][new_y] = std::move(this->position_pieces[x][y]);
    this->position_pieces[x][y]         = nullptr;
    set_is_white_turn(!is_white_turn);
}

bool ChessBoard::can_move(int new_x, int new_y)
{
    return std::find(this->_selected->all_possible_move.begin(), this->_selected->all_possible_move.end(), std::make_pair(new_x, new_y)) != this->_selected->all_possible_move.end();
}

bool ChessBoard::get_piece(int x, int y)
{
    return this->position_pieces[x][y] != nullptr;
}

bool ChessBoard::is_my_turn(int x, int y)
{
    return (this->position_pieces[x][y]->get_color() == PieceColor::WHITE && get_is_white_turn()) || (this->position_pieces[x][y]->get_color() == PieceColor::BLACK && !get_is_white_turn());
}

bool ChessBoard::piece_at_the_end(int x, int y)
{
    return (this->position_pieces[x][y]->get_positionx() == 0 && this->position_pieces[x][y]->get_color() == PieceColor::WHITE) || (this->position_pieces[x][y]->get_positionx() == 7 && this->position_pieces[x][y]->get_color() == PieceColor::BLACK);
}

void ChessBoard::change_piece(int x, int y, PieceType nouveau_type, PieceColor color)
{
    // Vérifier que la case contient bien une pièce
    if (position_pieces[x][y] == nullptr)
        return;

    // Créer la nouvelle pièce selon le type demandé
    switch (nouveau_type)
    {
    case PieceType::QUEEN:
        position_pieces[x][y] = std::make_unique<Queen>(color, x, y);
        break;
    case PieceType::ROOK:
        position_pieces[x][y] = std::make_unique<Rook>(color, x, y);
        break;
    case PieceType::BISHOP:
        position_pieces[x][y] = std::make_unique<Bishop>(color, x, y);
        break;
    case PieceType::KNIGHT:
        position_pieces[x][y] = std::make_unique<Knight>(color, x, y);
        break;
    default:
        return;
    }
}

void ChessBoard::draw_board()
{
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
                    this->deselect();
                }
                else if (_selected.has_value() && can_move(x, y))
                {
                    move(_selected->position_x, _selected->position_y, x, y);
                    if (this->position_pieces[x][y]->get_type() == PieceType::PAWN && piece_at_the_end(x, y))
                    {
                        _selected_pawn = this->select_pawn(x, y);
                        ImGui::OpenPopup("NEW PIECE");
                    }
                    if (game_won)
                    {
                        ImGui::OpenPopup("WIN");
                    }
                    this->deselect();
                }
                else if (get_piece(x, y) && is_my_turn(x, y))
                {
                    this->select(x, y);
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

    //Affichage de la popup pour upgrade un pion
    print_popup(_selected_pawn);
    //Affichage de la popup quand on a manger un roi
    print_popup_win();

    ImGui::PopStyleVar();
}

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

        struct PieceButton {
            PieceType   type;
            const char* white_label;
            const char* black_label;
            ImVec4      color;
        };

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
                // changer la piece en fonction de sur la case ou l'on clic
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
    ImGui::SetNextWindowSize(ImVec2(250, 70));

    if (ImGui::BeginPopupModal("WIN", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text((winner_color == PieceColor::WHITE) ? "Bravo, les Blancs ont gagné !" : "Bravo, les Noirs ont gagné !");

        if (ImGui::Button("Recommancer une partie !"))
        {
            game_won = false; // Fermer la popup
            ImGui::CloseCurrentPopup();
            reset_board();
        }

        ImGui::EndPopup();
    }
}

void ChessBoard::reset_board()
{
    // Réinitialiser l'état du jeu
    game_won = false;
    is_white_turn = true;
    _selected = std::nullopt;
    _selected_pawn = std::nullopt;

    // Effacer toutes les pièces
    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            position_pieces[x][y] = nullptr;
        }
    }

    // Remettre les pièces en place
    set_position();
}