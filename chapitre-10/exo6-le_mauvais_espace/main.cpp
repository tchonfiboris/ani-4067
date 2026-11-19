#include <iostream>
#include <string>

typedef long long ll;

struct Pose {
    ll x, y, z;
    int k;
};

// Compose l'ancre avec une pose : on tourne (x, z) de A.k quarts de tour, puis on ajoute l'ancre.
static Pose composer(const Pose& A, const Pose& p) {
    ll rx, rz;
    switch (A.k % 4) {
        case 0: rx = p.x;  rz = p.z;  break;
        case 1: rx = p.z;  rz = -p.x; break;
        case 2: rx = -p.x; rz = -p.z; break;
        default: rx = -p.z; rz = p.x; break;
    }
    Pose r;
    r.x = A.x + rx;
    r.y = A.y + p.y;
    r.z = A.z + rz;
    r.k = (A.k + p.k) % 4;
    return r;
}

int main() {
    Pose ancre;
    std::cin >> ancre.x >> ancre.y >> ancre.z >> ancre.k;

    int N;
    std::cin >> N;

    int justes = 0, fausses = 0;

    for (int i = 1; i <= N; ++i) {
        std::string D, C;
        Pose p;
        std::cin >> D >> C >> p.x >> p.y >> p.z >> p.k;

        Pose vraie = (D == "S") ? p : composer(ancre, p);
        Pose crue = (C == "S") ? p : composer(ancre, p);

        ll dx = crue.x - vraie.x;
        ll dy = crue.y - vraie.y;
        ll dz = crue.z - vraie.z;
        int dk = (crue.k - vraie.k + 4) % 4;

        std::cout << i << " CRU " << crue.x << " " << crue.y << " " << crue.z << " " << crue.k << std::endl;
        std::cout << i << " ECART " << dx << " " << dy << " " << dz << " " << dk << std::endl;

        if (dx == 0 && dy == 0 && dz == 0 && dk == 0) ++justes;
        else ++fausses;
    }

    std::cout << "JUSTES " << justes << std::endl;
    std::cout << "FAUSSES " << fausses << std::endl;
    return 0;
}