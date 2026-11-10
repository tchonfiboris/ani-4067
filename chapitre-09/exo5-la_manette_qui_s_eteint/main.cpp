#include <iostream>
#include <string>

int main() {
    int T;
    std::cin >> T;

    std::string signes;
    if (T > 0) std::cin >> signes;

    bool tenuAvec = false, tenuSans = false;  // au départ, les deux versions sont LIBRE
    bool tombe = false;                       // objet par terre dans la version SANS
    int precedent = 0;                        // avant l'image 1, current vaut 0
    long long prisesAvec = 0, prisesSans = 0, chutesSans = 0, coinces = 0, differences = 0;

    for (int t = 1; t <= T; ++t) {
        char s = signes[t - 1];
        int active = (s == 'x') ? 0 : 1;
        int current = (s == '1') ? 1 : 0;
        // changed est calculé même pendant la coupure.
        int changed = (current != precedent) ? 1 : 0;
        precedent = current;

        // Version AVEC : rien ne change si l'action est inactive.
        if (active == 1) {
            if (current == 1 && changed == 1) {
                tenuAvec = true;
                ++prisesAvec;
            } else if (current == 0 && changed == 1) {
                tenuAvec = false;
            }
        }

        // Version SANS : même logique, sans le test de active.
        if (current == 1 && changed == 1) {
            if (!tombe) {
                tenuSans = true;
                ++prisesSans;
            }
        } else if (current == 0 && changed == 1) {
            // Un lâcher sur une image inactive, objet en main : l'objet tombe.
            if (active == 0 && tenuSans) {
                ++chutesSans;
                tombe = true;
            }
            tenuSans = false;
        }

        // Images de signe 0 où la version AVEC tient encore l'objet.
        if (s == '0' && tenuAvec) ++coinces;
        if (tenuAvec != tenuSans) ++differences;

        std::cout << t << " " << (tenuAvec ? "TENU" : "LIBRE") << " "
                  << (tenuSans ? "TENU" : "LIBRE") << std::endl;
    }

    std::cout << "PRISES AVEC " << prisesAvec << std::endl;
    std::cout << "PRISES SANS " << prisesSans << std::endl;
    std::cout << "CHUTES SANS " << chutesSans << std::endl;
    std::cout << "COINCES AVEC " << coinces << std::endl;
    std::cout << "DIFFERENCES " << differences << std::endl;
    return 0;
}