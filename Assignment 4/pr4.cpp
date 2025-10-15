#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

struct Node {
    int x, y, g, f;
};

struct Compare {
    bool operator()(Node a, Node b) {
        return a.f > b.f; // min-heap
    }
};

int manhattan(int x, int y, int gx, int gy) {
    return abs(x - gx) + abs(y - gy);
}

bool isValid(int x, int y, vector<vector<int>>& grid) {
    int n = grid.size(), m = grid[0].size();
    return x >= 0 && x < n && y >= 0 && y < m && grid[x][y] == 0;
}

bool aStar(vector<vector<int>>& grid, pair<int,int> start, pair<int,int> goal) {
    priority_queue<Node, vector<Node>, Compare> pq;
    pq.push({start.first, start.second, 0, manhattan(start.first, start.second, goal.first, goal.second)});

    vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    while(!pq.empty()) {
        Node cur = pq.top(); pq.pop();
        if (visited[cur.x][cur.y]) continue;
        visited[cur.x][cur.y] = true;

        if (cur.x == goal.first && cur.y == goal.second) {
            cout << "Goal reached at (" << cur.x << "," << cur.y << ") with cost = " << cur.g << "\n";
            return true;
        }

        for(int i=0;i<4;i++) {
            int nx = cur.x + dx[i], ny = cur.y + dy[i];
            if (isValid(nx, ny, grid) && !visited[nx][ny]) {
                int g = cur.g + 1;
                int f = g + manhattan(nx, ny, goal.first, goal.second);
                pq.push({nx, ny, g, f});
            }
        }
    }
    cout << "No path found!\n";
    return false;
}

int main() {
    vector<vector<int>> grid = {
        {0,0,0,0,0},
        {1,1,1,1,0},
        {0,0,0,0,0},
        {0,1,1,1,1},
        {0,0,0,0,0}
    };

    pair<int,int> start = {0,0};
    pair<int,int> goal = {4,4};

    aStar(grid, start, goal);
    return 0;
}

        // {0,0,0,0,0},
        // {0,1,1,1,0},
        // {0,0,0,1,0},
        // {1,0,0,0,0},
        // {0,0,1,0,0}
