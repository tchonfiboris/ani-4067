#include <iostream>
#include <string>

int main() {
    int K, N;
    std::cin >> K >> N;

    bool trameOuverte = false;
    int index[2] = {0, 0};
    bool empruntee[2] = {false, false};
    int journal = 0, avertissements = 0, silencieux = 0;

    for (int n = 1; n <= N; ++n) {
        std::string appel;
        std::cin >> appel;

        std::cout << n << " " << appel;

        if (appel == "wait") {
            if (trameOuverte) {
                std::cout << " REFUSE";
                ++journal;
            } else {
                std::cout << " OK";
            }
        } else if (appel == "begin") {
            if (trameOuverte) {
                std::cout << " REFUSE";
                ++journal;
            } else {
                std::cout << " OK";
                trameOuverte = true;
            }
        } else if (appel == "acquire") {
            std::string oeil;
            std::cin >> oeil;
            int x = (oeil == "G") ? 0 : 1;
            if (empruntee[x]) {
                std::cout << " REFUSE";
                ++silencieux;
            } else {
                std::cout << " OK " << index[x];
                empruntee[x] = true;
            }
        } else if (appel == "release") {
            std::string oeil;
            std::cin >> oeil;
            int x = (oeil == "G") ? 0 : 1;
            if (!empruntee[x]) {
                std::cout << " REFUSE";
                ++silencieux;
            } else {
                std::cout << " OK";
                empruntee[x] = false;
                index[x] = (index[x] + 1) % K;
            }
        } else if (appel == "end") {
            std::string a;
            std::cin >> a;
            bool projection = (a != "-");
            bool renseignee[2] = {false, false};
            if (projection) {
                int d;
                std::cin >> d;
                renseignee[0] = (a == "1");
                renseignee[1] = (d == 1);
            }

            if (!trameOuverte) {
                std::cout << " REFUSE AUCUNE";
                ++journal;
            } else {
                trameOuverte = false;  // la trame se ferme dans tous les cas
                int bloque = -1;
                if (projection) {
                    for (int x = 0; x < 2; ++x) {
                        if (renseignee[x] && empruntee[x]) {
                            bloque = x;
                            break;
                        }
                    }
                }
                if (bloque >= 0) {
                    std::cout << " REFUSE ACQUISE " << (bloque == 0 ? "G" : "D");
                    ++journal;
                } else {
                    std::cout << " OK";
                    if (projection && (!renseignee[0] || !renseignee[1])) {
                        std::cout << " AVERT";
                        if (!renseignee[0]) {
                            std::cout << " G";
                            ++avertissements;
                        }
                        if (!renseignee[1]) {
                            std::cout << " D";
                            ++avertissements;
                        }
                    }
                }
            }
        }

        std::cout << std::endl;
    }

    std::cout << "JOURNAL " << journal << std::endl;
    std::cout << "AVERTISSEMENTS " << avertissements << std::endl;
    std::cout << "SILENCIEUX " << silencieux << std::endl;
    return 0;
}