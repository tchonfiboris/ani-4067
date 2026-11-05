#include <iostream>
#include <string>
#include <vector>

int main() {
    int n, T;
    long long x0, v;
    if (!(std::cin >> n >> T >> x0 >> v)) return 0;

    std::string modes;
    std::cin >> modes;

    std::vector<int> derniere(n, 0); // numéro de la dernière trame peinte dans chaque emplacement
    int prochaine = 0;

    bool prevMontree = false;
    long long prevPos = 0;

    bool aSaut = false;
    long long sautMin = 0, sautMax = 0;

    for (int t = 1; t <= T; ++t) {
        char mode = (t - 1 < (int)modes.size()) ? modes[t - 1] : 'A';

        // on emprunte la prochaine image et on y peint la trame t
        int emprunte = prochaine;
        derniere[emprunte] = t;

        int index = emprunte;
        if (mode == 'P') index = (prochaine + n - 1) % n; // lu avant la libération

        // on rend l'image
        prochaine = (prochaine + 1) % n;

        if (mode == 'D') index = (prochaine + n - 1) % n; // lu après la libération

        int f = derniere[index];
        if (f == 0) {
            std::cout << t << " NOIR -" << std::endl;
            prevMontree = false;
        } else {
            long long pos = x0 + v * f;
            if (t == 1 || !prevMontree) {
                std::cout << t << " " << pos << " -" << std::endl;
            } else {
                long long saut = pos - prevPos;
                std::cout << t << " " << pos << " " << saut << std::endl;
                if (!aSaut) {
                    aSaut = true;
                    sautMin = sautMax = saut;
                } else {
                    if (saut < sautMin) sautMin = saut;
                    if (saut > sautMax) sautMax = saut;
                }
            }
            prevMontree = true;
            prevPos = pos;
        }
    }

    if (!aSaut) {
        std::cout << "SAUTS AUCUN" << std::endl;
    } else {
        std::cout << "SAUT MIN " << sautMin << std::endl;
        std::cout << "SAUT MAX " << sautMax << std::endl;
        std::cout << "TREMBLE " << (sautMin != sautMax ? "OUI" : "NON") << std::endl;
    }
    return 0;
}
