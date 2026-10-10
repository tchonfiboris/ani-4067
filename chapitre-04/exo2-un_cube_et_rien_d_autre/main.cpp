#include <iostream>
#include <string>

int main() {
    int n;
    if (!(std::cin >> n)){
         return 0;
        }

    int visibles = 0;
    int enPanne = 0;

    for (int i = 0; i < n; ++i) {
        std::string nom;
        unsigned long long drapeaux;
        long long sx; 
        long long sy; 
        long long sz; 
        long long distance; 
        long long lumieres; 
        long long ambiante; 
        long long proche;
        std::cin >> nom >> drapeaux >> sx >> sy >> sz
                 >> distance >> lumieres >> ambiante >> proche;

        long long faceAvant = distance - sz / 2;
        std::string verdict;

        if ((drapeaux & 2ULL) == 0)
            verdict = "RENDER3D ETEINT";
        else if (sx == 0 || sy == 0 || sz == 0)
            verdict = "ECHELLE NULLE";
        else if (faceAvant <= 0)
            verdict = "CAMERA DANS LE CUBE";
        else if (faceAvant < proche)
            verdict = "COUPE PAR LE PLAN PROCHE";
        else if (lumieres == 0 && ambiante == 0)
            verdict = "PAS DE LUMIERE";
        else
            verdict = "VISIBLE";

        if (verdict == "VISIBLE") ++visibles;
        else ++enPanne;

        std::cout << nom << " " << verdict << std::endl;
    }

    std::cout << "VISIBLES " << visibles << std::endl;
    std::cout << "EN PANNE " << enPanne << std::endl;

    return 0;
}
