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

// Fonction qui retourne le nom du type de la pièce sous forme de chaîne
std::string ChessBoard::pieceTypeToString(PieceType type)
{
    switch (type)
    {
    case PieceType::KING: return "KING";
    case PieceType::QUEEN: return "QUEEN";
    case PieceType::ROOK: return "ROOK";
    case PieceType::KNIGHT: return "KNIGHT";
    case PieceType::PAWN: return "PAWN";
    case PieceType::BISHOP: return "BISHOP";
    default: return "UNKNOWN"; // Cas où le type est inconnu
    }
}

void ChessBoard::select(int x, int y)
{
    SelectedPiece selectedPiece{};
    selectedPiece.piece      = position_pieces[x][y].get();
    selectedPiece.position_x = x;
    selectedPiece.position_y = y;
    this->_selected          = selectedPiece;
    std::cout << position_pieces[x][y] << std::endl;
    std::cout << pieceTypeToString(position_pieces[x][y]->get_type()) << std::endl;
}

void ChessBoard::set_font(ImFont* font)
{
    this->font = font;
}

ImFont* ChessBoard::get_font() const
{
    return this->font;
}

void ChessBoard::typeToFont(int x, int y)
{
    switch (this->position_pieces[x][y]->get_type())
    {
    case PieceType::PAWN:
        this->character = (this->position_pieces[x][y]->get_color() == PieceColor::WHITE) ? 'p' : 'o';
        break;
    case PieceType::ROOK:
        this->character = (this->position_pieces[x][y]->get_color() == PieceColor::WHITE) ? 'r' : 't';
        break;
    case PieceType::KNIGHT:
        this->character = (this->position_pieces[x][y]->get_color() == PieceColor::WHITE) ? 'h' : 'j';
        break;
    case PieceType::BISHOP:
        this->character = (this->position_pieces[x][y]->get_color() == PieceColor::WHITE) ? 'b' : 'n';
        break;
    case PieceType::QUEEN:
        this->character = (this->position_pieces[x][y]->get_color() == PieceColor::WHITE) ? 'q' : 'w';
        break;
    case PieceType::KING:
        this->character = (this->position_pieces[x][y]->get_color() == PieceColor::WHITE) ? 'k' : 'l';
        break;
    }
}

void ChessBoard::draw_board()
{
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{0.f, 0.f}); // Bordure entre les cases à zéro.
    for (int x{0}; x < 8; x++)
    {
        for (int y{0}; y < 8; y++)
        {
            if (position_pieces[x][y] != nullptr)
            {
                ImGui::PushFont(this->get_font());
                ImGui::PushStyleColor(ImGuiCol_Text, (position_pieces[x][y]->get_color() == PieceColor::BLACK) ? IM_COL32(25, 25, 25, 255) : IM_COL32(250, 250, 250, 255));
                // this->typeToFont(x, y);
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

            if (_selected.has_value() && x == _selected->position_x && y == _selected->position_y)
            {
                ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 5.0f); // Bordure plus épaisse
                ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.5f, 0.0f, 0.5f, 1.0f));
                borderActivate = true;
            }

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
                        // std::cout << position_pieces[x][y] << '\n';
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

            ImGui::PopStyleColor();

            if (position_pieces[x][y] != nullptr)
            {
                ImGui::PopStyleColor();
                ImGui::PopFont();
            }
        }
    }
    ImGui::PopStyleVar();
}
