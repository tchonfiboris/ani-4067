#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

int main() {
    int n;
    std::cin >> n;

    // Registre ordonné par ordre de pose : (id, type)
    std::vector<std::pair<long long, std::string>> registre;

    for (int i = 0; i < n; ++i) {
        std::string cmd;
        std::cin >> cmd;

        if (cmd == "poser") {
            long long id;
            std::string type;
            std::cin >> id; 
            std::cin >> type;

            // Retirer l'ancien rappel de même id, puis ajouter à la fin
            registre.erase(
                std::remove_if(registre.begin(), registre.end(),
                    [id](const auto& r) { return r.first == id; }),
                registre.end());
            registre.push_back({id, type});
        } else if (cmd == "retirer") {
            long long id;
            std::cin >> id;

            registre.erase(
                std::remove_if(registre.begin(), registre.end(),
                    [id](const auto& r) { return r.first == id; }),
                registre.end());
        } else if (cmd == "envoyer") {
            std::string type;
            std::cin >> type;

            bool premier = true;
            for (const auto& r : registre) {
                if (r.second == type) {
                    if (!premier){
                         std::cout << " ";}
                    std::cout << r.first;
                    premier = false;
                }
            }
            if (premier){
                 std::cout << "AUCUN";}
            std::cout << std::endl;
        }
    }

    return 0;
}
