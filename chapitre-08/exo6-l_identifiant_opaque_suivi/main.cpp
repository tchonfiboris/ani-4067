#include <cstdint>
#include <iostream>
#include <set>
#include <string>
#include <vector>

int main() {
    int n, N;
    if (!(std::cin >> n >> N)) return 0;

    std::vector<std::uint64_t> emplacements(n, 0);
    std::set<std::uint64_t> textures;
    long long mortes = 0, larges = 0;

    for (int k = 0; k < N; ++k) {
        std::string ordre;
        if (!(std::cin >> ordre)) break;

        if (ordre == "cree") {
            std::uint64_t h;
            std::cin >> h;
            textures.insert(h);
        } else if (ordre == "detruit") {
            std::uint64_t h;
            std::cin >> h;
            textures.erase(h);
        } else if (ordre == "set") {
            std::uint64_t i, h;
            std::cin >> i >> h;
            if (i >= (std::uint64_t)n) {
                std::cout << "SET IGNORE " << i << std::endl;
            } else {
                emplacements[i] = h;
                if (h > 4294967295ULL) ++larges;
            }
        } else if (ordre == "get") {
            std::uint64_t i;
            std::cin >> i;
            std::uint64_t h = (i < (std::uint64_t)n) ? emplacements[i] : 0;
            if (h == 0) {
                std::cout << "GET " << i << " 0 VIDE" << std::endl;
            } else if (textures.count(h)) {
                std::cout << "GET " << i << " " << h << " VIVANTE" << std::endl;
            } else {
                std::cout << "GET " << i << " " << h << " MORTE" << std::endl;
                ++mortes;
            }
        }
    }

    std::cout << "MORTES " << mortes << std::endl;
    std::cout << "LARGES " << larges << std::endl;
    return 0;
}