#include <iostream>
#include <string>

int main() {

    int n;
    std::cin >> n;

    int sansGarde = 0;

    for (int i = 0; i < n; ++i) {
        std::string evenement;
        std::cin >> evenement;

        if (evenement == "enfonce") {
            std::cout << "SAISIR" << std::endl;
            ++sansGarde;
        } else if (evenement == "repete") {
            std::cout << "RIEN" << std::endl;
            ++sansGarde;
        } else if (evenement == "relache") {
            std::cout << "LACHER" << std::endl;
        } else {
            std::cout << "RIEN" << std::endl;
        }
    }

    std::cout << "SANS_GARDE " << sansGarde << std::endl;

    return 0;
}
