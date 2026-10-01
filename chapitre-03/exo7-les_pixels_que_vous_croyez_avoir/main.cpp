#include <iostream>

int main() {
    int n;
    std::cin >> n;

    int lisible = 0;

    for (int i = 0; i < n; ++i) {
        long long largeur; 
        long long hauteur; 
        long long echelle; 
        long long champ;
        std::cin >> largeur;  
        std::cin >> hauteur;  
        std::cin >> echelle;  
        std::cin >> champ;

        long long lr = largeur * echelle / 100;
        long long hr = hauteur * echelle / 100;
        long long ppd = (lr + champ / 2) / champ;

        std::cout << lr << " " << hr << " " << ppd << std::endl;

        if (ppd >= 15) {
            ++lisible;}
    }

    std::cout << "LISIBLE " << lisible << std::endl;

    return 0;
}
