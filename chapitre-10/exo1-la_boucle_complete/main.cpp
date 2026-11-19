#include <iostream>
#include <string>

int main() {
    int T;
    if (!(std::cin >> T)) T = 0;
    int justes = 0, fautives = 0;

    for (int t = 1; t <= T; ++t) {
        int n;
        std::cin >> n;

        bool waited = false, begun = false, ended = false, viewed = false;
        bool borrowed[2] = {false, false};
        std::string code;
        int place = 0;

        for (int i = 1; i <= n; ++i) {
            std::string c;
            std::cin >> c;
            if (!code.empty()) continue;  // première faute déjà retenue : on ignore la suite

            std::string f;
            if (ended) {
                f = "APRES_END";
            } else if (c == "WAIT") {
                if (begun) f = "WAIT_APRES_BEGIN";
                else waited = true;
            } else if (c == "BEGIN") {
                if (begun) f = "DOUBLE_BEGIN";
                else if (!waited) f = "BEGIN_SANS_WAIT";
                else begun = true;
            } else if (c == "VUES") {
                if (!waited) f = "VUES_SANS_WAIT";
                else viewed = true;
            } else if (c == "PREND_G" || c == "PREND_D") {
                int x = (c == "PREND_G") ? 0 : 1;
                if (!begun) f = "PREND_SANS_BEGIN";
                else if (!viewed) f = "PREND_SANS_VUES";
                else if (borrowed[x]) f = "DOUBLE_PREND";
                else borrowed[x] = true;
            } else if (c == "LACHE_G" || c == "LACHE_D") {
                int x = (c == "LACHE_G") ? 0 : 1;
                if (!borrowed[x]) f = "LACHE_SANS_PREND";
                else borrowed[x] = false;
            } else if (c == "END") {
                if (!begun) f = "END_SANS_BEGIN";
                else if (borrowed[0] || borrowed[1]) f = "END_IMAGE_PRISE";
                else ended = true;
            }

            if (!f.empty()) {
                code = f;
                place = i;
            }
        }

        if (code.empty() && !ended) {
            code = "SANS_END";
            place = n + 1;
        }

        if (code.empty()) {
            std::cout << t << " OK" << std::endl;
            ++justes;
        } else {
            std::cout << t << " FAUTE " << place << " " << code << std::endl;
            ++fautives;
        }
    }

    std::cout << "JUSTES " << justes << std::endl;
    std::cout << "FAUTIVES " << fautives << std::endl;
    return 0;
}