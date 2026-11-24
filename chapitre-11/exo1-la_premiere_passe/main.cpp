#include <iostream>
#include <string>
#include <vector>

static bool is_var_char(char c) {
    return (c >= 'A' && c <= 'Z') ||
           (c >= '0' && c <= '9') ||
           (c == '_');
}

static bool is_ident_char(char c) {
    return (c >= 'A' && c <= 'Z') ||
           (c >= 'a' && c <= 'z') ||
           (c >= '0' && c <= '9') ||
           (c == '_');
}

static bool already_seen(const std::vector<std::string>& vars, const std::string& name) {
    for (const std::string& v : vars) {
        if (v == name) {
            return true;
        }
    }
    return false;
}

static void extract_vars_from_line(const std::string& line, std::vector<std::string>& vars) {
    std::size_t pos = 0;
    while ((pos = line.find("NK_", pos)) != std::string::npos) {
        if (pos > 0 && is_ident_char(line[pos - 1])) {
            pos += 3;
            continue;
        }

        std::size_t cursor = pos + 3;
        while (cursor < line.size() && is_var_char(line[cursor])) {
            ++cursor;
        }

        // Au moins un caractere apres "NK_" et suivi immediatement de '='
        if (cursor > pos + 3 && cursor < line.size() && line[cursor] == '=') {
            std::string name = line.substr(pos, cursor - pos);
            if (!already_seen(vars, name)) {
                vars.push_back(name);
            }
            pos = cursor + 1;
        } else {
            pos += 3;
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n = 0;
    if (!(std::cin >> n)) {
        return 0;
    }

    std::string dummy;
    std::getline(std::cin, dummy); // consomme la fin de la ligne contenant N

    std::vector<std::string> lines;
    lines.reserve(n);
    for (std::size_t idx = 0; idx < n; ++idx) {
        std::string line;
        std::getline(std::cin, line);
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        lines.push_back(line);
    }

    std::size_t header_count = 0;
    bool in_header = true;
    std::vector<std::string> variables;

    for (std::size_t idx = 0; idx < n; ++idx) {
        if (!in_header) {
            break;
        }

        const std::string& line = lines[idx];
        std::size_t first_non_ws = 0;
        while (first_non_ws < line.size() &&
               (line[first_non_ws] == ' ' || line[first_non_ws] == '\t')) {
            ++first_non_ws;
        }

        if (first_non_ws + 1 < line.size() &&
            line[first_non_ws] == '/' &&
            line[first_non_ws + 1] == '/') {
            ++header_count;
            extract_vars_from_line(line, variables);
        } else {
            in_header = false;
        }
    }

    std::size_t ignored_count = n - header_count;
    std::size_t part = (n == 0) ? 0 : (100 * header_count) / n;

    std::cout << "ENTETE " << header_count << '\n';
    std::cout << "IGNOREES " << ignored_count << '\n';

    if (variables.empty()) {
        std::cout << "VARIABLE AUCUNE\n";
    } else {
        for (const std::string& var : variables) {
            std::cout << "VARIABLE " << var << '\n';
        }
    }

    std::cout << "PART " << part << '\n';
    return 0;
}