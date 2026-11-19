#include <iostream>
#include <string>

typedef long long ll;

static ll valeurAbsolue(ll x) { return x < 0 ? -x : x; }

int main() {
    ll w;
    int T;
    std::cin >> w >> T;

    int fausses = 0;
    ll pireCasque = 0, pireSimulateur = 0;

    for (int t = 1; t <= T; ++t) {
        ll P, S, A;
        std::string M;
        std::cin >> P >> S >> A >> M;

        // pose soumise - pose du rendu, écrit w * (écart d'instants) pour limiter les débordements
        ll casque = (M == "F") ? w * (S - P) : 0;
        ll simulateur = w * (A - P);

        if (casque != 0) ++fausses;
        if (valeurAbsolue(casque) > pireCasque) pireCasque = valeurAbsolue(casque);
        if (valeurAbsolue(simulateur) > pireSimulateur) pireSimulateur = valeurAbsolue(simulateur);

        std::cout << t << " CASQUE " << casque << " SIMULATEUR " << simulateur << std::endl;
    }

    std::cout << "FAUSSES " << fausses << std::endl;
    std::cout << "PIRE CASQUE " << pireCasque << std::endl;
    std::cout << "PIRE SIMULATEUR " << pireSimulateur << std::endl;
    return 0;
}