#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

struct Action {
    std::string nom;
    std::string usage;
};

// Le reste du programme ne manipule que des usages et des noms d'actions.
// Les noms de commandes n'existent que dans la table lue en entrée.
using Table = std::map<std::string, std::string>;  // usage -> commande

// Lit une table, puis ses images, et rejoue les intentions.
// Renvoie les lignes d'images pour pouvoir comparer deux tables.
static std::vector<std::string> rejouer(int numero, const std::vector<Action>& actions) {
    int U;
    std::cin >> U;
    Table table;
    for (int i = 0; i < U; ++i) {
        std::string usage, commande;
        std::cin >> usage >> commande;
        table[usage] = commande;
    }

    std::cout << "TABLE " << numero << std::endl;

    // Une action dont l'usage manque dans la table ne peut jamais être appuyée.
    std::vector<int> actives;
    for (size_t i = 0; i < actions.size(); ++i) {
        if (table.count(actions[i].usage)) actives.push_back((int)i);
        else std::cout << "INACTIVE " << actions[i].nom << std::endl;
    }

    int T;
    std::cin >> T;

    std::vector<std::string> lignes;
    std::vector<char> appuyeePrecedent(actions.size(), 0);  // rien n'est appuyé avant l'image 1

    for (int t = 1; t <= T; ++t) {
        int k;
        std::cin >> k;
        std::set<std::string> tenues;
        for (int j = 0; j < k; ++j) {
            std::string c;
            std::cin >> c;
            tenues.insert(c);
        }

        std::string ligne = std::to_string(t);
        bool aucune = true;
        std::vector<char> appuyee(actions.size(), 0);

        for (int i : actives) {
            appuyee[i] = tenues.count(table[actions[i].usage]) ? 1 : 0;
            // Vient d'être appuyée : tenue maintenant, et pas à l'image d'avant.
            if (appuyee[i] && !appuyeePrecedent[i]) {
                ligne += " " + actions[i].nom;
                aucune = false;
            }
        }
        if (aucune) ligne += " -";

        appuyeePrecedent = appuyee;
        lignes.push_back(ligne);
        std::cout << ligne << std::endl;
    }
    return lignes;
}

int main() {
    int A;
    std::cin >> A;

    // Les actions sont déclarées une seule fois, pour les deux tables.
    std::vector<Action> actions(A);
    for (auto& a : actions) std::cin >> a.nom >> a.usage;

    std::vector<std::string> premiere = rejouer(1, actions);
    std::vector<std::string> seconde = rejouer(2, actions);

    std::cout << "IDENTIQUES " << (premiere == seconde ? "OUI" : "NON") << std::endl;
    return 0;
}
