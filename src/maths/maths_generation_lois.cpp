#include <random>
#include "maths.hpp"

// Fonction pour générer un nombre aléatoire entre 2 valeurs
double genererDouble(double min, double max)
{
    std::random_device                     rd;                // Initialisation du générateur aléatoire basé sur le matériel
    std::mt19937                           gen(rd());         // Générateur de nombres aléatoires
    std::uniform_real_distribution<double> distrib(min, max); // Distribution uniforme
    return distrib(gen);                                      // Retourne un nombre aléatoire dans la plage [min, max]
}

// Fonction pour simuler une loi de Bernoulli
int bernoulli(double p)
{
    return genererDouble(0.0, 1.0) < p; // Compare le nombre généré avec p pour obtenir un nombre aleatoire en 0 et 1
}

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

// Fonction pour générer la loi de Pareto
double pareto(double alpha, double x0)
{
    double u = genererDouble(0.0, 1.0);     // Génère un nombre aléatoire entre 0 et 1
    return x0 * pow(1.0 - u, -1.0 / alpha); // Transformation inverse pour la loi de Pareto
}

// Fonction pour calculer la variance experimentale
double varianceExperimentale(const std::vector<double>& echantillons, double moyenne)
{
    double somme = 0.0;
    for (double echantillons : echantillons)
    {
        somme += pow(echantillons - moyenne, 2);
    }
    return somme / echantillons.size();
}
