// //To Implement A* Algorithm for an application. 
// #include <bits/stdc++.h>
// using namespace std;

// struct Cell {
//     int parent_i;
//     int parent_j;
//     double f;
//     double g;
//     double h;
//     Cell() {
//         parent_i = -1;
//         parent_j = -1;
//         f = std::numeric_limits<double>::infinity();
//         g = std::numeric_limits<double>::infinity();
//         h = 0.0;
//     }
// };

// const int ROW = 9;
// const int COL = 10;

// bool is_valid(int row, int col) {
//     return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL);
// }

// bool is_unblocked(const std::vector<std::vector<int>>& grid, int row, int col) {
//     return grid[row][col] == 1;
// }

// bool is_destination(int row, int col, const std::pair<int,int>& dest) {
//     return row == dest.first && col == dest.second;
// }

// double calculate_h_value(int row, int col, const std::pair<int,int>& dest) {
//     return std::sqrt((row - dest.first)*(row - dest.first) + (col - dest.second)*(col - dest.second));
// }

// void trace_path(const std::vector<std::vector<Cell>>& cell_details, const std::pair<int,int>& dest) {
//     std::cout << "The Path is\n";
//     std::vector<std::pair<int,int>> path;
//     int row = dest.first;
//     int col = dest.second;

//     while (!(cell_details[row][col].parent_i == row && cell_details[row][col].parent_j == col)) {
//         path.emplace_back(row, col);
//         int temp_row = cell_details[row][col].parent_i;
//         int temp_col = cell_details[row][col].parent_j;
//         row = temp_row;
//         col = temp_col;
//     }
//     path.emplace_back(row, col);
//     std::reverse(path.begin(), path.end());

//     for (auto &p : path) {
//         std::cout << "-> (" << p.first << "," << p.second << ") ";
//     }
//     std::cout << std::endl;
// }

// void a_star_search(const std::vector<std::vector<int>>& grid,
//                    const std::pair<int,int>& src,
//                    const std::pair<int,int>& dest) {
//     if (!is_valid(src.first, src.second) || !is_valid(dest.first, dest.second)) {
//         std::cout << "Source or destination is invalid\n";
//         return;
//     }

//     if (!is_unblocked(grid, src.first, src.second) || !is_unblocked(grid, dest.first, dest.second)) {
//         std::cout << "Source or the destination is blocked\n";
//         return;
//     }

//     if (is_destination(src.first, src.second, dest)) {
//         std::cout << "We are already at the destination\n";
//         return;
//     }

//     std::vector<std::vector<bool>> closed_list(ROW, std::vector<bool>(COL, false));
//     std::vector<std::vector<Cell>> cell_details(ROW, std::vector<Cell>(COL));

//     int i = src.first;
//     int j = src.second;
//     cell_details[i][j].f = 0.0;
//     cell_details[i][j].g = 0.0;
//     cell_details[i][j].h = 0.0;
//     cell_details[i][j].parent_i = i;
//     cell_details[i][j].parent_j = j;

//     // min-heap: tuple(f, row, col)
//     using T = std::tuple<double,int,int>;
//     std::priority_queue<T, std::vector<T>, std::greater<T>> open_list;
//     open_list.push(std::make_tuple(0.0, i, j));

//     bool found_dest = false;

//     const std::vector<std::pair<int,int>> directions = {
//         {0,1}, {0,-1}, {1,0}, {-1,0},
//         {1,1}, {1,-1}, {-1,1}, {-1,-1}
//     };

//     while (!open_list.empty()) {
//         auto p = open_list.top();
//         open_list.pop();

//         i = std::get<1>(p);
//         j = std::get<2>(p);
//         closed_list[i][j] = true;

//         for (auto &dir : directions) {
//             int new_i = i + dir.first;
//             int new_j = j + dir.second;

//             if (is_valid(new_i, new_j) && is_unblocked(grid, new_i, new_j) && !closed_list[new_i][new_j]) {
//                 if (is_destination(new_i, new_j, dest)) {
//                     cell_details[new_i][new_j].parent_i = i;
//                     cell_details[new_i][new_j].parent_j = j;
//                     std::cout << "The destination cell is found\n";
//                     trace_path(cell_details, dest);
//                     found_dest = true;
//                     return;
//                 } else {
//                     double g_new = cell_details[i][j].g + 1.0; // same as Python: uniform cost for every move
//                     double h_new = calculate_h_value(new_i, new_j, dest);
//                     double f_new = g_new + h_new;

//                     if (cell_details[new_i][new_j].f == std::numeric_limits<double>::infinity() ||
//                         cell_details[new_i][new_j].f > f_new) {
//                         open_list.push(std::make_tuple(f_new, new_i, new_j));
//                         cell_details[new_i][new_j].f = f_new;
//                         cell_details[new_i][new_j].g = g_new;
//                         cell_details[new_i][new_j].h = h_new;
//                         cell_details[new_i][new_j].parent_i = i;
//                         cell_details[new_i][new_j].parent_j = j;
//                     }
//                 }
//             }
//         }
//     }

//     if (!found_dest) {
//         std::cout << "Failed to find the destination cell\n";
//     }
// }

// int main() {
//     std::vector<std::vector<int>> grid = {
//         {1,0,1,1,1,1,0,1,1,1},
//         {1,1,1,0,1,1,1,0,1,1},
//         {1,1,1,0,1,1,0,1,0,1},
//         {0,0,1,0,1,0,0,0,0,1},
//         {1,1,1,0,1,1,1,0,1,0},
//         {1,0,1,1,1,1,0,1,0,0},
//         {1,0,0,0,0,1,0,0,0,1},
//         {1,0,1,1,1,1,0,1,1,1},
//         {1,1,1,0,0,0,1,0,0,1}
//     };

//     std::pair<int,int> src = {8,0};
//     std::pair<int,int> dest = {0,0};

//     a_star_search(grid, src, dest);
//     return 0;
// }

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
