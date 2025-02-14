#include "chessBoard.hpp"
#include <imgui.h>
#include <memory>
#include <optional>
#include "pieces.hpp"

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
    selectedPiece.piece      = position_pieces[x][y].get();
    selectedPiece.position_x = x;
    selectedPiece.position_y = y;
    this->_selected          = selectedPiece;
    std::cout << "(" << &selectedPiece << "\n";
}

void ChessBoard::draw_board()
{
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{0.f, 0.f}); // Bordure entre les cases à zéro.
    for (int x{0}; x < 8; x++)
    {
        for (int y{0}; y < 8; y++)
        {
            bool borderActivate = false;

            if ((x + y) % 2 == 0)
            {
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.f, 0.f, 0.f, 1.f});
            }
            else
            {
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{1.f, 1.f, 1.f, 1.f});
            }

            if (_selected.has_value() && x == _selected->position_x && y == _selected->position_y)
            {
                ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 3.0f); // Bordure plus épaisse
                ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
                borderActivate = true;
            }

            ImGui::PushFont(this->font);
            //  Piece* piece = board.get_pîece(x, y);  Code fait par Jules qui demande si sur une case il y a une piece ou non

            if (ImGui::Button((position_pieces[x][y] != nullptr ? pieceTypeToString(position_pieces[x][y]->get_type()) + "##" + std::to_string(x) + "_" + std::to_string(y) : "##" + std::to_string(x) + "_" + std::to_string(y)).c_str(), ImVec2{50.f, 50.f}))
            {
                if (position_pieces[x][y] != nullptr)
                {
                    if (_selected.has_value() && x == _selected->position_x && y == _selected->position_y)
                    {
                        this->deselect();
                    }
                    else
                    {
                        std::cout << _selected.has_value() << '\n';
                        std::cout << position_pieces[x][y] << '\n';
                        this->select(x, y);
                    }
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

            ImGui::PopFont();
            ImGui::PopStyleColor();
        }
    }
    ImGui::PopStyleVar();
}
