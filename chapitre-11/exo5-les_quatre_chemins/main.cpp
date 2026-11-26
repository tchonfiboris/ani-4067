#include <iostream>
#include <string>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int K = 0;
    if (!(std::cin >> K)) {
        return 0;
    }

    if (K == 0) {
        std::cout << "AUCUNE MACHINE\n";
        return 0;
    }

    for (int i = 1; i <= K; ++i) {
        std::string D, V, L, R, B, G;
        std::cin >> D >> V >> L >> R >> B >> G;

        int loaded = 0;
        int freed = 0;
        bool has_lib = false;
        bool has_entry = false;
        bool xr_ready = false;
        std::string source;

        if (D == "SIMULATEUR") {
            std::cout << i << " BACKEND SIMULATEUR DEMANDE\n";
        } else {
            // 2. Variable d'environnement
            std::string v_state;
            if (V == "-") {
                // rien
            } else if (V == "ABSENT") {
                std::cout << i << " VARIABLE IGNOREE\n";
            } else {
                std::cout << i << " VARIABLE CHARGEE\n";
                ++loaded;
                has_lib = true;
                v_state = V;
                source = "VARIABLE";
            }

            // 3. Loader standard uniquement si aucune bibliotheque n'est chargee
            std::string l_state;
            if (!has_lib) {
                if (L == "ABSENT") {
                    std::cout << i << " LOADER ABSENT\n";
                } else {
                    std::cout << i << " LOADER CHARGE\n";
                    ++loaded;
                    has_lib = true;
                    l_state = L;
                    source = "LOADER";
                }
            }

            // 4. Verification du point d'entree sur la bibliotheque chargee
            if (has_lib) {
                std::string active_state = (source == "VARIABLE") ? v_state : l_state;
                if (active_state == "BON") {
                    has_entry = true;
                } else if (active_state == "SANS") {
                    std::cout << i << " SANS_ENTREE\n";
                    ++freed;
                    has_lib = false;
                }
            }

            // 5. Decouverte directe si toujours pas de point d'entree
            if (!has_entry) {
                std::cout << i << " DIRECT " << R << '\n';
                if (R == "NEGO_KO" || R == "BON") {
                    ++loaded;
                    has_lib = true;
                    if (R == "BON") {
                        has_entry = true;
                        source = "DIRECT";
                    }
                }
            }

            // 6. Backend OpenXR ou indisponibilite + liaison graphique
            if (!has_entry) {
                std::cout << i << " BACKEND INDISPONIBLE\n";
                if (has_lib) {
                    ++freed;
                    has_lib = false;
                }
            } else {
                std::cout << i << " BACKEND OPENXR " << source << '\n';
                if (B == "NON") {
                    if (has_lib) {
                        ++freed;
                        has_lib = false;
                    }
                    std::cout << i << " LIAISON ECHOUEE\n";
                } else {
                    xr_ready = true;
                }
            }
        }

        // 7. Niveau atteint
        if (D == "OPENXR" && xr_ready) {
            std::cout << i << " NIVEAU 1 CASQUE\n";
        } else if (G == "OUI") {
            std::cout << i << " NIVEAU 2 SIMULATEUR CARTE\n";
        } else {
            std::cout << i << " NIVEAU 3 SIMULATEUR LOGICIEL\n";
        }

        // 8. Bilan des bibliotheques
        std::cout << i << " CHARGEES " << loaded << " LIBEREES " << freed << '\n';
    }

    return 0;
}