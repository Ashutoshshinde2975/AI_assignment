#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
using namespace std;

struct Rule {
    vector<string> premises;
    string conclusion;
};

bool backwardChaining(vector<Rule>& rules, unordered_set<string>& facts, string goal) {
    if (facts.find(goal) != facts.end()) return true;

    for (auto &rule : rules) {
        if (rule.conclusion == goal) {
            bool allPremisesSatisfied = true;
            for (auto &p : rule.premises) {
                if (!backwardChaining(rules, facts, p)) {
                    allPremisesSatisfied = false;
                    break;
                }
            }
            if (allPremisesSatisfied) {
                facts.insert(goal);
                cout << "Proved: " << goal << "\n";
                return true;
            }
        }
    }
    return false;
}

int main() {
    vector<Rule> rules = {
        {{"A", "B"}, "C"},
        {{"C"}, "D"},
        {{"D"}, "E"}
    };

    unordered_set<string> facts = {"A", "B"}; // known facts
    string goal = "E";

    if (backwardChaining(rules, facts, goal))
        cout << "Goal " << goal << " is provable!\n";
    else
        cout << "Goal " << goal << " cannot be proven.\n";

    return 0;
}