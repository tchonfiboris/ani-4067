#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>

struct ProjectFile {
    std::string name;
    std::vector<std::string> includes;
};

static bool ends_with_cpp(const std::string& name) {
    return name.size() >= 4 && name.compare(name.size() - 4, 4, ".cpp") == 0;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t E = 0;
    if (!(std::cin >> E)) {
        return 0;
    }

    std::unordered_set<std::string> external_headers;
    external_headers.reserve(E);
    for (std::size_t i = 0; i < E; ++i) {
        std::string ext;
        std::cin >> ext;
        external_headers.insert(ext);
    }

    std::size_t F = 0;
    if (!(std::cin >> F)) {
        return 0;
    }

    std::vector<ProjectFile> files;
    files.reserve(F);
    std::unordered_map<std::string, std::size_t> file_index;
    file_index.reserve(F);

    for (std::size_t i = 0; i < F; ++i) {
        ProjectFile pf;
        std::size_t k = 0;
        std::cin >> pf.name >> k;
        pf.includes.reserve(k);
        for (std::size_t j = 0; j < k; ++j) {
            std::string inc;
            std::cin >> inc;
            pf.includes.push_back(inc);
        }
        file_index[pf.name] = files.size();
        files.push_back(std::move(pf));
    }

    std::size_t touched = 0;
    std::size_t units = 0;

    for (const auto& file : files) {
        if (!ends_with_cpp(file.name)) {
            continue;
        }
        ++units;

        std::queue<std::string> q;
        std::unordered_set<std::string> visited;
        std::unordered_map<std::string, std::string> parent;

        visited.insert(file.name);
        q.push(file.name);

        bool found = false;
        std::string reached_external;

        while (!q.empty() && !found) {
            std::string curr = q.front();
            q.pop();

            auto it = file_index.find(curr);
            if (it == file_index.end()) {
                continue;
            }

            const auto& curr_includes = files[it->second].includes;
            for (const auto& inc : curr_includes) {
                if (visited.count(inc)) {
                    continue;
                }
                visited.insert(inc);
                parent[inc] = curr;

                if (external_headers.count(inc)) {
                    found = true;
                    reached_external = inc;
                    break;
                }

                if (file_index.count(inc)) {
                    q.push(inc);
                }
            }
        }

        if (found) {
            ++touched;
            std::vector<std::string> path;
            for (std::string cur = reached_external; ; cur = parent[cur]) {
                path.push_back(cur);
                if (cur == file.name) {
                    break;
                }
            }

            std::cout << file.name << " OUI ";
            for (std::size_t idx = path.size(); idx > 0; --idx) {
                std::cout << path[idx - 1];
                if (idx > 1) {
                    std::cout << '>';
                }
            }
            std::cout << '\n';
        } else {
            std::cout << file.name << " NON\n";
        }
    }

    std::cout << "TOUCHEES " << touched << " SUR " << units << '\n';
    return 0;
}