#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

static std::vector<std::string> ordreDe(const std::string& plateforme) {
    if (plateforme == "WINDOWS") 
    return {"VULKAN", "DX12", "DX11", "OPENGL", "SOFTWARE"};
    if (plateforme == "MACOS")   
    return {"METAL", "OPENGL", "SOFTWARE"};
    if (plateforme == "IOS")     
    return {"METAL", "SOFTWARE"};
    return {"VULKAN", "OPENGL", "SOFTWARE"}; // ANDROID et toute autre plateforme
}

int main() {
    const std::map<std::string, std::string> lisible = {
        {"VULKAN", "Vulkan"},      {"DX12", "DirectX 12"}, {"DX11", "DirectX 11"},
        {"OPENGL", "OpenGL"},      {"METAL", "Metal"},     {"SOFTWARE", "Software"}};

    int n;
    if (!(std::cin >> n)){
         n = 0;
        }

    int ignorees = 0; 
    int logiciel = 0;
    std::set<std::string> differents;

    for (int i = 0; i < n; ++i) {
        std::string nom; 
        std::string plateforme;
        int k;
        std::cin >> nom >> plateforme >> k;
        std::set<std::string> liste;
        for (int j = 0; j < k; ++j) {
            std::string api;
            std::cin >> api;
            liste.insert(api);
        }

        std::vector<std::string> ordre = ordreDe(plateforme);
        std::set<std::string> dansOrdre(ordre.begin(), ordre.end());
        for (const std::string& api : liste)
            if (!dansOrdre.count(api)){
                 ++ignorees;
                }

        std::string choisie = "SOFTWARE"; // repli : marche partout
        for (const std::string& api : ordre) {
            if (liste.count(api)) { 
                choisie = api; 
                break; 
            }
        }

        const std::string& nomLisible = lisible.at(choisie);
        if (choisie == "SOFTWARE"){
             ++logiciel;
            }
        differents.insert(nomLisible);
        std::cout << nom << " " << nomLisible << std::endl;
    }

    std::cout << "IGNOREES " << ignorees << std::endl;
    std::cout << "LOGICIEL " << logiciel << std::endl;
    std::cout << "DIFFERENTES " << differents.size() << std::endl;

    return 0;
}