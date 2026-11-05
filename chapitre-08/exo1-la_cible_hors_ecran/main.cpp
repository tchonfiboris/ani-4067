#include <iostream>
#include <string>
#include <utility>
#include <vector>

int main() {
    long long L, H;
    int F, N;
    if (!(std::cin >> L >> H >> F >> N)) return 0;

    bool offscreen = false;
    bool bloque = false;
    std::vector<std::pair<long long, long long>> cibles; // cible k = cibles[k-1]
    int vers = 0;                                        // 0 = fenêtre
    long long zoneW = L, zoneH = H;
    std::vector<bool> pris(F, false);
    int numImage = 0, nbImages = 0;

    for (int i = 0; i < N && !bloque; ++i) {
        std::string ordre;
        if (!(std::cin >> ordre)) break;

        if (ordre == "allume") {
            std::string nom;
            std::cin >> nom;
            if (nom == "OFFSCREEN") offscreen = true;
        } else if (ordre == "cible") {
            long long w, h;
            std::cin >> w >> h;
            if (!offscreen) {
                std::cout << "CIBLE NULLE" << std::endl;
            } else {
                cibles.push_back({w, h});
                std::cout << "CIBLE " << cibles.size() << " " << w << " " << h << std::endl;
            }
        } else if (ordre == "vers") {
            long long k;
            std::cin >> k;
            if (k == 0 || (k >= 1 && k <= (long long)cibles.size()))
                vers = (int)k;
            else
                std::cout << "VERS REFUSE" << std::endl;
        } else if (ordre == "taille") {
            std::cin >> zoneW >> zoneH;
        } else if (ordre == "image") {
            ++numImage;
            int t = (numImage - 1) % F;
            if (pris[t]) {
                std::cout << "BLOQUE " << numImage << std::endl;
                bloque = true;
                break;
            }
            ++nbImages;
            if (vers == 0) {
                std::cout << "IMAGE " << numImage << " FENETRE" << std::endl;
            } else {
                std::cout << "IMAGE " << numImage << " CIBLE " << vers << std::endl;
                auto [cw, ch] = cibles[vers - 1];
                if (zoneW > cw || zoneH > ch) pris[t] = true;
            }
        }
    }

    std::cout << "IMAGES " << nbImages << std::endl;
    std::cout << "ETAT " << (bloque ? "BLOQUE" : "LIBRE") << std::endl;
    return 0;
}