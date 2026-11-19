#include <cmath>
#include <iostream>
#include <string>

typedef long long ll;

// Tourne (x, z) de k quarts de tour ; y ne tourne pas.
static void tourner(int k, ll x, ll z, ll& rx, ll& rz) {
    switch (k % 4) {
        case 0: rx = x;  rz = z;  break;
        case 1: rx = z;  rz = -x; break;
        case 2: rx = -x; rz = -z; break;
        default: rx = -z; rz = x; break;
    }
}

// Racine carrée arrondie à l'entier le plus proche, calculée exactement sur des entiers.
static ll racineArrondie(ll d2) {
    ll r = (ll)std::sqrt((double)d2);
    while (r * r > d2) --r;
    while ((r + 1) * (r + 1) <= d2) ++r;
    // (r + 0.5)^2 = r^2 + r + 0.25 : on monte d'un cran dès que d2 >= r^2 + r + 1
    if (d2 >= r * r + r + 1) ++r;
    return r;
}

int main() {
    ll ax, ay, az;
    int ak;
    std::cin >> ax >> ay >> az >> ak;

    ll ex, ey, ez;
    std::cin >> ex >> ey >> ez;

    int N;
    std::cin >> N;

    for (int i = 1; i <= N; ++i) {
        std::string E;
        ll x, y, z, w, h;
        int k;
        std::cin >> E >> x >> y >> z >> k >> w >> h;

        // Un espace non précisé ("-") retombe dans LOCAL.
        bool stage = (E == "S");

        ll cx, cy, cz;
        int ck;
        if (stage) {
            cx = x; cy = y; cz = z; ck = k;
        } else {
            ll rx, rz;
            tourner(ak, x, z, rx, rz);
            cx = ax + rx;
            cy = ay + y;
            cz = az + rz;
            ck = (ak + k) % 4;
        }

        std::cout << "PANNEAU " << i << " " << (stage ? "STAGE" : "LOCAL") << std::endl;

        ll coinsX[4] = {-w / 2, w / 2, w / 2, -w / 2};
        ll coinsY[4] = {-h / 2, -h / 2, h / 2, h / 2};
        for (int c = 0; c < 4; ++c) {
            ll rx, rz;
            tourner(ck, coinsX[c], 0, rx, rz);
            std::cout << cx + rx << " " << cy + coinsY[c] << " " << cz + rz << std::endl;
        }

        ll dx = cx - ex, dy = cy - ey, dz = cz - ez;
        std::cout << "DISTANCE " << racineArrondie(dx * dx + dy * dy + dz * dz) << std::endl;
    }

    std::cout << "PANNEAUX " << N << std::endl;
    return 0;
}