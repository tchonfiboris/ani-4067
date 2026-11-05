#include <iostream>
#include <string>

int main() {
    int N;
    if (!(std::cin >> N)) N = 0;

    long long acceptees = 0, occupes = 0, gauche = 0, droit = 0, sansNom = 0;

    for (int i = 0; i < N; ++i) {
        long long largeur, hauteur, images;
        int oeil;
        std::string nom;
        if (!(std::cin >> largeur >> hauteur >> images >> oeil >> nom)) break;

        bool sans = (nom == "-");
        std::string affiche = sans ? "SANS-NOM" : nom;

        if (largeur == 0 || hauteur == 0) {
            std::cout << "REFUSEE " << affiche << " TAILLE" << std::endl;
        } else if (images == 0 || images > 4) {
            std::cout << "REFUSEE " << affiche << " IMAGES" << std::endl;
        } else {
            std::cout << "CHAINE " << affiche << " " << largeur << " " << hauteur << " "
                      << images << " " << (oeil == 0 ? "GAUCHE" : "DROIT") << std::endl;
            ++acceptees;
            occupes += images;
            if (oeil == 0) ++gauche; else ++droit;
            if (sans) ++sansNom;
        }
    }

    std::cout << "ACCEPTEES " << acceptees << std::endl;
    std::cout << "EMPLACEMENTS " << 4 * acceptees << std::endl;
    std::cout << "OCCUPES " << occupes << std::endl;
    std::cout << "GAUCHE " << gauche << std::endl;
    std::cout << "DROIT " << droit << std::endl;
    std::cout << "SANS NOM " << sansNom << std::endl;
    return 0;
}