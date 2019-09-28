#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int W, H;

typedef vector<vector<char>> map;
typedef struct point {
    int i, j;
    point() {
        point(-1, -1);
    }
    point(int _i, int _j) {
        i = _i;
        j = _j;
    }
} point;

vector<point> adj{point(0, -1), point(-1, 0), point(0, +1), point(+1, 0)};

int bfs(map& M, point s) {
    vector<vector<bool>> visited(H, vector<bool>(W));
    queue<point> q;
    int tot_gold = 0;
    q.push(s);
    visited[s.i][s.j] = true;
    while (!q.empty()) {
        point u = q.front();
        q.pop();
        int tot_adj = 0;
        bool found_gold = false;
        bool found_trap = false;
        for (point coord : adj) {
            int i = coord.i + u.i;
            int j = coord.j + u.j;
            if (i >= 0 && i < H && j >= 0 && j < W && M[i][j] != '#' && !visited[i][j]) {
                visited[i][j] = true;
                q.push(point(i, j));
                tot_adj++;
                if (M[i][j] == 'T') {
                    found_trap = true;
                } else if (M[i][j] == 'G') {
                    found_gold = true;
                }
            }
        }
        if (found_trap) {
            //  Se trovo una trappola, nei vicini, tolgo i vicini dalla coda
            for (int i = 0; i < tot_adj; i++) {
                q.pop();
            }
        } else if (found_gold) {
            tot_gold++;
        }
    }
    return tot_gold;
}

int main(int argc, char** argv) {
    cin >> W >> H;
    vector<vector<char>> M(H, vector<char>(W));

    point P;
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            cin >> M[i][j];
            if (M[i][j] == 'P') {
                P = point(i, j);
            }
        }
    }

    cout << bfs(M, P) << endl;

    return 0;
}