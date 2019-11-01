#include <iostream>
#include <queue>
#include <vector>

using namespace std;

#define MAXN 100

typedef vector<vector<char>> matrix;

int M, N;
matrix map;

void c_bfs(int x, int y, char parent_c, queue<pair<int, int>>& q, vector<vector<bool>>& visited) {
    if (x >= 0 && y >= 0 && x < M && y < N && !visited[x][y] && map[x][y] == parent_c) {
        visited[x][y] = true;
        q.push({x, y});
    }
}

void bfs(int ux, int uy, vector<vector<bool>>& visited) {
    visited[ux][uy] = true;
    queue<pair<int, int>> q;
    q.push({ux, uy});
    char c;
    while (!q.empty()) {
        ux = q.front().first;
        uy = q.front().second;
        c = map[ux][uy];
        q.pop();
        c_bfs(ux - 1, uy, c, q, visited);
        c_bfs(ux, uy - 1, c, q, visited);
        c_bfs(ux + 1, uy, c, q, visited);
        c_bfs(ux, uy + 1, c, q, visited);
    }
}

int solve() {
    vector<vector<bool>> visited(M, vector<bool>(N));

    int stars = 0;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (!visited[i][j]) {
                if (map[i][j] == '-') stars++;
                bfs(i, j, visited);
            }
        }
    }
    return stars;
}

int main(int argc, char** argv) {
    map.resize(MAXN, vector<char>(MAXN));
    int i = 1;
    while (cin >> M >> N) {
        cerr << "M: " << M << ", N: " << N << endl;
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                cin >> map[i][j];
            }
        }

        cout << "Case " << i << ": " << solve() << endl;
        i++;
    }

    return 0;
}