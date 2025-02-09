#include <iostream>
#include <iomanip>
#include <random>

// Fonction pour générer un double aléatoire dans une plage donnée
static double genererDouble(double min, double max) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> distrib(min, max);
  return distrib(gen);
}

static int function() {
  // Initialisation des plages
  double minDouble = 0.0;
  double maxDouble = 1.0;

  // Génération de nombres aléatoires
  std::cout << "Double aléatoire: " << std::setprecision(100) << genererDouble(minDouble, maxDouble) << '\n';

  return 0;
}