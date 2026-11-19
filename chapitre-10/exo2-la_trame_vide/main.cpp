#include <iostream>
#include <string>

int main() {
    int N, T;
    std::cin >> N >> T;

    if (N < 1 || N > 4) {
        std::cout << "CHAINE REFUSEE" << std::endl;
        return 0;
    }

    std::string mots;
    if (T > 0) std::cin >> mots;

    int fins = 0, rendues = 0, sautees = 0;
    int prochaine = 0;

    for (int t = 1; t <= T; ++t) {
        bool rendre = (t - 1 < (int)mots.size()) && mots[t - 1] == '1';
        if (rendre) {
            int i = prochaine;
            int lacet = t - 1;
            std::cout << t << " OUI 1 " << lacet << " " << i << std::endl;
            prochaine = (i + 1) % N;
            ++rendues;
        } else {
            std::cout << t << " NON 0" << std::endl;
            ++sautees;
        }
        ++fins;  // une fin de trame par image, rendue ou non
    }

    std::cout << "FINS " << fins << std::endl;
    std::cout << "RENDUES " << rendues << std::endl;
    std::cout << "SAUTEES " << sautees << std::endl;
    std::cout << "PROCHAINE " << prochaine << std::endl;
    return 0;
}