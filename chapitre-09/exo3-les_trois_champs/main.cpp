#include <iostream>
#include <string>

int main() {
    int T;
    std::cin >> T;

    std::string signes;
    if (T > 0) std::cin >> signes;

    int precedent = 0;  // avant l'image 1, current vaut 0
    long long appuis = 0, relaches = 0, fauxRelaches = 0, tenues = 0;

    for (int t = 1; t <= T; ++t) {
        char s = signes[t - 1];

        int active = (s == 'x') ? 0 : 1;
        // Une action inactive vaut toujours 0.
        int current = (s == '1') ? 1 : 0;
        int changed = (current != precedent) ? 1 : 0;

        if (current == 1 && changed == 1) ++appuis;
        if (current == 0 && changed == 1) {
            ++relaches;
            // Un relâchement où l'action est inactive est un faux relâchement.
            if (active == 0) ++fauxRelaches;
        }
        if (current == 1) ++tenues;

        std::cout << t << " " << current << " " << changed << " " << active << std::endl;
        precedent = current;
    }

    std::cout << "APPUIS " << appuis << std::endl;
    std::cout << "RELACHES " << relaches << std::endl;
    std::cout << "FAUX RELACHES " << fauxRelaches << std::endl;
    std::cout << "TENUES " << tenues << std::endl;
    return 0;
}