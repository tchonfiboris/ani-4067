#include <cctype>
#include <iostream>
#include <string>
#include <vector>

static std::string strip_cr(std::string s) {
    if (!s.empty() && s.back() == '\r') {
        s.pop_back();
    }
    return s;
}

static bool is_ident_char(char c) {
    unsigned char uc = static_cast<unsigned char>(c);
    return std::isalnum(uc) != 0 || c == '_';
}

static bool is_comment_line(const std::string& text) {
    std::size_t pos = 0;
    while (pos < text.size() && (text[pos] == ' ' || text[pos] == '\t')) {
        ++pos;
    }
    return pos + 1 < text.size() && text[pos] == '/' && text[pos + 1] == '/';
}

static bool contains_exact_name(const std::string& text, const std::string& name) {
    if (name.empty() || text.size() < name.size()) {
        return false;
    }
    std::size_t pos = 0;
    while ((pos = text.find(name, pos)) != std::string::npos) {
        bool left_ok = (pos == 0) || !is_ident_char(text[pos - 1]);
        std::size_t end_pos = pos + name.size();
        bool right_ok = (end_pos == text.size()) || !is_ident_char(text[end_pos]);
        if (left_ok && right_ok) {
            return true;
        }
        pos += 1;
    }
    return false;
}

static bool contains_any_name(const std::string& text, const std::vector<std::string>& names) {
    for (const std::string& name : names) {
        if (contains_exact_name(text, name)) {
            return true;
        }
    }
    return false;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string token;
    int k = 0;
    if (!(std::cin >> token >> k)) {
        return 0;
    }
    std::vector<std::string> c_names;
    c_names.reserve(k);
    for (int i = 0; i < k; ++i) {
        std::string s;
        std::cin >> s;
        c_names.push_back(s);
    }

    int m = 0;
    if (!(std::cin >> token >> m)) {
        return 0;
    }
    std::vector<std::string> d_names;
    d_names.reserve(m);
    for (int i = 0; i < m; ++i) {
        std::string s;
        std::cin >> s;
        d_names.push_back(s);
    }

    int N = 0;
    if (!(std::cin >> N)) {
        return 0;
    }

    std::string dummy;
    std::getline(std::cin, dummy); // consomme la fin de la ligne N

    int decisions = 0;
    int fuites = 0;
    int definis = 0;

    for (int line_no = 1; line_no <= N; ++line_no) {
        std::string raw_line;
        if (!std::getline(std::cin, raw_line)) {
            break;
        }
        raw_line = strip_cr(raw_line);

        std::size_t space_pos = raw_line.find(' ');
        std::string zone;
        std::string text;
        if (space_pos == std::string::npos) {
            zone = raw_line;
            text.clear();
        } else {
            zone = raw_line.substr(0, space_pos);
            text = raw_line.substr(space_pos + 1);
        }

        if (is_comment_line(text)) {
            continue;
        }

        bool has_c = contains_any_name(text, c_names);
        bool has_d = contains_any_name(text, d_names);

        bool line_has_fuite = false;
        bool line_has_defini = false;

        if (has_c) {
            if (zone == "INIT") {
                ++decisions;
            } else if (zone == "BOUCLE" || zone == "SCENE") {
                line_has_fuite = true;
            }
            // En FABRIQUE : autorisé, ni décision ni fuite
        }

        if (has_d && zone != "FABRIQUE") {
            line_has_defini = true;
        }

        if (line_has_fuite) {
            std::cout << "FUITE " << line_no << ' ' << zone << '\n';
            ++fuites;
        }
        if (line_has_defini) {
            std::cout << "DEFINI " << line_no << ' ' << zone << '\n';
            ++definis;
        }
    }

    std::cout << "DECISIONS " << decisions << '\n';
    std::cout << "FUITES " << fuites << '\n';
    std::cout << "DEFINIS " << definis << '\n';
    if (fuites == 0 && definis == 0) {
        std::cout << "ABSTRACTION TENUE\n";
    } else {
        std::cout << "ABSTRACTION FUIT\n";
    }

    return 0;
}