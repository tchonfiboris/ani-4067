#include <iostream>
#include <string>
#include <cstdlib>

int main() {
    int n;
    if (!(std::cin >> n)){
         return 0;
        }

    int aCorriger = 0;
    long long pire = 0;

    for (int i = 0; i < n; ++i) {
        std::string nom;
        long long e; 
        long long  y;
        std::cin >> nom >> e >> y;

        long long demi = e / 2;      // la demi-hauteur, pas la hauteur
        long long bas = y - demi;
        long long haut = y + demi;

        std::string verdict;
        if (haut <= 0)
            verdict = "SOUS LE SOL";
        else if (bas < 0)
            verdict = "ENTERRE";
        else if (bas == 0)
            verdict = "POSE";
        else
            verdict = "FLOTTE";

        if (verdict != "POSE") 
            ++aCorriger;

        long long ecart = bas < 0 ? -bas : bas;
        if (ecart > pire) 
            pire = ecart;

        std::cout << nom << " " << bas << " " << haut << " "
                  << verdict << " " << demi << std::endl;
    }

    std::cout << "A CORRIGER " << aCorriger << std::endl;
    std::cout << "PIRE " << pire << std::endl;

    return 0;
}
