#include <iostream>
#include <string>
#include <vector>

struct Mur {
    long long xmin;
    long long xmax;
    long long zmin;
    long long zmax;
};

int main() {
    long long L;
    long long e;
    if (!(std::cin >> L >> e)){
         return 0;
        }
    int n;
    if (!(std::cin >> n)){
         n = 0;
        }

    std::vector<Mur> murs;
    for (int i = 0; i < n; ++i) {
        std::string nom;
        long long cx;
        long long cz;
        long long sx;
        long long sz;
        std::cin >> nom >> cx >> cz >> sx >> sz;

        Mur m;
        m.xmin = cx - sx / 2;
        m.xmax = cx + sx / 2;
        m.zmin = cz - sz / 2;
        m.zmax = cz + sz / 2;
        murs.push_back(m);

        std::cout << nom << " " << m.xmin << " " << m.xmax << " "
                  << m.zmin << " " << m.zmax << std::endl;
    }

    long long h = L / 2;

    struct Angle {
        const char* nom;
        long long x0;
        long long x1;
        long long z0;
        long long z1;
    };
    Angle angles[4] = {
        {"FOND_GAUCHE",   -h - e, -h,     -h - e, -h},
        {"FOND_DROIT",     h,      h + e, -h - e, -h},
        {"ENTREE_GAUCHE", -h - e, -h,      h,      h + e},
        {"ENTREE_DROIT",   h,      h + e,  h,      h + e}
    };

    int trous = 0;
    for (const Angle& a : angles) {
        bool bouche = false;
        // un seul mur doit contenir tout le carré
        for (const Mur& m : murs) {
            if (m.xmin <= a.x0 && m.xmax >= a.x1 &&
                m.zmin <= a.z0 && m.zmax >= a.z1) {
                bouche = true;
                break;
            }
        }
        if (!bouche) ++trous;
        std::cout << a.nom << " " << (bouche ? "BOUCHE" : "TROU") << std::endl;
    }

    std::cout << "TROUS " << trous << std::endl;

    return 0;
}
