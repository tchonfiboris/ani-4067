#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

int main() {
    // Numéro de chaque usage.
    const std::map<std::string, int> usages = {
        {"SELECT", 0},        {"GRAB", 1},           {"MENU", 2},
        {"MOVE", 3},          {"AIM_POSE", 4},       {"GRIP_POSE", 5},
        {"HAPTIC", 6},        {"SELECT_LEFT", 7},    {"GRAB_LEFT", 8},
        {"AIM_POSE_LEFT", 9}, {"GRIP_POSE_LEFT", 10}, {"HAPTIC_LEFT", 11},
        {"MOVE_RIGHT", 12}};

    int N;
    std::cin >> N;

    std::vector<std::string> noms;  // noms[h - 1] : nom de l'action de handle h
    std::set<std::string> vus;
    long long doubles = 0;
    bool attache = false;
    long long k = 0;  // nombre d'actions connues de la session

    for (int i = 0; i < N; ++i) {
        std::string cmd;
        std::cin >> cmd;

        if (cmd == "cree") {
            std::string nom, type, usage;
            std::cin >> nom >> type >> usage;

            // Le handle vaut le nombre d'actions déclarées, celle-ci comprise.
            noms.push_back(nom);
            long long h = noms.size();

            // Le nom ne sert qu'au journal : un doublon a quand même son handle.
            if (!vus.insert(nom).second) ++doubles;

            auto it = usages.find(usage);
            int u = (it != usages.end()) ? it->second : -1;
            std::cout << "ACTION " << h << " " << nom << " " << type << " " << u << std::endl;
        } else if (cmd == "attache") {
            if (attache) {
                std::cout << "ATTACHE REFUSE" << std::endl;
            } else {
                attache = true;
                k = noms.size();
                std::cout << "ATTACHE " << k << std::endl;
            }
        } else if (cmd == "lit") {
            long long h;  // jusqu'à 4294967295
            std::cin >> h;
            long long declarees = noms.size();

            if (h == 0 || h > declarees) {
                std::cout << "LIT " << h << " INVALIDE" << std::endl;
            } else if (!attache || h > k) {
                std::cout << "LIT " << h << " INCONNUE" << std::endl;
            } else {
                std::cout << "LIT " << h << " " << noms[h - 1] << std::endl;
            }
        }
    }

    std::cout << "ACTIONS " << noms.size() << std::endl;
    std::cout << "ATTACHEES " << (attache ? k : 0) << std::endl;
    std::cout << "NOMS EN DOUBLE " << doubles << std::endl;
    return 0;
}