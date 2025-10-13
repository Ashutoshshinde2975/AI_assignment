//Perform parsing of family tree using knowledge-base
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <regex>
#include <algorithm>

struct Person {
    std::string name;
    std::string gender;  // "male" or "female" (unknown allowed)
    std::vector<Person*> parents;
    std::vector<Person*> children;

    Person(const std::string& n, const std::string& g) : name(n), gender(g) {}
};

class KnowledgeBaseFamilyTree {
private:
    std::unordered_map<std::string, Person*> people;

public:
    ~KnowledgeBaseFamilyTree() {
        for (auto& pair : people) {
            delete pair.second;
        }
    }

    void addPerson(const std::string& name, const std::string& gender) {
        if (people.find(name) == people.end()) {
            people[name] = new Person(name, gender);
        }   
    }

    void addFact(const std::string& relation, const std::string& parent, const std::string& child) {
        std::string gender = (relation == "father") ? "male" : "female";
        addPerson(parent, gender);
        addPerson(child, "unknown");  // gender may be unknown initially

        Person* p = people[parent];
        Person* c = people[child];
        p->children.push_back(c);
        c->parents.push_back(p);
    }

    std::vector<std::string> getParents(const std::string& name) {
        std::vector<std::string> result;
        if (people.find(name) != people.end()) {
            for (auto& p : people[name]->parents) {
                result.push_back(p->name);
            }
        }
        return result;
    }

    std::vector<std::string> getFather(const std::string& name) {
        std::vector<std::string> fathers;
        if (people.find(name) != people.end()) {
            for (auto& p : people[name]->parents) {
                if (p->gender == "male") {
                    fathers.push_back(p->name);
                }
            }
        }
        return fathers;
    }

    std::vector<std::string> getMother(const std::string& name) {
        std::vector<std::string> mothers;
        if (people.find(name) != people.end()) {
            for (auto& p : people[name]->parents) {
                if (p->gender == "female") {
                    mothers.push_back(p->name);
                }
            }
        }
        return mothers;
    }

    std::vector<std::string> getGrandmother(const std::string& name) {
        std::unordered_set<std::string> grandmothers;
        auto parents = getParents(name);
        for (const auto& parent : parents) {
            auto gps = getParents(parent);
            for (const auto& gp : gps) {
                if (people[gp]->gender == "female") {
                    grandmothers.insert(gp);
                }
            }
        }
        return {grandmothers.begin(), grandmothers.end()};
    }

    std::vector<std::string> getSiblings(const std::string& name) {
        std::unordered_set<std::string> siblings;
        if (people.find(name) != people.end()) {
            for (auto& parent : people[name]->parents) {
                for (auto& child : parent->children) {
                    if (child->name != name) {
                        siblings.insert(child->name);
                    }
                }
            }
        }
        return {siblings.begin(), siblings.end()};
    }

    void displayResults(const std::string& relationship, const std::string& person,
                        const std::vector<std::string>& results) {
        std::cout << "\n" << relationship << " of " << person << "\n";
        if (results.empty()) {
            std::cout << "| No " << relationship << " found                          |\n";
        } else {
            for (const auto& res : results) {
                std::cout << "| " << res 
                          << std::string(50 - res.length(), ' ') << "|\n";
            }
        }
    }

    // Parse facts like "father(John, Bob)." or "mother(Mary, Bob)."
    void parseFact(const std::string& fact) {
        std::regex pattern(R"((father|mother)\((\w+),\s*(\w+)\)\.)");
        std::smatch match;
        if (std::regex_match(fact, match, pattern)) {
            std::string relation = match[1];
            std::string parent = match[2];
            std::string child = match[3];
            addFact(relation, parent, child);
        }
    }
};

int main() {
    KnowledgeBaseFamilyTree tree;

    // Knowledge base facts
    std::vector<std::string> facts = {
        "father(John, Bob).",
        "mother(Mary, Bob).",
        "father(Bob, Kate).",
        "mother(Alice, Kate).",
        "father(Bob, Frank).",
        "mother(Alice, Frank).",
        "father(John, Anna).",
        "mother(Mary, Anna)."
    };

    for (const auto& f : facts) {
        tree.parseFact(f);
    }

    int choice;
    std::string person;

    while (true) {
        std::cout << "\n====== Family Tree Knowledge-Base Query ======\n";
        std::cout << "1. Find Father\n";
        std::cout << "2. Find Mother\n";
        std::cout << "3. Find Grandmother\n";
        std::cout << "4. Find Siblings\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 5) {
            std::cout << "Exiting program...\n";
            break;
        }

        std::cout << "Enter person's name: ";
        std::getline(std::cin, person);

        std::transform(person.begin(), person.end(), person.begin(), ::tolower);
        if (!person.empty()) person[0] = std::toupper(person[0]);

        if (choice == 1) {
            auto results = tree.getFather(person);
            tree.displayResults("Father", person, results);
        } 
        else if (choice == 2) {
            auto results = tree.getMother(person);
            tree.displayResults("Mother", person, results);
        } 
        else if (choice == 3) {
            auto results = tree.getGrandmother(person);
            tree.displayResults("Grandmother", person, results);
        }
        else if (choice == 4) {
            auto results = tree.getSiblings(person);
            tree.displayResults("Siblings", person, results);
        } 
        else {
            std::cout << "Invalid choice!\n";
        }
    }

    return 0;
}
