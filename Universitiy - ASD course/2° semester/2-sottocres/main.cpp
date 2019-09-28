#include <climits>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int>> matrix;

//  RICORSIVO
int solve_rec(vector<int> A, int i, int last, matrix* _DP) {
    if (i >= A.size()) return 0;

    matrix& DP = *_DP;
    int j = last != -1 ? last : A.size();

    if (DP[i][j] == -1) {
        int taken = INT_MIN;
        if (last == -1 || A[i] >= A[last]) {
            //  Se posso prendere l'elemento
            taken = solve_rec(A, i + 1, i, &DP) + A[i];
        }
        int not_taken = solve_rec(A, i + 1, last, &DP);
        DP[i][j] = max(taken, not_taken);
    }
    return DP[i][j];
}

int solve(vector<int> A) {
    matrix DP = matrix(A.size(), vector<int>(A.size() + 1, -1));  //  Metto in posizione N+1 quelli con last == -1
    return solve_rec(A, 0, -1, &DP);
}

//  ITERATIVO
int solve_iter(vector<int> A) {
    int N = A.size();
    vector<int> DP(N);

    int m = 0;
    for (int i = 0; i < N; i++) {
        DP[i] = A[i];
        for (int k = 0; k < i; k++)
            if (A[k] <= A[i])
                DP[i] = max(DP[i], A[i] + DP[k]);
        m = max(m, DP[i]);
    }
    return m;
}

int main(int argc, char** argv) {
    ifstream in("input.txt");
    ofstream out("output.txt");

    int N;
    in >> N;

    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        in >> A[i];
    }

    int soluz = solve_iter(A);
    cout << soluz << endl;
    out << soluz << endl;

    return 0;
}
