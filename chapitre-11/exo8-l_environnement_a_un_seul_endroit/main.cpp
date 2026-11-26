#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

static std::string strip_cr(std::string s) {
    if (!s.empty() && s.back() == '\r') {
        s.pop_back();
    }
    return s;
}

static bool is_digit_char(char c) {
    return c >= '0' && c <= '9';
}

static bool is_space_char(char c) {
    return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}

// Lit un entier selon la regle 4 :
// saute les espaces du debut, lit + ou - facultatif, puis les chiffres.
// S'arrete au premier autre signe. Retourne 0 sans chiffre.
static long long parse_int_prefix(const std::string& s, std::size_t& pos) {
    while (pos < s.size() && is_space_char(s[pos])) {
        ++pos;
    }

    int sign = 1;
    if (pos < s.size() && (s[pos] == '+' || s[pos] == '-')) {
        if (s[pos] == '-') {
            sign = -1;
        }
        ++pos;
    }

    bool has_digit = false;
    long long value = 0;
    while (pos < s.size() && is_digit_char(s[pos])) {
        has_digit = true;
        value = value * 10 + (s[pos] - '0');
        ++pos;
    }

    while (pos < s.size() && !is_space_char(s[pos]) && s[pos] != ',') {
        ++pos;
    }

    if (!has_digit) {
        return 0;
    }
    return sign * value;
}

// Tente de lire un entier pour NK_XR_SIM_POSE en indiquant si au moins un chiffre a ete lu.
static bool try_parse_pose_int(const std::string& s, std::size_t& pos, long long& out) {
    while (pos < s.size() && is_space_char(s[pos])) {
        ++pos;
    }

    int sign = 1;
    if (pos < s.size() && (s[pos] == '+' || s[pos] == '-')) {
        if (s[pos] == '-') {
            sign = -1;
        }
        ++pos;
    }

    bool has_digit = false;
    long long value = 0;
    while (pos < s.size() && is_digit_char(s[pos])) {
        has_digit = true;
        value = value * 10 + (s[pos] - '0');
        ++pos;
    }

    if (!has_digit) {
        return false;
    }

    out = sign * value;
    return true;
}

static std::string parse_switch(const std::string& val) {
    if ((!val.empty() && val[0] == '0') || val == "false") {
        return "NON";
    }
    return "OUI";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string line;
    if (!std::getline(std::cin, line)) {
        return 0;
    }
    line = strip_cr(line);

    std::string backend = "SIMULATEUR";
    long long hz = 0;
    std::string demi = "NON";
    std::string profondeur = "NON";
    std::string liste = "NON";
    long long latence = 0;

    {
        std::istringstream iss(line);
        iss >> backend >> hz >> demi >> profondeur >> liste >> latence;
    }

    std::string loader = "-";
    if (std::getline(std::cin, loader)) {
        loader = strip_cr(loader);
    }

    std::string pose_mode = "LIBRE";
    long long pose_vals[5] = {0, 0, 0, 0, 0};
    if (std::getline(std::cin, line)) {
        line = strip_cr(line);
        std::istringstream piss(line);
        piss >> pose_mode;
        if (pose_mode == "FIXE") {
            for (int k = 0; k < 5; ++k) {
                piss >> pose_vals[k];
            }
        } else {
            pose_mode = "LIBRE";
        }
    }

    int M = 0;
    if (!(std::cin >> M)) {
        M = 0;
    }
    std::getline(std::cin, line); // consomme la fin de ligne de M

    int applied = 0;
    int ignored = 0;

    for (int i = 0; i < M; ++i) {
        std::string entry;
        if (!std::getline(std::cin, entry)) {
            break;
        }
        entry = strip_cr(entry);

        std::size_t eq_pos = entry.find('=');
        if (eq_pos == std::string::npos) {
            ++ignored;
            continue;
        }

        std::string name = entry.substr(0, eq_pos);
        std::string val = entry.substr(eq_pos + 1);

        if (val.empty()) {
            ++ignored;
            continue;
        }

        if (name == "NK_XR_BACKEND") {
            if (val == "openxr") {
                backend = "OPENXR";
                ++applied;
            } else {
                ++ignored;
            }
        } else if (name == "NK_XR_HZ") {
            std::size_t p = 0;
            hz = parse_int_prefix(val, p);
            ++applied;
        } else if (name == "NK_XR_HALF_RATE") {
            demi = parse_switch(val);
            ++applied;
        } else if (name == "NK_XR_DEPTH_LAYER") {
            profondeur = parse_switch(val);
            ++applied;
        } else if (name == "NK_XR_LIST_EXT") {
            liste = parse_switch(val);
            ++applied;
        } else if (name == "NK_XR_OPENXR_LOADER") {
            loader = val;
            ++applied;
        } else if (name == "NK_XR_SIM_LATENCY_MS") {
            std::size_t p = 0;
            latence = parse_int_prefix(val, p);
            ++applied;
        } else if (name == "NK_XR_SIM_POSE") {
            std::size_t p = 0;
            long long tmp[5] = {0, 0, 0, 0, 0};
            int count = 0;
            while (count < 5) {
                long long num = 0;
                if (!try_parse_pose_int(val, p, num)) {
                    break;
                }
                tmp[count] = num;
                ++count;

                while (p < val.size() && (val[p] == ',' || is_space_char(val[p]))) {
                    ++p;
                }
                if (p >= val.size()) {
                    break;
                }
            }

            if (count == 5) {
                pose_mode = "FIXE";
                for (int k = 0; k < 5; ++k) {
                    pose_vals[k] = tmp[k];
                }
                ++applied;
            } else {
                ++ignored;
            }
        } else {
            ++ignored;
        }
    }

    std::cout << "BACKEND " << backend << '\n';
    std::cout << "HZ " << hz << '\n';
    std::cout << "DEMI " << demi << '\n';
    std::cout << "PROFONDEUR " << profondeur << '\n';
    std::cout << "LISTE " << liste << '\n';
    std::cout << "LOADER " << loader << '\n';
    std::cout << "LATENCE " << latence << '\n';

    if (pose_mode == "FIXE") {
        std::cout << "POSE FIXE";
        for (int k = 0; k < 5; ++k) {
            std::cout << ' ' << pose_vals[k];
        }
        std::cout << '\n';
    } else {
        std::cout << "POSE LIBRE\n";
    }

    std::cout << "APPLIQUEES " << applied << '\n';
    std::cout << "IGNOREES " << ignored << '\n';

    return 0;
}