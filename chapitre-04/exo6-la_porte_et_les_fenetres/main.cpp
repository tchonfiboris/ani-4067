#include <iostream>
#include <string>

int main() {
    long long W;
    long long H;
    long long seuil;
    if (!(std::cin >> W >> H >> seuil)){
         return 0;
        }
    int n;
    if (!(std::cin >> n)){
         n = 0;
        }

    int ok = 0;
    int areprendre = 0;

    for (int i = 0; i < n; ++i) {
        std::string nom;
        long long u;
        long long y;
        long long l;
        long long h;
        long long e;
        long long d;
        std::cin >> nom >> u >> y >> l >> h >> e >> d;

        long long saillie = d + e / 2;   // face avant
        long long arriere = d - e / 2;   // face arriere

        std::string verdict;
        // bornes comparees doublees pour eviter toute troncature de W / 2
        if (2 * u - l < -W || 2 * u + l > W || 2 * y - h < 0 || 2 * y + h > 2 * H)
           { verdict = "DEBORDE";}
        else if (saillie <= 0)
            {verdict = "INVISIBLE";}
        else if (saillie < seuil)
            {verdict = "CLIGNOTE";}
        else if (arriere > seuil)
           { verdict = "DECOLLE";}
        else
            {verdict = "OK";}

        if (verdict == "OK"){
             ++ok;
            }
        else{
             ++areprendre;
            }

        std::cout << nom << " " << saillie << " " << verdict << std::endl;
    }

    std::cout << "OK " << ok << std::endl;
    std::cout << "A REPRENDRE " << areprendre << std::endl;

    return 0;
}