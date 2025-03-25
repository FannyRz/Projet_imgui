#pragma once
#include <vector>
#include "pieces/pieces.hpp"
#include "quick_imgui/quick_imgui.hpp"

struct LoiDeGamma {
    bool   is_display_chronometer = false;
    double moveTimeChronometer{};

    void increment_moveTimeChronometer();
    void reset_LoiDeGamma();
};

struct Chronometer {
    std::chrono::steady_clock::time_point gameStartTime{};

    // Fonction pour initialiser le chronomètre au début de la partie
    void startChronometer();

    // Affiche le temps écoulé depuis le début du jeu
    void displayGameTime() const;
    void reset_Chronometer();
};

/* ---------------------- MATHS_GENERATION_LOIS ---------------------- */
/* ---------- test Bernoulli  ---------- */
double genererDouble(double min, double max);
int    bernoulli(double p);
int    binomial(int n, double p);

/*  ---------- test Poisson  ---------- */
int poisson(double lambda);

/*  ---------- test Pareto  ---------- */
double pareto(double alpha, double x0);
double varianceExperimentale(const std::vector<double>& echantillons, double moyenne);

/*  ---------- test Gamma  ---------- */
float generateUniform();
float generateExponential(float beta);
float generateGamma(int alpha, float beta);

/* ---------------------- MATHS_GAME ---------------------- */
ImFont*   load_font_based_on_bernoulli(ImGuiIO& io);
PieceType select_piece_promotion();