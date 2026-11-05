#include <iostream>
#include <string>

int main() {
    int n, N;
    if (!(std::cin >> n >> N)) return 0;

    int prochaine = 0;
    bool emprunte = false;
    int imageEmpruntee = -1;
    bool dessinee = false;       // l'image empruntée a reçu un draw
    bool rendue = false;         // une image a été rendue depuis la dernière soumission acceptée
    bool derniereVide = false;   // la dernière image rendue l'a été sans aucun draw
    long long soumises = 0, refus = 0, horsEmprunt = 0;

    for (int i = 0; i < N; ++i) {
        std::string ordre;
        if (!(std::cin >> ordre)) break;

        if (ordre == "acquire") {
            if (emprunte) {
                std::cout << "ACQUIRE REFUSE" << std::endl;
                ++refus;
            } else {
                emprunte = true;
                imageEmpruntee = prochaine;
                dessinee = false;
                std::cout << "ACQUIRE " << imageEmpruntee << std::endl;
            }
        } else if (ordre == "draw") {
            if (emprunte) {
                dessinee = true;
                std::cout << "DRAW " << imageEmpruntee << std::endl;
            } else {
                std::cout << "DRAW HORS EMPRUNT" << std::endl;
                ++horsEmprunt;
            }
        } else if (ordre == "release") {
            if (!emprunte) {
                std::cout << "RELEASE REFUSE" << std::endl;
                ++refus;
            } else {
                derniereVide = !dessinee;
                prochaine = (prochaine + 1) % n;
                emprunte = false;
                rendue = true;
                std::cout << "RELEASE OK" << std::endl;
            }
        } else if (ordre == "submit") {
            if (emprunte) {
                std::cout << "SUBMIT REFUSE EMPRUNTEE" << std::endl;
                ++refus;
            } else if (!rendue) {
                std::cout << "SUBMIT REFUSE RIEN" << std::endl;
                ++refus;
            } else {
                int j = (prochaine + n - 1) % n;
                std::cout << "SUBMIT " << j << (derniereVide ? " VIDE" : "") << std::endl;
                rendue = false;
                ++soumises;
            }
        }
    }

    std::cout << "SOUMISES " << soumises << std::endl;
    std::cout << "REFUS " << refus << std::endl;
    std::cout << "HORS EMPRUNT " << horsEmprunt << std::endl;
    return 0;
}