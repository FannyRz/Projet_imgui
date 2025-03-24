#pragma once
#include <vector>
#include "pieces/pieces.hpp"
#include "quick_imgui/quick_imgui.hpp"

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

/* ---------------------- MATHS_GAME ---------------------- */
ImFont*   load_font_based_on_bernoulli(ImGuiIO& io);
PieceType select_piece_promotion();