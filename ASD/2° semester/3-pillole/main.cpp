#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<long long int>> matrix;

long long int solve_rec(int I, int M, matrix& DP) {
    if (DP[I][M] == -1) {
        if (I == 0) {
            DP[I][M] = 1;
        } else if (M == 0) {
            DP[I][M] = solve_rec(I - 1, M + 1, DP);
        } else {
            DP[I][M] = solve_rec(I - 1, M + 1, DP)  //  Pesco intera
                       + solve_rec(I, M - 1, DP);   //  Pesco mezza
        }
    }
    return DP[I][M];
}

int main(int argc, char** argv) {
    ifstream in("input.txt");
    ofstream out("output.txt");

    int N;
    in >> N;

    matrix DP = matrix(N + 1, vector<long long int>(N + 1, -1));

    long long int soluz = solve_rec(N, 0, DP);
    out << soluz << endl;
    cout << soluz << endl;

    return 0;
}