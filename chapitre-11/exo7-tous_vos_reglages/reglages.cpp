#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

struct SettingInfo {
    std::string name;
    bool has_declare = false;
    bool has_ecrit = false;
    bool has_env = false;
    bool has_lit = false;
    bool has_getenv = false;
};

static std::string classify_setting(const SettingInfo& s) {
    if (s.has_getenv) {
        return "CACHE";
    }
    if (!s.has_lit) {
        return "FANTOME";
    }
    if (!s.has_ecrit && !s.has_env) {
        return "CONSTANTE";
    }
    return "MENU";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int R = 0;
    if (!(std::cin >> R)) {
        return 0;
    }

    std::vector<std::string> order;
    order.reserve(R > 0 ? static_cast<std::size_t>(R) : 0);

    std::unordered_map<std::string, SettingInfo> settings;
    settings.reserve(static_cast<std::size_t>(R) * 2 + 1);

    for (int i = 0; i < R; ++i) {
        std::string name, action;
        if (!(std::cin >> name >> action)) {
            break;
        }

        auto it = settings.find(name);
        if (it == settings.end()) {
            order.push_back(name);
            SettingInfo info;
            info.name = name;
            it = settings.emplace(name, info).first;
        }

        SettingInfo& info = it->second;
        if (action == "DECLARE") {
            info.has_declare = true;
        } else if (action == "ECRIT") {
            info.has_ecrit = true;
        } else if (action == "ENV") {
            info.has_env = true;
        } else if (action == "LIT") {
            info.has_lit = true;
        } else if (action == "GETENV") {
            info.has_getenv = true;
        }
    }

    long long menu_count = 0;
    const long long total_count = static_cast<long long>(order.size());

    for (const std::string& name : order) {
        const std::string cls = classify_setting(settings[name]);
        if (cls == "MENU") {
            ++menu_count;
        }
        std::cout << name << ' ' << cls << '\n';
    }

    std::cout << "MENU " << menu_count << " SUR " << total_count << '\n';

    return 0;
}