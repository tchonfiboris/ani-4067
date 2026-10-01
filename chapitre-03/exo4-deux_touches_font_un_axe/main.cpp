#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

int main() {
    int c;
    std::cin >> c;

    std::vector<long long> echelle(c); 
    std::vector <long long> seuil(c);
    for (int i = 0; i < c; ++i) {
        std::string nom;
        std::cin >> nom; 
        std::cin >> echelle[i]; 
        std::cin >> seuil[i];
    }

    int t;
    std::cin >> t;

    for (int k = 0; k < t; ++k) {
        long long axe = 0;
        for (int i = 0; i < c; ++i) {
            long long brut;
            std::cin >> brut;

            long long contribution = brut * echelle[i] / 1000;

            if (std::llabs(contribution) < seuil[i]) {
                continue;
            }
            axe = axe + contribution;
        }
        std::cout << axe << std::endl;
    }

    return 0;
}
