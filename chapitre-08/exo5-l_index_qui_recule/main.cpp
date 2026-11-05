#include <cstdint>
#include <iostream>

int main() {
    int N;
    if (!(std::cin >> N)) N = 0;

    long long refusees = 0, fauxSigne = 0, fauxNonSigne = 0;

    for (int i = 0; i < N; ++i) {
        long long n, r;
        if (!(std::cin >> n >> r)) break;

        if (n == 0 || n > 4) {
            std::cout << n << " " << r << " REFUSEE" << std::endl;
            ++refusees;
            continue;
        }

        int nn = (int)n;
        long long prochaine = r % n; // 64 bits
        int p = (int)prochaine;

        int juste = (p + nn - 1) % nn;
        int signe = (p - 1) % nn;
        std::uint32_t up = (std::uint32_t)prochaine;
        std::uint32_t nonsigne = (up - 1u) % (std::uint32_t)nn;

        if (signe != juste) ++fauxSigne;
        if (nonsigne != (std::uint32_t)juste) ++fauxNonSigne;

        std::cout << n << " " << r << " " << prochaine << " " << juste << " "
                  << signe << " " << nonsigne << std::endl;
    }

    std::cout << "REFUSEES " << refusees << std::endl;
    std::cout << "FAUX SIGNE " << fauxSigne << std::endl;
    std::cout << "FAUX NON SIGNE " << fauxNonSigne << std::endl;
    return 0;
}