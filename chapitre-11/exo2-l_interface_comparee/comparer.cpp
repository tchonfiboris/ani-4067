#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int nA = 0;
    if (!(std::cin >> nA)) {
        return 0;
    }

    std::vector<std::string> listA;
    listA.reserve(nA > 0 ? static_cast<std::size_t>(nA) : 0);
    std::unordered_set<std::string> setA;
    setA.reserve(static_cast<std::size_t>(nA) * 2 + 1);

    for (int i = 0; i < nA; ++i) {
        std::string name;
        if (std::cin >> name) {
            listA.push_back(name);
            setA.insert(name);
        }
    }

    int nB = 0;
    if (!(std::cin >> nB)) {
        nB = 0;
    }

    std::vector<std::string> listB;
    listB.reserve(nB > 0 ? static_cast<std::size_t>(nB) : 0);
    std::unordered_set<std::string> setB;
    setB.reserve(static_cast<std::size_t>(nB) * 2 + 1);

    for (int i = 0; i < nB; ++i) {
        std::string name;
        if (std::cin >> name) {
            listB.push_back(name);
            setB.insert(name);
        }
    }

    long long both_count = 0;
    std::unordered_set<std::string> seen_both;
    for (const std::string& name : listA) {
        if (setB.find(name) != setB.end() && seen_both.insert(name).second) {
            ++both_count;
        }
    }

    std::vector<std::string> onlyA;
    std::unordered_set<std::string> seen_onlyA;
    for (const std::string& name : listA) {
        if (setB.find(name) == setB.end() && seen_onlyA.insert(name).second) {
            onlyA.push_back(name);
        }
    }

    std::vector<std::string> onlyB;
    std::unordered_set<std::string> seen_onlyB;
    for (const std::string& name : listB) {
        if (setA.find(name) == setA.end() && seen_onlyB.insert(name).second) {
            onlyB.push_back(name);
        }
    }

    const long long diff_count = static_cast<long long>(onlyA.size() + onlyB.size());
    const long long union_count = both_count + diff_count;

    std::cout << "DEUX " << both_count << '\n';
    for (const std::string& name : onlyA) {
        std::cout << "SEUL_A " << name << '\n';
    }
    for (const std::string& name : onlyB) {
        std::cout << "SEUL_B " << name << '\n';
    }
    std::cout << "DIFFERENTES " << diff_count << " SUR " << union_count << '\n';

    return 0;
}