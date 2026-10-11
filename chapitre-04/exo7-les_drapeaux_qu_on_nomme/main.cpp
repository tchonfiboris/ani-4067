#include <cstdint>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

struct Drapeau {
    const char* nom;
    uint32_t valeur;
};

// Les treize drapeaux simples
static const Drapeau SIMPLES[13] = {
    {"RENDER2D", 1u},     {"RENDER3D", 2u},      {"TEXT", 4u},
    {"UI", 8u},           {"SHADOW", 16u},       {"POST_PROCESS", 32u},
    {"VFX", 64u},         {"ANIMATION", 128u},   {"OVERLAY", 256u},
    {"SIMULATION", 512u}, {"OFFSCREEN", 1024u},  {"RAYTRACING", 2048u},
    {"GPU_CULLING", 4096u}
};

// Les cinq noms composes
static const Drapeau COMPOSES[5] = {
    {"NONE", 0u},
    {"2D_ESSENTIALS", 1u | 4u},
    {"3D_BASE", 2u | 16u | 32u},
    {"DEBUG", 256u | 512u},
    {"ALL", 4294967295u}
};

static bool chercher(const std::string& nom, uint32_t& valeur) {
    for (const Drapeau& d : SIMPLES)
        if (nom == d.nom) { valeur = d.valeur; return true; }
    for (const Drapeau& d : COMPOSES)
        if (nom == d.nom) { valeur = d.valeur; return true; }
    return false;
}

int main() {
    int n;
    if (!(std::cin >> n)){
         return 0;
        }

    uint32_t valeur = 0;
    std::vector<std::string> inconnus;

    for (int i = 0; i < n; ++i) {
        std::string nom;
        std::cin >> nom;
        uint32_t v;
        if (chercher(nom, v))
            {valeur |= v;}           // OU binaire, pas une addition
        else
            {inconnus.push_back(nom);}
    }

    // Rien de nomme : la configuration garde sa valeur par defaut, ALL
    if (n == 0){
         valeur = 4294967295u;
        }

    for (const std::string& nom : inconnus)
        {std::cout << "INCONNU " << nom << std::endl;}

    std::cout << "VALEUR " << valeur << std::endl;
    std::printf("HEXA 0x%08X\n", (unsigned)valeur);

    // Dependances, dans l'ordre : TEXT, UI, SHADOW, OVERLAY
    struct Dep {
        const char* nom;
        uint32_t bit;
        std::vector<std::pair<const char*, uint32_t>> besoins;
    };
    const uint32_t R2D = 1u, R3D = 2u, TXT = 4u;
    std::vector<Dep> deps = {
        {"TEXT",    4u,   {{"RENDER2D", R2D}}},
        {"UI",      8u,   {{"RENDER2D", R2D}, {"TEXT", TXT}}},
        {"SHADOW",  16u,  {{"RENDER3D", R3D}}},
        {"OVERLAY", 256u, {{"RENDER2D", R2D}, {"TEXT", TXT}}}
    };
    for (const Dep& d : deps) {
        if (!(valeur & d.bit)) 
        continue;   // un drapeau eteint ne reclame rien
        for (const auto& b : d.besoins)
            if (!(valeur & b.second))
                {std::cout << "MANQUE " << d.nom << " " << b.first << std::endl;}
    }

    int allumes = 0;
    for (const Drapeau& d : SIMPLES)
        if (valeur & d.valeur){
             ++allumes;
            }

    std::cout << "ALLUMES " << allumes << std::endl;
    std::cout << "ETEINTS " << (13 - allumes) << std::endl;

    return 0;
}