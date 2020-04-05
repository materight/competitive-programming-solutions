#include <fstream>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

typedef struct {
    char c;
    int v = 0;
} group;

typedef struct {
    int val = -1;
} _int;

int N;  //  Numero serate
int M;  //  Numero istanti per serata
int T;  //  Massimo numero di travestimenti

vector<vector<group>> S;
vector<vector<map<pair<int, char>, _int>>> DP;

// int solve_rec(int i, int j, int t, char last) {
//     if (i >= N) return 0;

//     if (j >= S[i].size()) {
//         //  Passo alla riga successiva
//         last = 'X';
//         j = 0;
//         i++;
//         if (i >= N) return 0;
//     }

//     group g = S[i][j];

//     if (DP[i][j][{t, last}].val == -1) {
//         if (t <= 0 && g.c != last) {
//             return solve_rec(i, j + 1, t, last);  //   Non prendo l'elemento, non posso più prenderli
//         } else if (g.c == last) {
//             DP[i][j][{t, last}].val = solve_rec(i, j + 1, t, last) + g.v;  //   Prendo l'elemento senza decrementare il numero di travestimenti
//         } else {
//             DP[i][j][{t, last}].val = max(
//                 solve_rec(i, j + 1, t - 1, g.c) + g.v,  //   Prendo l'elemento e decremento il numero di travestimenti disponibili
//                 solve_rec(i, j + 1, t, last)            //   Non prendo l'elemento
//             );
//         }
//     }
//     //printf("DP[%d,%d,%d,%c] = %d\n", i, j, t, last, DP[i][j][{t, last}].val);
//     return DP[i][j][{t, last}].val;
// }

int solve(int T) {
    //return solve_rec(0, 0, T, 'X');

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < S[i].size(); j++) {
        }
    }
}

int main(int argc, char** argv) {
    ifstream in("input.txt");
    ofstream out("output.txt");

    in >> N >> M >> T;

    S.resize(N);
    DP.resize(N);

    for (int i = 0; i < N; i++) {
        group g;
        g.v = 1;
        in >> g.c;
        for (int j = 1; j < M; j++) {
            char c;
            in >> c;
            if (c != g.c) {
                S[i].push_back(g);
                g.v = 1;
                g.c = c;
            } else {
                g.v++;
            }
        }
        S[i].push_back(g);
        DP[i].resize(S[i].size(), map<pair<int, char>, _int>());
    }

    // cout << N << " " << M << " " << T << endl;
    // for (auto i : S) {
    //     for (auto j : i) {
    //         cout << j.v << j.c << " ";
    //     }
    //     cout << endl;
    // }

    int soluz = solve(T);
    cout << soluz << endl;
    out << soluz << endl;

    //printf("DP[%d,%d,%d,%c] = %d\n", i, j, t, last, DP[i][j][{t, last}].val);

    // cout << endl
    //      << endl;
    // for (int i = 0; i < N; i++) {
    //     for (int j = 0; j < DP[i].size(); j++) {
    //         //cout << j.size() << " ";
    //         if (i == 0 && j == 1) {
    //             for (int k = 0; k <= T; k++) {
    //                 printf("DP[%d,%d,%d,%c] = %d\n", i, j, k, 'H', DP[i][j][{k, 'H'}].val);
    //                 printf("DP[%d,%d,%d,%c] = %d\n", i, j, k, 'J', DP[i][j][{k, 'J'}].val);
    //                 printf("DP[%d,%d,%d,%c] = %d\n", i, j, k, 'X', DP[i][j][{k, 'X'}].val);
    //             }
    //         }
    //     }
    //     cout << endl;
    // }

    return 0;
}