#include <iostream>
#include <string>

int main() {
    std::string politique;
    int T;
    std::cin >> politique >> T;

    std::string mots;
    if (T > 0) std::cin >> mots;

    bool toujours = (politique == "TOUJOURS");
    bool trameOuverte = false;
    int rendues = 0, perdues = 0, erreurs = 0;
    int premierRefus = 0;  // 0 = aucun

    for (int t = 1; t <= T; ++t) {
        bool signe = (t - 1 < (int)mots.size()) && mots[t - 1] == '1';
        bool rendre = false;  // état neuf

        // WaitFrame
        std::string w;
        if (trameOuverte) {
            w = "REFUSE";
            ++erreurs;
            if (premierRefus == 0) premierRefus = t;
        } else {
            w = "OK";
            rendre = signe;
        }

        // BeginFrame
        std::string b;
        if (trameOuverte) {
            b = "REFUSE";
            ++erreurs;
        } else {
            b = "OK";
            trameOuverte = true;
        }

        // Rendu
        if (rendre) ++rendues;
        else if (signe) ++perdues;

        // EndFrame
        std::string e = "-";
        if (toujours || rendre) {
            if (trameOuverte) {
                e = "OK";
                trameOuverte = false;
            } else {
                e = "REFUSE";
                ++erreurs;
            }
        }

        std::cout << t << " " << w << " " << b << " "
                  << (rendre ? "OUI" : "NON") << " " << e << std::endl;
    }

    std::cout << "RENDUES " << rendues << std::endl;
    std::cout << "PERDUES " << perdues << std::endl;
    std::cout << "ERREURS " << erreurs << std::endl;
    if (premierRefus == 0) std::cout << "PREMIER REFUS AUCUN" << std::endl;
    else std::cout << "PREMIER REFUS " << premierRefus << std::endl;
    return 0;
}