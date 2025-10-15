#include <bits/stdc++.h>
using namespace std;

class FamilyTree {
    // Knowledge base
    vector<pair<string,string>> parents;   // (parent, child)
    unordered_set<string> male;
    unordered_set<string> female;

public:
    // Add facts
    void addParent(string p, string c) {
        parents.push_back({p,c});
    }
    void addMale(string name) { male.insert(name); }
    void addFemale(string name) { female.insert(name); }

    // Derived rules
    bool isParent(string p, string c) {
        for (auto &pc : parents)
            if (pc.first == p && pc.second == c) return true;
        return false;
    }

    bool isFather(string p, string c) {
        return isParent(p,c) && male.count(p);
    }

    bool isMother(string p, string c) {
        return isParent(p,c) && female.count(p);
    }

    vector<string> children(string p) {
        vector<string> res;
        for (auto &pc : parents)
            if (pc.first == p) res.push_back(pc.second);
        return res;
    }

    vector<string> siblings(string x) {
        vector<string> sibs;
        for (auto &p1 : parents) {
            if (p1.second == x) {
                for (auto &p2 : parents) {
                    if (p1.first == p2.first && p2.second != x)
                        sibs.push_back(p2.second);
                }
            }
        }
        sort(sibs.begin(), sibs.end());
        sibs.erase(unique(sibs.begin(), sibs.end()), sibs.end());
        return sibs;
    }

    vector<string> grandparents(string x) {
        vector<string> gp;
        for (auto &pc : parents) {
            if (pc.second == x) {
                string parent = pc.first;
                for (auto &pg : parents) {
                    if (pg.second == parent) gp.push_back(pg.first);
                }
            }
        }
        sort(gp.begin(), gp.end());
        gp.erase(unique(gp.begin(), gp.end()), gp.end());
        return gp;
    }
};

int main() {
    FamilyTree ft;

    // Facts
    ft.addParent("John", "Alice");
    ft.addParent("John", "Bob");
    ft.addParent("Mary", "Alice");
    ft.addParent("Mary", "Bob");
    ft.addParent("Alice", "Charlie");
    ft.addParent("Alice", "Diana");
    ft.addParent("Peter", "Charlie");
    ft.addParent("Peter", "Diana");

    ft.addMale("John");
    ft.addMale("Bob");
    ft.addMale("Peter");
    ft.addMale("Charlie");
    ft.addFemale("Mary");
    ft.addFemale("Alice");
    ft.addFemale("Diana");

    // Queries
    cout << "Father of Alice: ";
    if (ft.isFather("John","Alice")) cout << "John\n";

    cout << "Mother of Bob: ";
    if (ft.isMother("Mary","Bob")) cout << "Mary\n";

    cout << "Siblings of Charlie: ";
    for (auto &s : ft.siblings("Charlie")) cout << s << " ";
    cout << "\n";

    cout << "Grandparents of Diana: ";
    for (auto &g : ft.grandparents("Diana")) cout << g << " ";
    cout << "\n";

    return 0;
}