#include <iostream>
#include <sstream>
#include <string>
#include <vector>

static std::string strip_cr(std::string s) {
    if (!s.empty() && s.back() == '\r') {
        s.pop_back();
    }
    return s;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    long long hz = 0;
    if (!(std::cin >> hz)) {
        return 0;
    }
    if (hz <= 1) {
        hz = 72;
    }
    const long long period = 1000000000LL / hz;

    std::string line;
    std::getline(std::cin, line); // consomme la fin de ligne de hz

    long long lacet = 0;
    long long tangage = 0;
    long long x = 1700;
    long long y = 0;
    long long z = 0;

    if (std::getline(std::cin, line)) {
        line = strip_cr(line);
        std::istringstream iss(line);
        std::string mode;
        iss >> mode;
        if (mode == "FIXE") {
            iss >> lacet >> tangage >> x >> y >> z;
        } else {
            lacet = 0;
            tangage = 0;
            x = 1700;
            y = 0;
            z = 0;
        }
    }

    int T = 0;
    if (!(std::cin >> T)) {
        T = 0;
    }

    std::vector<long long> clkA(T > 0 ? T : 0);
    std::vector<long long> clkB(T > 0 ? T : 0);

    if (T > 0) {
        for (int i = 0; i < T; ++i) {
            std::cin >> clkA[i];
        }
        for (int i = 0; i < T; ++i) {
            std::cin >> clkB[i];
        }
    }

    std::cout << "PERIODE " << period << '\n';
    std::cout << "POSE " << lacet << ' ' << tangage << ' ' << x << ' ' << y << ' ' << z << '\n';

    int first_brut_diff = 0;
    int first_rel_diff = 0;

    if (T > 0) {
        const long long predA1 = clkA[0] + period;
        const long long predB1 = clkB[0] + period;

        for (int i = 0; i < T; ++i) {
            const int t = i + 1;
            const long long predA = clkA[i] + period;
            const long long predB = clkB[i] + period;

            const long long brut = predB - predA;
            const long long relatif = (predB - predB1) - (predA - predA1);
            const long long scripte = static_cast<long long>(t) * period;

            if (brut != 0 && first_brut_diff == 0) {
                first_brut_diff = t;
            }
            if (relatif != 0 && first_rel_diff == 0) {
                first_rel_diff = t;
            }

            std::cout << t << " BRUT " << brut << " RELATIF " << relatif << " SCRIPTE " << scripte << '\n';
        }
    }

    if (first_brut_diff == 0) {
        std::cout << "BRUT IDENTIQUE\n";
    } else {
        std::cout << "BRUT DIFFERENT " << first_brut_diff << '\n';
    }

    if (first_rel_diff == 0) {
        std::cout << "RELATIF IDENTIQUE\n";
    } else {
        std::cout << "RELATIF DIFFERENT " << first_rel_diff << '\n';
    }

    return 0;
}