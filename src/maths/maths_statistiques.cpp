// #include "maths.hpp"

// int main()
// {
/* ---------- test Bernoulli  ---------- */
//   int numSucces = 0; // Compteur des succès
//   int numEchecs = 0; // Compteur des échecs

//   // Simuler 1000 lancers
//   for (int i = 0; i < 1000; ++i) {
//     int result = bernoulli(0.6);

//     if (result == 1) // Succès
//       numSucces++;
//     else // Échec
//       numEchecs++;
//   }

//   double probaSucces = numSucces / 1000.;
//   double probaEchecs = numEchecs / 1000.;

//   // Calcul de la variance
//   double variance = probaSucces * probaEchecs;

//   std::cout << probaSucces << '\n';
//   std::cout << probaEchecs << '\n';
//   std::cout << variance << '\n';

/*  ---------- test Poisson  ---------- */
// int    N      = 10000; // Nombre d'échantillons
// double lambda = 2.0;   // Paramètre de la loi de Poisson

// // Génération des N échantillons et calcul de la somme
// int sum = 0;
// for (int i = 0; i < N; ++i)
// {
//     sum += poisson(lambda); // Ajoute chaque tirage à la somme
// }

// // Affichage de la moyenne des tirages (environ lambda)
// std::cout << "Moyenne des " << N
//           << " tirages : " << sum / static_cast<double>(N) << std::endl;

// // Initialisation d'un tableau pour compter les occurrences de chaque
// std::vector<int> count(11, 0); // On compte les valeurs de 0 à 10

// // Génération des 1000 tirages et comptage des résultats
// for (int i = 0; i < N; ++i)
// {
//     int k = poisson(lambda);
//     if (k <= 10)
//     { // On limite à 10 pour la comparaison, mais on pourrait
//       // étendre selon les besoins
//         count[k]++;
//     }
// }

// // Affichage des résultats expérimentaux
// std::cout << "Distribution experimentale (frequences sur 1000 tirages):\n ";
// for (int i = 0; i <= 10; ++i)
// {
//     std::cout << "P(X = " << i << ") = " << static_cast<double>(count[i]) / N
//               << "\n";
// }

/*  ---------- test Pareto  ---------- */
// // Paramètres de la loi de Pareto
// double alpha = 3.0; // Paramètre de forme
// double x0 = 1.0;    // Paramètre de seuil
// int N = 10000;      // Nombre d'échantillons à générer

// // Générer des échantillons suivant la loi de Pareto
// std::vector<double> echantillons;
// for (int i = 0; i < N; ++i) {
//   echantillons.push_back(pareto(alpha, x0));
// }

// // Calcul de la moyenne experimentale
// double somme = 0.0;
// for (double sample : echantillons) {
//   somme += sample;
// }
// double moyenne = somme / N;

// // Calcul de la variance experimentale
// double variance_emp = varianceExperimentale(echantillons, moyenne);

// // Calcul de la variance théorique (valide pour alpha > 2)
// double variance_theo =
//     (alpha * pow(x0, 2)) / (pow(alpha - 1, 2) * (alpha - 2));

// // Affichage des résultats
// std::cout << "Variance experimentale  : " << variance_emp << std::endl;
// std::cout << "Variance theorique: " << variance_theo << std::endl;

/*  ---------- test Exponentielle  ---------- */
// double min    = 0.0;
// double max    = 1.0;
// double lambda = 0.5;
// int    N      = 1000; // Nombre d'échantillons
// double somme  = 0.0;

// std::vector<double> echantillons;
// for (int i{}; i < N; i++)
// {
//     echantillons.push_back(loiExponentielle(lambda, min, max));
// }

// for (double sample : echantillons)
// {
//     somme += sample;
// }

// double moyenne = somme / N;

// double variance_exp = varianceExperimentale(echantillons, moyenne);
// double variance_th  = 1 / pow(0.5, 2);

// std::cout << "Variance exp : " << variance_exp << "\n";
// std::cout << "Variance th : " << variance_th << "\n";
/* ---------- loi de Gamma ---------- */
// // Paramètres de la loi Gamma
// int   alpha = 2;     // Paramètre de forme (nombre d'événements)
// float beta  = 10.0f; // Paramètre d'échelle (temps moyen par événement)

// std::vector<float> samples;
// float              sum = 0;

// // Générer un certain nombre d'échantillons
// for (int i = 0; i < 1000; ++i)
// {
//     float sample = generateGamma(alpha, beta);
//     samples.push_back(sample);
//     sum += sample;
// }

// // Calcul de l'espérance (moyenne des échantillons)
// float esperance = sum / 1000;

// // Calcul de la variance
// float squaredSum = 0;
// for (float sample : samples)
// {
//     squaredSum += (sample - esperance) * (sample - esperance);
// }
// float variance = squaredSum / 1000;

// // Affichage des résultats
// std::cout << "Estimation experimentale de l'esperance : " << esperance
//           << std::endl;
// std::cout << "Estimation experimentale de la variance : " << variance
//           << std::endl;

//     return 0;
// }
