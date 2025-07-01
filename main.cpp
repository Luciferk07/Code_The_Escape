#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100;
int n, m;
char maze[MAXN][MAXN];
char originalMaze[MAXN][MAXN];
bool visited[MAXN][MAXN];
pair<int, int> parent[MAXN][MAXN];
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
pair<int, int> start, end_pos;

// TODO 1: Check if (x, y) is a valid move
bool isValid(int x, int y) {
    if(x>=n||y>=m||x<0||y<0) return false;
    if(maze[x][y]=='0') return false;
    if(visited[x][y]) return false;
return true;
    }

// TODO 2: BFS Implementation
void bfs() {
    queue<pair<int, int>> q;
    visited[start.first][start.second] = true;
    q.push(start);

    while (!q.empty()) {
        pair<int, int> cur = q.front(); q.pop();
        if (cur == end_pos) break;

        for (int i = 0; i < 4; ++i) {
            int nx = cur.first + dx[i];
            int ny = cur.second + dy[i];

            // Fill the condition and logic
            if (isValid(nx, ny)) {
                visited[nx][ny] = true;
                parent[nx][ny] = cur;
                q.push({nx, ny});
            }
        }
    }
}

// TODO 3: DFS Implementation
bool dfs(int x, int y) {
    if (x == end_pos.first && y == end_pos.second) return true;

    visited[x][y] = true;
    if (maze[x][y] != 'S' && maze[x][y] != 'E') maze[x][y] = '*';

    bool check = false;

    for (int dir = 0; dir < 4; dir++) {
        int nx = x + dx[dir];
        int ny = y + dy[dir];
        if (isValid(nx, ny)) {
            parent[nx][ny] = {x, y};
            if (dfs(nx, ny)) {
                check = true;
                break;
            }
        }
    }

    if (check) return true;
    if (maze[x][y] != 'S' && maze[x][y] != 'E')
        maze[x][y] = '1';
    visited[x][y] = false;
    return false;

}

// TODO 4: Reconstruct and print the path
void reconstructPath(pair<int, int> end_point) {
    vector<pair<int, int>> path;

    pair<int, int> cur = end_point;

    // Trace back to start
    while (!(cur == start)) {
        path.push_back(cur);
        cur = parent[cur.first][cur.second];
    }
    path.push_back(start);

    reverse(path.begin(), path.end());

    cout << "Path from S to E:\n";
    for (auto p : path) {
        cout << "(" << p.first << ", " << p.second << ") ";
    }
    cout << '\n';
}


void printMaze() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << maze[i][j];
        }
        cout << '\n';
    }
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> maze[i][j];
            originalMaze[i][j] = maze[i][j];
            if (maze[i][j] == 'S') start = {i, j};
            if (maze[i][j] == 'E') end_pos = {i, j};
        }
    }

    // Uncomment the one you want to test
    cout << "BFS Pathfinding \n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            maze[i][j] = originalMaze[i][j];
            visited[i][j] = false;
        }
    }
    bfs();
    if (visited[end_pos.first][end_pos.second]) {
        reconstructPath(end_pos);
        cout << "Maze with BFS Path:\n";
        printMaze();
    } else {
        cout << "No Path from S to E found by BFS.\n";
        cout << "Original Maze:\n";
        printMaze();
    }

    cout << "\nDFS Pathfinding\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            maze[i][j] = originalMaze[i][j];
            visited[i][j] = false;
        }
    }

    bool found = dfs(start.first, start.second);
    if (found) {
        cout << "Maze with DFS Path:\n";
        reconstructPath(end_pos);
        printMaze();
    } else {
        cout << "No Path from S to E found by DFS.\n";
        cout << "Original Maze:\n";
        printMaze();
    }

    return 0;
}
