#include <iostream>
#include <string>

int main() {
    int n;
    std::cin >> n;

    // accumulateur
    long long dx = 0; 
    long long dy = 0;
    // moteur défectueux   
    long long bx = 0; 
    long long by = 0;   

    for (int i = 0; i < n; ++i) {
        std::string mot;
        std::cin >> mot;

        if (mot == "bouge") {
            long long x; 
            long long y;
            std::cin >> x; 
            std::cin >> y;
            dx = dx + x;
            dy = dy + y;
            bx = x;
            by = y;
        } else if (mot == "image") {
            std::cout << dx << " " << dy << " " << bx << " " << by << std::endl;
            dx = 0;
            dy = 0;
        }
    }

    return 0;
}
