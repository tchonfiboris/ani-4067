#include <iostream>
#include <string>

int main() {
    int n, N;
    if (!(std::cin >> n >> N)) return 0;

    bool emprunte = false;
    long long reussies = 0, refusees = 0, liberations = 0;
    int premiereFuite = 0;

    for (int t = 1; t <= N; ++t) {
        std::string mot;
        if (!(std::cin >> mot)) break;

        // chaque trame commence par un emprunt
        if (emprunte) {
            ++refusees;
            std::cout << t << " BLOQUEE" << std::endl;
            continue;
        }
        emprunte = true;
        ++reussies;

        if (mot == "sortie") {
            // sortie anticipée : l'image n'est jamais rendue
            if (premiereFuite == 0) premiereFuite = t;
            std::cout << t << " FUITE" << std::endl;
        } else if (mot == "double") {
            // second emprunt refusé, puis libération
            ++refusees;
            emprunte = false;
            ++liberations;
            std::cout << t << " DOUBLE" << std::endl;
        } else {
            // normal : on dessine puis on rend l'image
            emprunte = false;
            ++liberations;
            std::cout << t << " OK" << std::endl;
        }
    }

    std::cout << "REUSSIES " << reussies << std::endl;
    std::cout << "REFUSEES " << refusees << std::endl;
    std::cout << "LIBERATIONS " << liberations << std::endl;
    std::cout << "ECART " << reussies - liberations << std::endl;
    if (premiereFuite == 0)
        std::cout << "PREMIERE FUITE AUCUNE" << std::endl;
    else
        std::cout << "PREMIERE FUITE " << premiereFuite << std::endl;
    return 0;
}
