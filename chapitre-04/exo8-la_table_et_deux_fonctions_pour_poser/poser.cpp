#include <iostream>
#include <string>

// Toutes les longueurs sont en millimetres.
// Un objet est un pave centre sur son origine.

struct Pos {
    long long x, y, z;
};

// Centre d'un objet de hauteur sy pose au sol en (x, z) : y = sy / 2.
Pos PoserAuSol(long long sy, long long x, long long z) {
    return Pos{x, sy / 2, z};
}

// Centre d'un objet de hauteur sy pose sur un dessus de hauteur H :
// y = H + sy / 2.
Pos PoserSurTable(long long sy, long long x, long long z, long long H) {
    return Pos{x, H + sy / 2, z};
}

int main() {
    long long L, P, H, ep, pied, tx, tz;
    if (!(std::cin >> L >> P >> H >> ep >> pied >> tx >> tz)) return 0;

    // Plateau : son dessus est a H, son centre a H - ep / 2.
    std::cout << "PLATEAU " << tx << " " << (H - ep / 2) << " " << tz << "\n";

    // Pieds : hauteur H - ep, poses au sol, decalages L/2 - pied et P/2 - pied.
    long long hPied = H - ep;
    long long dx = L / 2 - pied;
    long long dz = P / 2 - pied;
    const int sx[4] = {-1, +1, -1, +1};   // moins-moins, plus-moins,
    const int sz[4] = {-1, -1, +1, +1};   // moins-plus, plus-plus
    for (int i = 0; i < 4; ++i) {
        Pos p = PoserAuSol(hPied, tx + sx[i] * dx, tz + sz[i] * dz);
        std::cout << "PIED " << p.x << " " << p.y << " " << p.z << "\n";
    }

    int n;
    if (!(std::cin >> n)) return 0;
    for (int i = 0; i < n; ++i) {
        std::string nom, ou;
        long long sxo, syo, szo, x, z;
        std::cin >> nom >> sxo >> syo >> szo >> x >> z >> ou;
        Pos p = (ou == "TABLE") ? PoserSurTable(syo, x, z, H)
                                : PoserAuSol(syo, x, z);
        std::cout << nom << " " << p.x << " " << p.y << " " << p.z << "\n";
    }
    return 0;
}
