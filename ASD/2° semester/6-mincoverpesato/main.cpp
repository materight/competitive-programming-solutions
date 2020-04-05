#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int>> tree;
typedef vector<vector<int>> matrix;

int solve_rec(tree& T, vector<int>& P, matrix& DP, int i, bool preso) {
    if (DP[i][preso] == -1) {
        DP[i][preso] = preso ? P[i] : 0;
        for (int n : T[i]) {
            if (preso) {
                DP[i][preso] += min(solve_rec(T, P, DP, n, true), solve_rec(T, P, DP, n, false));
            } else {
                DP[i][preso] += solve_rec(T, P, DP, n, true);
            }
        }
    }
    return DP[i][preso];
}

int solve(tree& T, vector<int>& P) {
    matrix DP(T.size(), vector<int>(2, -1));
    return min(solve_rec(T, P, DP, 0, true), solve_rec(T, P, DP, 0, false));
}

int main(int argc, char** argv) {
    ifstream in("input.txt");
    ofstream out("output.txt");

    int N;
    in >> N;

    tree T(N);
    vector<int> P(N);

    for (int i = 0; i < N; i++) {
        in >> P[i];
    }

    for (int i = 0; i < N - 1; i++) {
        int p, f;
        in >> p >> f;
        T[p].push_back(f);
    }

    int soluz = solve(T, P);
    cout << soluz << endl;
    out << soluz << endl;

    return 0;
}