#include <iostream>
#include <string>

static long long absval(long long v) { return v < 0 ? -v : v; }

int main() {
    int n;
    if (!(std::cin >> n)){
         return 0;
    }
    int deplaces = 0;
    long long pire = 0;

    for (int i = 0; i < n; ++i) {
        std::string nom;
        long long tx;
        long long ty;
        long long tz;
        long long sx;
        long long sy;
        long long sz;
        std::cin >> nom >> tx >> ty >> tz >> sx >> sy >> sz;

        // mauvais ordre : chaque composante est multipliee par sa propre
        // echelle, puis divisee par 1000 (division entiere tronquee vers zero)
        long long x = sx * tx / 1000;
        long long y = sy * ty / 1000;
        long long z = sz * tz / 1000;

        long long ecart = absval(tx - x);
        long long ey = absval(ty - y);
        long long ez = absval(tz - z);
        if (ey > ecart){
             ecart = ey;
            }
        if (ez > ecart){
             ecart = ez;
            }

        if (ecart != 0){
             ++deplaces;
            }
        if (ecart > pire){
             pire = ecart;
            }

        std::cout << nom << " " << x << " " << y << " " << z << " "
                  << ecart << std::endl;
    }

    std::cout << "DEPLACES " << deplaces << std::endl;
    std::cout << "PIRE " << pire << std::endl;

    return 0;
}