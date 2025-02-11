#include <iomanip>
#include <iostream>
#include <random>

// Fonction pour générer un double aléatoire dans une plage donnée
static double genererDouble(double min, double max)
{
    std::random_device                     rd;
    std::mt19937                           gen(rd());
    std::uniform_real_distribution<double> distrib(min, max);
    return distrib(gen);
}

static int function()
{
    // Initialisation des plages
    double minDouble = 0.0;
    double maxDouble = 1.0;

    // Génération de nombres aléatoires
    std::cout << "Double aléatoire: " << std::setprecision(100) << genererDouble(minDouble, maxDouble) << '\n';

    return 0;
}

static int factoriel(int n)
{
    if (n == 0)
    {
        return 1;
    }
    return n * factoriel(n - 1);
}

static double binomiale(double p, int N, int k)
{
    return (factoriel(N) / (factoriel(k) * factoriel(N - k))) * pow(p, k) * pow(1 - p, N - k);
}

// static double loiBinomiale(double p, int N)
// {
//     double proba{};
//     for (int k{0}; k <= N; k++)
//     {
//     }
// }