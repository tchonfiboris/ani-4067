#include <iostream>
#include <string>

int main() {
    int N;
    std::cin >> N;

    long long bonnes = 0, longues = 0, muettes = 0;
    long long temps = 0;  // entier de 64 bits

    for (int i = 1; i <= N; ++i) {
        // Ordre de ApplyHaptic : amplitude, durée, fréquence.
        long long a, d, f;
        std::cin >> a >> d >> f;

        // Amplitude remise entre 0 et 100.
        long long A = a < 0 ? 0 : (a > 100 ? 100 : a);
        // Durée ou fréquence nulle ou négative : remplacée par le défaut du runtime.
        std::string D = (d > 0) ? std::to_string(d) : "MIN";
        std::string F = (f > 0) ? std::to_string(f) : "DEFAUT";

        // La durée écrite compte dans le temps, muettes comprises ; MIN vaut 0.
        if (d > 0) temps += d;

        // Le verdict : muette d'abord.
        std::string verdict;
        if (A == 0) {
            verdict = "MUETTE";
            ++muettes;
        } else if (d < 50) {  // MIN compris, puisque d <= 0 < 50
            verdict = "BREVE";
        } else if (d <= 200) {
            verdict = "BONNE";
            ++bonnes;
        } else {
            verdict = "LONGUE";
            ++longues;
        }

        std::cout << i << " " << A << " " << D << " " << F << " " << verdict << std::endl;
    }

    std::cout << "BONNES " << bonnes << std::endl;
    std::cout << "LONGUES " << longues << std::endl;
    std::cout << "MUETTES " << muettes << std::endl;
    std::cout << "TEMPS " << temps << std::endl;
    return 0;
}