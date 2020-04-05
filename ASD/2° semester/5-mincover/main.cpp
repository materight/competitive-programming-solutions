#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int>> tree;
typedef vector<vector<int>> matrix;

int solve_rec(tree& T, matrix& DP, int i, bool preso) {
    if (DP[i][preso] == -1) {
        DP[i][preso] = preso;
        for (int n : T[i]) {
            if (preso) {
                DP[i][preso] += min(solve_rec(T, DP, n, true), solve_rec(T, DP, n, false));
            } else {
                DP[i][preso] += solve_rec(T, DP, n, true);
            }
        }
    }
    return DP[i][preso];
}

int solve(tree& T) {
    matrix DP(T.size(), vector<int>(2, -1));
    return min(solve_rec(T, DP, 0, true), solve_rec(T, DP, 0, false));
}

int main(int argc, char** argv) {
    ifstream in("input.txt");
    ofstream out("output.txt");

    int N;
    in >> N;

    tree T(N);
    vector<bool> S;

    for (int i = 0; i < N - 1; i++) {
        int P, F;
        in >> P >> F;
        T[P].push_back(F);
    }

    int soluz = solve(T);
    cout << soluz << endl;
    out << soluz << endl;

    return 0;
}