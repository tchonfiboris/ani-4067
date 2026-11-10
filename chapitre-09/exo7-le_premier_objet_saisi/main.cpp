#include <iostream>
#include <vector>

struct Pose {
    long long x = 0, y = 0;
    int k = 0;
};

// Tourne (u, v) de k quarts de tour, sens inverse des aiguilles d'une montre.
static void tourner(long long u, long long v, int k, long long& ru, long long& rv) {
    k = ((k % 4) + 4) % 4;
    switch (k) {
        case 0: ru = u;  rv = v;  break;
        case 1: ru = -v; rv = u;  break;
        case 2: ru = -u; rv = -v; break;
        default: ru = v; rv = -u; break;
    }
}

// A * B : position A + (B tournée de A.k), angle (A.k + B.k) % 4.
static Pose composer(const Pose& A, const Pose& B) {
    long long ru, rv;
    tourner(B.x, B.y, A.k, ru, rv);
    Pose r;
    r.x = A.x + ru;
    r.y = A.y + rv;
    r.k = (A.k + B.k) % 4;
    return r;
}

// Inverse de A : angle (4 - A.k) % 4, position (-A.x, -A.y) tournée de ce nouvel angle.
static Pose inverse(const Pose& A) {
    Pose r;
    r.k = (4 - A.k) % 4;
    tourner(-A.x, -A.y, r.k, r.x, r.y);
    return r;
}

int main() {
    int M, T;
    std::cin >> M >> T;

    std::vector<Pose> objets(M + 1);  // numérotés à partir de 1
    for (int j = 1; j <= M; ++j) std::cin >> objets[j].x >> objets[j].y >> objets[j].k;

    int tenu = 0;       // numéro de l'objet tenu, 0 si aucun
    bool rate = false;  // appui raté sur cette image
    Pose attache;       // calculée une seule fois, à l'appui
    int bPrecedent = 0; // avant l'image 1, b vaut 0
    long long saisies = 0, ratees = 0;

    for (int t = 1; t <= T; ++t) {
        Pose paume;
        int b;
        std::cin >> paume.x >> paume.y >> paume.k >> b;
        rate = false;

        if (b == 1 && bPrecedent == 0) {
            // Appui : l'objet le plus proche, à 150 mm au plus, plus petit numéro à égalité.
            int meilleur = 0;
            long long meilleureDist = 0;
            for (int j = 1; j <= M; ++j) {
                long long dx = objets[j].x - paume.x;
                long long dy = objets[j].y - paume.y;
                long long d = dx * dx + dy * dy;
                if (d <= 22500 && (meilleur == 0 || d < meilleureDist)) {
                    meilleur = j;
                    meilleureDist = d;
                }
            }
            if (meilleur != 0) {
                tenu = meilleur;
                attache = composer(inverse(paume), objets[tenu]);
                ++saisies;
            } else {
                tenu = 0;
                rate = true;
                ++ratees;
            }
        } else if (b == 0 && bPrecedent == 1) {
            // Relâchement : plus rien n'est tenu, l'objet reste où il est.
            tenu = 0;
        }
        bPrecedent = b;

        if (tenu != 0) {
            objets[tenu] = composer(paume, attache);
            std::cout << t << " TIENT " << tenu << " " << objets[tenu].x << " "
                      << objets[tenu].y << " " << objets[tenu].k << std::endl;
        } else if (rate) {
            std::cout << t << " RATE" << std::endl;
        } else {
            std::cout << t << " LIBRE" << std::endl;
        }
    }

    std::cout << "SAISIES " << saisies << std::endl;
    std::cout << "RATEES " << ratees << std::endl;
    for (int j = 1; j <= M; ++j)
        std::cout << "OBJET " << j << " " << objets[j].x << " " << objets[j].y << " "
                  << objets[j].k << std::endl;
    return 0;
}