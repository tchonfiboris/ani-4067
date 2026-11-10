#include <iostream>

int main() {
    int T;
    std::cin >> T;

    // Au départ, les trois champs valent 0.
    int current = 0, changed = 0, active = 0;
    int pPrecedent = 0;  // avant l'image 1, p vaut 0
    long long appuisReels = 0, saisies = 0, refusees = 0;

    for (int t = 1; t <= T; ++t) {
        int p, s, f;
        std::cin >> p >> s >> f;

        // Un front réel : p passe de 0 à 1 d'une image à l'autre.
        if (p == 1 && pPrecedent == 0) ++appuisReels;
        pPrecedent = p;

        for (int i = 0; i < s; ++i) {
            if (f == 0) {
                // Sans le focus, l'appel est refusé : les trois champs gardent leur valeur.
                ++refusees;
            } else {
                // Appel accepté : changed d'abord, puis current, puis active.
                changed = (p != current) ? 1 : 0;
                current = p;
                active = 1;
            }
        }

        // Lecture de l'état après les s appels (même sans aucun appel).
        bool saisit = (current == 1 && changed == 1);
        if (saisit) ++saisies;

        std::cout << t << " " << current << " " << changed << " " << active
                  << " " << (saisit ? "SAISIT" : "-") << std::endl;
    }

    std::cout << "APPUIS REELS " << appuisReels << std::endl;
    std::cout << "SAISIES " << saisies << std::endl;
    std::cout << "SYNC REFUSEES " << refusees << std::endl;
    return 0;
}