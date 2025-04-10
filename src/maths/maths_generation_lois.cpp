#include <random>
#include <iostream>
#include "maths.hpp"

// Fonction pour générer un nombre aléatoire entre 2 valeurs
double generer_double(double min, double max)
{
    std::random_device                     rd;                // Initialisation du générateur aléatoire basé sur le matériel
    std::mt19937                           gen(rd());         // Générateur de nombres aléatoires
    std::uniform_real_distribution<double> distrib(min, max); // Distribution uniforme
    return distrib(gen);                                      // Retourne un nombre aléatoire dans la plage [min, max]
}

/********************************************************BERNOULLI***************************************************/

// Fonction pour simuler une loi de Bernoulli
int bernoulli(double p)
{
    return generer_double(0.0, 1.0) < p; // Compare le nombre généré avec p pour obtenir un nombre aleatoire en 0 et 1
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

/********************************************************POISSON***************************************************/

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
    return k - 1; // On retourne k-1, car k est incrémenté une dernière fois avant
                  // de sortir de la boucle
}

/********************************************************PARETO***************************************************/  

// Fonction pour générer la loi de Pareto
double pareto(double alpha, double x0)
{
    double u = generer_double(0.0, 1.0);     // Génère un nombre aléatoire entre 0 et 1
    return x0 * pow(1.0 - u, -1.0 / alpha); // Transformation inverse pour la loi de Pareto
}

// Fonction pour calculer la variance experimentale
double variance_experimentale_pareto(const std::vector<double>& echantillons, double moyenne)
{
    double somme = 0.0;
    for (double echantillons : echantillons)
    {
        somme += pow(echantillons - moyenne, 2);
    }
    return somme / echantillons.size();
}


// Fonction pour générer une variable aléatoire suivant une loi uniforme [0,1]
float generate_uniform()
{
    std::random_device                    rd;
    std::mt19937                          gen(rd());
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    return dist(gen);
}

// Fonction pour générer une variable suivant une loi exponentielle de paramètre 1/beta
float generate_exponential(float beta)
{
    float U = generate_uniform();
    return -beta * std::log(U);
}

// Fonction pour générer une variable suivant une loi Gamma
float generate_gamma(int alpha, float beta)
{
    float sum = 0.0f;

    // Somme de alpha variables exponentielles
    for (int i = 0; i < alpha; ++i)
    {
        sum += generate_exponential(beta);
    }

    return sum;
}
