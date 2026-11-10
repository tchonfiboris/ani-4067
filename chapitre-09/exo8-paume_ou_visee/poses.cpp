#include <cmath>
#include <iostream>
#include <vector>

struct Vec {
    long long x, y, z;
};

// Tourne (x, z) de k quarts de tour ; y ne change pas.
static Vec tourner(const Vec& v, int k) {
    k = ((k % 4) + 4) % 4;
    Vec r = v;
    switch (k) {
        case 0: r.x = v.x;  r.z = v.z;  break;
        case 1: r.x = v.z;  r.z = -v.x; break;
        case 2: r.x = -v.x; r.z = -v.z; break;
        default: r.x = -v.z; r.z = v.x; break;
    }
    return r;
}

// Du repère de la tête vers la salle : rotation du lacet, puis position de la tête.
static Vec versSalle(const Vec& local, const Vec& tete, int k) {
    Vec r = tourner(local, k);
    return {r.x + tete.x, r.y + tete.y, r.z + tete.z};
}

static long long dist2(const Vec& a, const Vec& b) {
    long long dx = a.x - b.x, dy = a.y - b.y, dz = a.z - b.z;
    return dx * dx + dy * dy + dz * dz;
}

// Objet le plus proche à 150 mm au plus (22500 au carré) ; 0 si aucun. Égalité : plus petit numéro.
static int plusProche(const Vec& p, const std::vector<Vec>& objets) {
    int meilleur = 0;
    long long meilleureDist = 0;
    for (size_t j = 1; j < objets.size(); ++j) {
        long long d = dist2(p, objets[j]);
        if (d <= 22500 && (meilleur == 0 || d < meilleureDist)) {
            meilleur = (int)j;
            meilleureDist = d;
        }
    }
    return meilleur;
}

static void ecrireSaisie(const char* nom, int j) {
    std::cout << "SAISIE " << nom << " ";
    if (j == 0) std::cout << "AUCUNE";
    else std::cout << j;
    std::cout << std::endl;
}

static void ecrirePose(const char* nom, const Vec& v) {
    std::cout << nom << " " << v.x << " " << v.y << " " << v.z << std::endl;
}

int main() {
    int H, M;
    std::cin >> H >> M;

    struct Tete {
        Vec pos;
        int k;
    };
    std::vector<Tete> tetes(H);
    for (auto& t : tetes) std::cin >> t.pos.x >> t.pos.y >> t.pos.z >> t.k;

    std::vector<Vec> objets(M + 1);  // numérotés à partir de 1
    for (int j = 1; j <= M; ++j) std::cin >> objets[j].x >> objets[j].y >> objets[j].z;

    // Poses de la main droite dans le repère de la tête ; la gauche change le signe de x.
    const Vec paumeD = {180, -300, -250};
    const Vec viseeD = {180, -250, -400};
    const Vec paumeG = {-paumeD.x, paumeD.y, paumeD.z};
    const Vec viseeG = {-viseeD.x, viseeD.y, viseeD.z};

    for (int h = 1; h <= H; ++h) {
        const Tete& t = tetes[h - 1];
        Vec pd = versSalle(paumeD, t.pos, t.k);
        Vec vd = versSalle(viseeD, t.pos, t.k);
        Vec pg = versSalle(paumeG, t.pos, t.k);
        Vec vg = versSalle(viseeG, t.pos, t.k);

        std::cout << "TETE " << h << std::endl;
        ecrirePose("PAUME D", pd);
        ecrirePose("VISEE D", vd);
        ecrirePose("PAUME G", pg);
        ecrirePose("VISEE G", vg);

        // La saisie se fait avec la paume droite et avec la visée droite.
        ecrireSaisie("PAUME", plusProche(pd, objets));
        ecrireSaisie("VISEE", plusProche(vd, objets));
    }

    // Distance entre la paume droite et la visée droite (la rotation ne la change pas).
    double e = std::sqrt((double)dist2(paumeD, viseeD));
    std::cout << "ECART " << std::llround(e) << std::endl;
    return 0;
}
