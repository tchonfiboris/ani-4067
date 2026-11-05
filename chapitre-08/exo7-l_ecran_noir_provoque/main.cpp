#include <iostream>
#include <string>

int main() {
    int N;
    if (!(std::cin >> N)) N = 0;

    long long courante = 0;   // poignée de la cible courante
    long long prochaineHandle = 101;
    long long index0 = 0;     // valeur rangée à l'index 0 de la chaîne
    long long numImage = 0;
    long long affichees = 0, noires = 0, perimees = 0;

    for (int i = 0; i < N; ++i) {
        std::string ordre;
        if (!(std::cin >> ordre)) break;

        if (ordre == "cible") {
            long long w, h;
            std::cin >> w >> h;
            courante = prochaineHandle++;
            std::cout << "CIBLE " << courante << " " << w << " " << h << std::endl;
        } else if (ordre == "chaine") {
            index0 = 0;
        } else if (ordre == "enregistre") {
            index0 = courante;
        } else if (ordre == "image") {
            ++numImage;
            if (index0 == 0) {
                std::cout << "IMAGE " << numImage << " NOIR" << std::endl;
                ++noires;
            } else if (index0 == courante) {
                std::cout << "IMAGE " << numImage << " AFFICHE " << index0 << std::endl;
                ++affichees;
            } else {
                std::cout << "IMAGE " << numImage << " PERIMEE " << index0 << std::endl;
                ++perimees;
            }
        }
    }

    std::cout << "AFFICHEES " << affichees << std::endl;
    std::cout << "NOIRES " << noires << std::endl;
    std::cout << "PERIMEES " << perimees << std::endl;
    return 0;
}