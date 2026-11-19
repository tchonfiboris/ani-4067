#include <cmath>
#include <iostream>

typedef long long ll;

static ll valeurAbsolue(ll x) { return x < 0 ? -x : x; }

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
    ll N, d;
    std::cin >> N >> d;

    ll sommePosition = 0, sommeAngle = 0;

    for (ll t = 1; t <= N; ++t) {
        ll x1, z1, a1, x2, z2, a2;
        std::cin >> x1 >> z1 >> a1 >> x2 >> z2 >> a2;

        ll dx = x2 - x1, dz = z2 - z1;
        ll p = racineArrondie(dx * dx + dz * dz);
        ll a = valeurAbsolue(a2 - a1);

        sommePosition += p;
        sommeAngle += a;

        std::cout << t << " POSITION " << p << " ANGLE " << a << std::endl;
    }

    if (N == 0 || d == 0) {
        std::cout << "AUCUNE" << std::endl;
        return 0;
    }

    // Sommes positives : la division entière arrondit bien à l'entier inférieur.
    std::cout << "MOYENNE POSITION " << sommePosition / N << std::endl;
    std::cout << "MOYENNE ANGLE " << sommeAngle / N << std::endl;
    // millièmes de degré par milliseconde = degrés par seconde
    std::cout << "VITESSE " << sommeAngle / (N * d) << std::endl;
    return 0;
}
