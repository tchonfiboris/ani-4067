#include <iostream>
#include <sstream>
#include <string>

int main() {
    std::string ligne;
    std::getline(std::cin, ligne);
    int n = std::stoi(ligne);

    for (int i = 0; i < n; ++i) {
        std::getline(std::cin, ligne);
        std::istringstream flux(ligne);

        bool w = false; 
        bool z = false; 
        bool s = false;
        bool a = false; 
        bool q = false; 
        bool d = false;

        std::string t;
        while (flux >> t) {
            if (t == "W"){
                 w = true;}
            else if (t == "Z") {
                z = true;}
            else if (t == "S") {
                s = true;}
            else if (t == "A") {
                a = true;}
            else if (t == "Q") {
                q = true;}
            else if (t == "D") {
                d = true;}
            // toute autre touche (dont "rien") est ignorée
        }

        int avance = 0; 
        int cote = 0;
        if (w) {
            ++avance;}
        if (z) {
            ++avance;}
        if (s) {
            --avance;}
        if (a) {
            --cote;}
        if (q) {
            --cote;}
        if (d) {
            ++cote;}

        std::cout << avance << " " << cote << std::endl;
    }

    return 0;
}
