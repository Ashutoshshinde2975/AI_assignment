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

bool forwardChaining(vector<Rule>& rules, unordered_set<string> facts, string goal) {
    bool addedNewFact = true;
    while (addedNewFact) {
        addedNewFact = false;
        for (auto &rule : rules) {
            bool allPremisesTrue = true;
            for (auto &p : rule.premises) {
                if (facts.find(p) == facts.end()) {
                    allPremisesTrue = false;
                    break;
                }
            }
            if (allPremisesTrue && facts.find(rule.conclusion) == facts.end()) {
                facts.insert(rule.conclusion);
                cout << "Derived new fact: " << rule.conclusion << "\n";
                addedNewFact = true;
                if (rule.conclusion == goal) return true;
            }
        }
    }
    return facts.find(goal) != facts.end();
}

int main() {
    vector<Rule> rules = {
        {{"A", "B"}, "C"},
        {{"C"}, "D"},
        {{"D"}, "E"}
    };

    unordered_set<string> facts = {"A", "B"}; // known facts
    string goal = "E";

    if (forwardChaining(rules, facts, goal))
        cout << "Goal " << goal << " is achievable!\n";
    else
        cout << "Goal " << goal << " cannot be derived.\n";

    return 0;
}