#include <iostream>
#include <set>
#include <string>

int main() {
    long long v;
    int T;
    std::cin >> v >> T;

    // Avant et droite de la tête, au sol, selon le lacet k : (x, z).
    const int avant[4][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
    const int droite[4][2] = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};

    // Le décalage du monde : la seule chose que le programme modifie.
    // Le lacet de la tête n'est que lu : le programme ne l'écrit jamais.
    long long decalageX = 0, decalageZ = 0;
    long long diagonales = 0;

    for (int t = 1; t <= T; ++t) {
        int k, n;
        std::cin >> k >> n;
        std::set<std::string> tenues;
        for (int j = 0; j < n; ++j) {
            std::string c;
            std::cin >> c;
            tenues.insert(c);
        }

        // Le manche : deux flèches opposées s'annulent.
        int x = (tenues.count("F_DROITE") ? 1 : 0) - (tenues.count("F_GAUCHE") ? 1 : 0);
        int y = (tenues.count("F_HAUT") ? 1 : 0) - (tenues.count("F_BAS") ? 1 : 0);
        if (x != 0 && y != 0) ++diagonales;

        // Décalage += v * (y * avant + x * droite).
        const int* a = avant[k];
        const int* d = droite[k];
        decalageX += v * (y * a[0] + x * d[0]);
        decalageZ += v * (y * a[1] + x * d[1]);

        std::cout << t << " " << x << "," << y << " " << decalageX << " " << decalageZ << std::endl;
    }

    std::cout << "DECALAGE " << decalageX << " " << decalageZ << std::endl;
    std::cout << "DIAGONALES " << diagonales << std::endl;
    return 0;
}
