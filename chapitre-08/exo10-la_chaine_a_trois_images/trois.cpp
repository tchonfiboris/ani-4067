#include <iostream>

int main() {
    int K;
    if (!(std::cin >> K)) return 0;

    for (int s = 0; s < K; ++s) {
        int n, L, T;
        if (!(std::cin >> n >> L >> T)) break;

        // images peintes par chaque trame
        std::cout << "CIBLES " << n << " " << L;
        for (int u = 1; u <= T; ++u)
            std::cout << " " << (u - 1) % n;
        std::cout << std::endl;

        // trames en conflit : l'image peinte a été soumise par une des L trames d'avant
        int conflits = 0;
        for (int u = 1; u <= T; ++u) {
            bool conflit = false;
            for (int w = u - 1; w >= u - L && w >= 1; --w) {
                if ((w - 1) % n == (u - 1) % n) {
                    conflit = true;
                    break;
                }
            }
            if (conflit) ++conflits;
        }
        std::cout << "CONFLITS " << n << " " << L << " " << conflits << std::endl;
    }
    return 0;
}
