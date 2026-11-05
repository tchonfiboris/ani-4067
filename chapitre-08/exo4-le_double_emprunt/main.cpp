#include <iostream>
#include <string>

int main() {
    int n, N;
    unsigned long long v;
    if (!(std::cin >> n >> v >> N)) return 0;

    unsigned long long vars[26];
    for (int i = 0; i < 26; ++i) vars[i] = v;

    int prochaine = 0;
    bool emprunte = false;

    for (int i = 0; i < N; ++i) {
        std::string ordre;
        if (!(std::cin >> ordre)) break;

        if (ordre == "acquire") {
            std::string x;
            std::cin >> x;
            int k = x[0] - 'a';
            if (emprunte) {
                std::cout << "ACQUIRE FAUX " << x << " " << vars[k] << std::endl;
            } else {
                vars[k] = prochaine;
                emprunte = true;
                std::cout << "ACQUIRE VRAI " << x << " " << vars[k] << std::endl;
            }
        } else if (ordre == "release") {
            if (!emprunte) {
                std::cout << "RELEASE FAUX" << std::endl;
            } else {
                prochaine = (prochaine + 1) % n;
                emprunte = false;
                std::cout << "RELEASE VRAI" << std::endl;
            }
        } else if (ordre == "last") {
            std::cout << "LAST " << (prochaine + n - 1) % n << std::endl;
        }
    }

    std::cout << "EMPRUNTEE " << (emprunte ? "OUI" : "NON") << std::endl;
    std::cout << "PROCHAINE " << prochaine << std::endl;
    return 0;
}