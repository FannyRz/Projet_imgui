#include <iostream>
#include <numbers>
#include <random>
#include "maths.hpp"

// Fonction pour générer un nombre aléatoire entre 2 valeurs
double generate_double(double min, double max)
{
    std::random_device                     rd;                // Initialisation du générateur aléatoire basé sur le matériel
    std::mt19937                           gen(rd());         // Générateur de nombres aléatoires
    std::uniform_real_distribution<double> distrib(min, max); // Distribution uniforme
    return distrib(gen);                                      // Retourne un nombre aléatoire dans la plage [min, max]
}

// Fonction pour générer une variable
double generate_variance(std::vector<int>& echantillons, double moyenne)
{
    double somme = 0.0;
    for (int echantillon : echantillons)
    {
        somme += pow(echantillon - moyenne, 2);
    }
    return somme / echantillons.size();
}

/********************************************************1_GEOMETRIQUE & UNIFORME***************************************************/
// Fonction pour simuler une loi de Géométrique
int geometrique(double p, double min, double max)
{
    double u = generate_double(min, max);
    return std::ceil(std::log(1 - u) / std::log(1 - p));
}

// Fonction pour générer une variable aléatoire suivant une loi uniforme [0,1]
float uniform()
{
    std::random_device                    rd;
    std::mt19937                          gen(rd());
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    return dist(gen);
}

/********************************************************2_BERNOULLI***************************************************/
// Fonction pour simuler une loi de Bernoulli
int bernoulli(double p)
{
    return generate_double(0.0, 1.0) < p; // Compare le nombre généré avec p pour obtenir un nombre aleatoire en 0 et 1
}

/********************************************************BINOMIAL***************************************************/
// Fonction pour simuler une loi binomiale (n, p)
int binomial(int n, double p)
{
    int y = 0;
    for (int i = 0; i < n; ++i)
    {
        y += bernoulli(p); // Ajoute un succès si bernoulli(p) retourne 1
    }
    return y;
}

/********************************************************3_PARETO***************************************************/
// Fonction pour simuler la loi de Pareto
double pareto(double alpha, double x0)
{
    double u = generate_double(0.0, 1.0);   // Génère un nombre aléatoire entre 0 et 1
    return x0 * pow(1.0 - u, -1.0 / alpha); // Transformation inverse pour la loi de Pareto
}

/********************************************************4_EXPONENTIEL***************************************************/
// Fonction pour générer une variable suivant une loi exponentielle de paramètre 1/beta
float exponential(float beta)
{
    float U = uniform();
    return -beta * std::log(U);
}

/********************************************************5_POISSON***************************************************/
// Fonction pour générer la loi de Poisson
int poisson(double lambda)
{
    // Générateur aléatoire et distribution uniforme
    std::random_device               rd;
    std::mt19937                     gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    int    k = 0;
    double L = std::exp(-lambda);
    double p = 1.0; // Probabilité cumulative
    // Générer des événements jusqu'à ce que la probabilité cumulative dépasse 1
    while (p > L)
    {
        p *= dis(gen);
        ++k;
    }
    return k - 1; // On retourne k-1, car k est incrémenté une dernière fois avant de sortir de la boucle
}

/********************************************************6_NORMALE***************************************************/
// Fonction pour simuler une loi normale
double normale(double mu, double sigma, double min, double max)
{
    double u1 = generate_double(min, max);
    double u2 = generate_double(min, max);
    double z0 = std::sqrt(-2.0 * std::log(u1)) * std::cos(2.0 * std::numbers::pi * u2);

    // Transformation vers une loi normale de moyenne mu et ecart-type sigma
    double result = mu + sigma + z0;

    return result;
}

/********************************************************7_GAMMA***************************************************/
// Fonction pour générer une variable suivant une loi Gamma
float gamma(int alpha, float beta)
{
    float sum = 0.0f;

    // Somme de alpha variables exponentielles
    for (int i = 0; i < alpha; ++i)
    {
        sum += exponential(beta);
    }

    return sum;
}

/********************************************************8_CAUCHY***************************************************/
// Fonction pour simuler une loi de Cauchy
double cauchy(double x0, double gamma, double min, double max)
{
    double x{};
    do
    {
        double u = generate_double(0.00001, 0.999999); // Evite exactement 0 et 1 a cause de tan()
        x        = x0 + gamma * std::tan(std::numbers::pi * (u - 0.5));
    } while (x < min || x > max);
    return x;
}


// /********************************************************9_CHAINE DE MARKOV***************************************************/
// // Fonction pour simuler une chaine de Markov à trois états
// void simulerTransitionMarkov(Piece& piece) {
//     double r = generate_double(0.0, 1.0);  // Génère un nombre aléatoire entre 0 et 1

//     switch (piece.etatMarkov) {
//         case 0:  // Fidèle
//             if (r < 0.02) {
//                 piece.etatMarkov = 1;  // Devient influencée
//             }
//             break;
//         case 1:  // Influencée
//             if (r < 0.10) {
//                 piece.etatMarkov = 2;  // Devient convertie
//                 piece.changerEquipe(); 
//             }
//             break;
//         case 2:
//             // État absorbant, ne change pas
//             break;
//     }
// }
