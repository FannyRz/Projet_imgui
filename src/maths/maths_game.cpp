#include <chrono>
#include <iostream>
#include <thread>
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
        double value = generer_double(0.0, 1.0);
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

/* ---------- Exponentielle  ---------- */
void print_random_pawn()
{
    double min    = 0.0;
    double max    = 1.0;
    double lambda = 0.5;

    double attente = exponentielle(lambda, min, max);
    std::this_thread::sleep_for(std::chrono::duration<double>(attente)); // Attendre le temps généré

    std::cout << "evenement  apres " << attente << " secondes." << '\n';
}

/* ---------- Gamma  ---------- */
void LoiDeGamma::increment_moveTimeChronometer()
{
    moveTimeChronometer += generate_gamma(2.0, 10.0);

    if (moveTimeChronometer > 300)
    {
        this->isDisplayChronometer = true;
    }
    std::cout << "Temps total accumule: " << moveTimeChronometer << " secondes" << '\n';
}

void LoiDeGamma::reset_loiDeGamma()
{
    isDisplayChronometer = false;
    moveTimeChronometer  = 0.f;
}

/* ---------- Chronometer  ---------- */
void Chronometer::start_chronometer()
{
    gameStartTime = std::chrono::steady_clock::now();
}

void Chronometer::display_game_time() const
{
    // Calcul du temps écoulé depuis le début du jeu
    std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
    auto                                  duration    = std::chrono::duration_cast<std::chrono::seconds>(currentTime - gameStartTime);

    int minutes = duration.count() / 60; // Calcul des minutes
    int seconds = duration.count() % 60; // Calcul des secondes
    ImGui::Text("Temps de jeu : %02d:%02d", minutes, seconds);
}

void Chronometer::reset_chronometer()
{
    start_chronometer();
}