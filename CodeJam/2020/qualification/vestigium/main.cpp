#include <bits/stdc++.h>

using namespace std;

int M[100][100];

int main(int argc, char** argv) {
    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        int N;
        cin >> N;
        int trace = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cin >> M[i][j];
                if (i == j) {
                    trace += M[i][j];
                }
            }
        }
        // Rows
        int rep_rows = 0;
        for (int i = 0; i < N; i++) {
            vector<bool> visited(N);
            for (int j = 0; j < N; j++) {
                if (visited[M[i][j]]) {
                    rep_rows++;
                    break;
                } else {
                    visited[M[i][j]] = true;
                }
            }
        }
        // Cols
        int rep_cols = 0;
        for (int j = 0; j < N; j++) {
            vector<bool> visited(N);
            for (int i = 0; i < N; i++) {
                if (visited[M[i][j]]) {
                    rep_cols++;
                    break;
                } else {
                    visited[M[i][j]] = true;
                }
            }
        }

        cout << "Case #" << t << ": " << trace << " " << rep_rows << " " << rep_cols << endl;
    }
    return 0;
}