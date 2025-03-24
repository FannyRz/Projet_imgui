#include "maths.hpp"

/* ---------- Bernoulli  ---------- */
ImFont* load_font_based_on_bernoulli(ImGuiIO& io)
{
    bool use_font_1 = bernoulli(0.6); // 60% de chance de choisir la font 1

    const char* font_file = use_font_1 ? "fonts/CHEQ_TT.TTF" : "fonts/Alpha.TTF";

    // Charger la font choisie dans ImGui
    ImFont* font = io.Fonts->AddFontFromFileTTF(font_file, 70.0f);
    IM_ASSERT(font != nullptr); // Vérifier que la police a bien été chargée
    return font;
}

/* ---------- Pareto  ---------- */
PieceType select_piece_promotion()
{
    double pareto_value = pareto(3, 1);
    if (pareto_value < 1.2)
    {
        return PieceType::QUEEN;
    }
    else
    {
        double value = genererDouble(0.0, 1.0);
        if (value < 0.33)
        {
            return PieceType::KNIGHT;
        }
        else if (value < 0.66)
        {
            return PieceType::ROOK;
        }
        else
        {
            return PieceType::BISHOP;
        }
    }
}