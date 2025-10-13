#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <utility>
#include <algorithm>

using namespace std;

const vector<vector<int>> goal_state = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 0}
};

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

bool is_goal(const vector<vector<int>> &state) {
    return state == goal_state;
}

pair<int, int> find_zero(const vector<vector<int>> &state) {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (state[i][j] == 0)
                return {i, j};
    return {-1, -1}; // should not happen
}

vector<vector<vector<int>>> generate_successors(const vector<vector<int>> &state) {
    pair<int, int> zero_pos = find_zero(state);
    int x = zero_pos.first;
    int y = zero_pos.second;
    vector<vector<vector<int>>> successors;

    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < 3 && ny >= 0 && ny < 3) {
            vector<vector<int>> new_state = state;
            swap(new_state[x][y], new_state[nx][ny]);
            successors.push_back(new_state);
        }
    }
    return successors;
}

string state_to_string(const vector<vector<int>> &state) {
    string s;
    for (const auto &row : state)
        for (int val : row)
            s += to_string(val);
    return s;
}

// ---- NEW: Solvability Check ----
bool is_solvable(const vector<vector<int>> &state) {
    vector<int> arr;
    for (auto &row : state)
        for (int val : row)
            if (val != 0) arr.push_back(val);

    int inv_count = 0;
    for (int i = 0; i < arr.size(); i++)
        for (int j = i + 1; j < arr.size(); j++)
            if (arr[i] > arr[j]) inv_count++;

    return (inv_count % 2 == 0); // solvable if inversions even
}

vector<vector<vector<int>>> bfs(const vector<vector<int>> &start_state) {
    set<string> visited; //track visited states
    queue<pair<vector<vector<int>>, vector<vector<vector<int>>>>> q; 
    q.push({start_state, {}});

    while (!q.empty()) {
        vector<vector<int>> current = q.front().first;
        vector<vector<vector<int>>> path = q.front().second;
        q.pop();

        if (is_goal(current)) {
            path.push_back(current);
            return path;
        }

        visited.insert(state_to_string(current));
        for (auto &succ : generate_successors(current)) {
            string s = state_to_string(succ);
            if (visited.find(s) == visited.end()) {
                vector<vector<vector<int>>> new_path = path;
                new_path.push_back(current);
                q.push({succ, new_path});
            }
        }
    }
    return {};
}

vector<vector<vector<int>>> dfs(const vector<vector<int>> &start_state, int depth_limit = 20) {
    set<string> visited;
    stack<pair<vector<vector<int>>, vector<vector<vector<int>>>>> st;
    st.push({start_state, {}});

    while (!st.empty()) {
        auto top_pair = st.top();
        st.pop();

        vector<vector<int>> current = top_pair.first;
        vector<vector<vector<int>>> path = top_pair.second;

        if (is_goal(current)) {
            path.push_back(current);
            return path;
        }

        if (path.size() >= depth_limit)
            continue;

        visited.insert(state_to_string(current));
        for (auto &succ : generate_successors(current)) {
            string s = state_to_string(succ);
            if (visited.find(s) == visited.end()) {
                vector<vector<vector<int>>> new_path = path;
                new_path.push_back(current);
                st.push({succ, new_path});
            }
        }
    }
    return {};
}

void print_solution(const vector<vector<vector<int>>> &path) {
    if (path.empty()) {
        cout << "No solution found.\n";
        return;
    }
    for (size_t step = 0; step < path.size(); ++step) {
        cout << "\nStep " << step << ":\n";
        for (const auto &row : path[step]) {
            for (int val : row)
                cout << val << " ";
            cout << '\n';
        }
    }
}

int main() {
    vector<vector<int>> start_state(3, vector<int>(3));
    cout << "Enter the 3x3 start state (use 0 for blank):\n";
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            cin >> start_state[i][j];

    // ---- Solvability Check ----
    if (!is_solvable(start_state)) {
        cout << "This puzzle configuration is unsolvable.\n";
        return 0;
    }

    cout << "\nBFS Solution:";
    print_solution(bfs(start_state));

    cout << "\nDFS Solution:";
    print_solution(dfs(start_state));

    return 0;
}
