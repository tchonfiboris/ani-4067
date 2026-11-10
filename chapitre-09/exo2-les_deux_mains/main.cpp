#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>

int main() {
    // Table du simulateur : usage -> (main, commande).
    const std::map<std::string, std::pair<std::string, std::string>> table = {
        {"SELECT", {"DROITE", "SOURIS_G"}},
        {"GRAB", {"DROITE", "SOURIS_D"}},
        {"MENU", {"GAUCHE", "TAB"}},
        {"MOVE", {"GAUCHE", "FLECHES"}},
        {"AIM_POSE", {"DROITE", "AUCUNE"}},
        {"GRIP_POSE", {"DROITE", "AUCUNE"}},
        {"HAPTIC", {"DROITE", "AUCUNE"}},
        {"SELECT_LEFT", {"GAUCHE", "SOURIS_M"}},
        {"GRAB_LEFT", {"GAUCHE", "MAJ_G"}},
        {"AIM_POSE_LEFT", {"GAUCHE", "AUCUNE"}},
        {"GRIP_POSE_LEFT", {"GAUCHE", "AUCUNE"}},
        {"HAPTIC_LEFT", {"GAUCHE", "AUCUNE"}},
        {"MOVE_RIGHT", {"DROITE", "IJKL"}}};

    int A, T;
    std::cin >> A >> T;

    std::vector<std::string> commandes(A);
    int droite = 0, gauche = 0;

    for (int i = 0; i < A; ++i) {
        std::string nom, usage;
        std::cin >> nom >> usage;
        const auto& e = table.at(usage);
        commandes[i] = e.second;
        if (e.first == "DROITE") ++droite;
        else ++gauche;
        std::cout << nom << " " << e.first << " " << e.second << std::endl;
    }

    const std::set<std::string> tete = {"Z", "Q", "S", "D", "W", "A"};
    int imagesTete = 0;

    for (int t = 1; t <= T; ++t) {
        int k;
        std::cin >> k;
        std::set<std::string> tenues;
        for (int j = 0; j < k; ++j) {
            std::string c;
            std::cin >> c;
            tenues.insert(c);
        }

        // Les lettres ZQSDWA bougent la tête, elles ne comptent pour aucune action.
        for (const auto& l : tete)
            if (tenues.count(l)) {
                ++imagesTete;
                break;
            }

        auto tenue = [&](const std::string& c) { return tenues.count(c) > 0; };
        // Axe : +1 pour le côté positif, -1 pour le négatif, 0 si les deux.
        auto axe = [&](const char* plus, const char* moins) {
            return (tenue(plus) ? 1 : 0) - (tenue(moins) ? 1 : 0);
        };

        std::cout << t;
        for (int i = 0; i < A; ++i) {
            const std::string& c = commandes[i];
            std::cout << " ";
            if (c == "AUCUNE") {
                std::cout << "-";
            } else if (c == "FLECHES") {
                std::cout << axe("F_DROITE", "F_GAUCHE") << ","
                          << axe("F_HAUT", "F_BAS");
            } else if (c == "IJKL") {
                std::cout << axe("L", "J") << "," << axe("I", "K");
            } else {
                std::cout << (tenue(c) ? 1 : 0);
            }
        }
        std::cout << std::endl;
    }

    std::cout << "DROITE " << droite << std::endl;
    std::cout << "GAUCHE " << gauche << std::endl;
    std::cout << "TETE " << imagesTete << std::endl;
    return 0;
}