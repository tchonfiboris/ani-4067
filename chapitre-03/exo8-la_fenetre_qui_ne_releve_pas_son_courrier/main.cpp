#include <iostream>
#include <string>

int main() {
    int p; 
    int f;
    std::cin >> p; 
    std::cin >> f;

    int compteur = 0;
    int premier = 0;

    for (int tour = 1; tour <= f; ++tour) {
        std::string action;
        std::cin >> action;

        if (action == "releve") {
            compteur = 0;
        } else {
            ++compteur;
        }

        if (compteur >= p) {
            std::cout << compteur << " MORTE" << std::endl;
            if (premier == 0) premier = tour;
        } else {
            std::cout << compteur << " VIVANTE" << std::endl;
        }
    }

    std::cout << "PREMIER " << premier << std::endl;

    return 0;
}
