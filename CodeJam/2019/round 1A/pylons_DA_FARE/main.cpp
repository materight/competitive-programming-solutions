#include <iostream>
#include <vector>

using namespace std;

vector<int> mx{-1, 1, 2, 2, 1, -1, -2, -2};
vector<int> my{-2, -2, -1, 1, 2, 2, 1, -1};

void processSolution(vector<pair<int, int>>& solution) {
    cout << "POSSIBLE" << endl;
    for (auto p : solution) {
        cout << p.first << " " << p.second << endl;
    }
}

bool solve(vector<vector<int>>& S, vector<pair<int, int>>& solution, int R, int C, int i, int x, int y) {
    for (int i = 0; i < 8; i++) {
        int nx = x + mx[i];
        int ny = y + my[i];
        if ((1 <= nx && nx <= R) && (1 <= ny && ny <= C) && S[nx][ny] == 0) {
            S[x][y] = i;
            solution[i] = make_pair(x, y);
            if (i == R * C) {
                processSolution(solution);
                return true;
            } else if (solve(S, solution, R, C, i + 1, nx, ny)) {
                return true;
            }
            S[x][y] = 0;
            solution[i] = make_pair(-1, -1);
        }
    }
    return false;
}

int main(int argc, char** argv) {
    int T;
    cin >> T;

    for (int t = 0; t < T; t++) {
        int R, C;
        cin >> R >> C;

        vector<vector<int>> S(R + 1, vector<int>(C + 1));
        vector<pair<int, int>> solution(R * C);

        cout << "Case #" << t + 1 << ": ";
        if (!solve(S, solution, R, C, 0, 0, 0)) {
            cout << "IMPOSSIBLE" << endl;
        }
    }
    return 0;
}