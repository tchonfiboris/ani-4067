#include <iostream>
#include <string>

static std::string strip_cr(std::string s) {
    if (!s.empty() && s.back() == '\r') {
        s.pop_back();
    }
    return s;
}

static bool is_abs_path(const std::string& v) {
    if (v.empty()) {
        return false;
    }
    if (v[0] == '\\' || v[0] == '/') {
        return true;
    }
    if (v.size() >= 2 && v[1] == ':') {
        return true;
    }
    return false;
}

static std::string manifest_dir_prefix(const std::string& path) {
    std::size_t pos = path.find_last_of("\\/");
    if (pos == std::string::npos) {
        return path;
    }
    return path.substr(0, pos + 1);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int K = 0;
    if (!(std::cin >> K)) {
        return 0;
    }

    std::string line;
    std::getline(std::cin, line); // consomme la fin de la ligne de K

    for (int i = 1; i <= K; ++i) {
        std::string reg_path;
        if (!std::getline(std::cin, reg_path)) {
            break;
        }
        reg_path = strip_cr(reg_path);

        int L = 0;
        if (!(std::cin >> L)) {
            break;
        }
        std::getline(std::cin, line); // consomme la fin de la ligne de L

        std::string manifest_text;
        for (int r = 0; r < L; ++r) {
            std::string mline;
            std::getline(std::cin, mline);
            mline = strip_cr(mline);
            manifest_text += mline;
            manifest_text.push_back('\n');
        }

        if (reg_path == "-") {
            std::cout << i << " REGISTRE AUCUN\n";
            continue;
        }

        std::cout << i << " MANIFESTE " << reg_path << '\n';

        if (L == -1) {
            std::cout << i << " ECHEC ILLISIBLE\n";
            continue;
        }

        const std::string key = "\"library_path\"";
        std::size_t key_pos = manifest_text.find(key);
        if (key_pos == std::string::npos) {
            std::cout << i << " ECHEC CLE\n";
            continue;
        }

        std::size_t colon_pos = manifest_text.find(':', key_pos + key.size());
        if (colon_pos == std::string::npos) {
            std::cout << i << " ECHEC DEUX_POINTS\n";
            continue;
        }

        std::size_t q1 = manifest_text.find('"', colon_pos + 1);
        if (q1 == std::string::npos) {
            std::cout << i << " ECHEC GUILLEMET\n";
            continue;
        }

        std::size_t q2 = manifest_text.find('"', q1 + 1);
        if (q2 == std::string::npos) {
            std::cout << i << " ECHEC GUILLEMET\n";
            continue;
        }

        std::string raw_val = manifest_text.substr(q1 + 1, q2 - (q1 + 1));
        std::string val;
        val.reserve(raw_val.size());

        for (std::size_t idx = 0; idx < raw_val.size(); ++idx) {
            if (raw_val[idx] == '\\' && idx + 1 < raw_val.size() && raw_val[idx + 1] == '\\') {
                val.push_back('\\');
                ++idx;
            } else {
                val.push_back(raw_val[idx]);
            }
        }

        if (val.empty()) {
            std::cout << i << " ECHEC VIDE\n";
            continue;
        }

        std::cout << i << " VALEUR " << val << '\n';

        if (is_abs_path(val)) {
            std::cout << i << " ABSOLU\n";
            std::cout << i << " CHARGE " << val << '\n';
        } else {
            std::cout << i << " RELATIF\n";
            std::cout << i << " CHARGE " << manifest_dir_prefix(reg_path) << val << '\n';
        }
    }

    return 0;
}