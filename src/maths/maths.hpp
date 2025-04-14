#pragma once
#include <vector>
#include "pieces/pieces.hpp"
#include "quick_imgui/quick_imgui.hpp"

struct LoiDeGamma {
    bool   isDisplayChronometer = false;
    double moveTimeChronometer{};

    void increment_moveTimeChronometer();
    void reset_loiDeGamma();
};

struct Chronometer {
    std::chrono::steady_clock::time_point gameStartTime{};

    // Fonction pour initialiser le chronomètre au début de la partie
    void start_chronometer();

    // Affiche le temps écoulé depuis le début du jeu
    void display_game_time() const;
    void reset_chronometer();
};

/* ---------------------- MATHS_GENERATION_LOIS ---------------------- */
double generate_double(double min, double max);
double generate_variance(std::vector<int>& echantillons, double moyenne);

/* ---------- test Géométrique & Uniforme ---------- */
int   geometrique(double p, double min, double max);
float uniform();

/* ---------- test Bernoulli  ---------- */
int bernoulli(double p);
int binomial(int n, double p);

/*  ---------- test Pareto  ---------- */
double pareto(double alpha, double x0);

/*  ---------- test Exponentielle  ---------- */
float exponential(float beta);

/*  ---------- test Poisson  ---------- */
int poisson(double lambda);

/* ---------- test Normale  ---------- */
double normale(double mu, double sigma, double min, double max);

/*  ---------- test Gamma  ---------- */
float gamma(int alpha, float beta);

/* ---------- test Cauchy  ---------- */
double cauchy(double x0, double gamma, double min, double max);

/* ---------- test chaine de Markov  ---------- */
void simulerTransitionMarkov(Piece& piece);

/* ---------------------- MATHS_GAME ---------------------- */
ImFont*   load_font_based_on_bernoulli(ImGuiIO& io);
PieceType select_piece_promotion();
