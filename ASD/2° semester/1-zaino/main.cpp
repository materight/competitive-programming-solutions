#include <climits>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

typedef struct {
    int val = -1;

} _int;
typedef map<pair<int, int>, _int> matrix;

int knapsack_rec(vector<int> P, vector<int> V, int i, int c, matrix DP) {
    if (c < 0)
        return INT_MIN;
    else if (i < 0 || c == 0)
        return 0;
    else {
        pair<int, int> key = {i, c};
        if (DP[key].val < 0) {
            DP[key].val = max(
                knapsack_rec(P, V, i - 1, c, DP),                 //    Non prendo l'oggetto
                knapsack_rec(P, V, i - 1, c - P[i], DP) + V[i]);  //  Prendo l'oggetto
        }
        return DP[key].val;
    }
}

int knapsack(vector<int> P, vector<int> V, int N, int C) {
    matrix DP;
    return knapsack_rec(P, V, N - 1, C, DP);
}

int main(int argc, char** argv) {
    ifstream in("input.txt");
    ofstream out("output.txt");

    int C, N;  //  N = Numero oggetti, C = Capacità zaino
    in >> C >> N;

    vector<int> P(N);  //    Peso
    vector<int> V(N);  //    Valore

    for (int i = 0; i < N; i++) {
        in >> P[i] >> V[i];
    }

    int result = knapsack(P, V, N, C);
    out << result << endl;
    cout << result << endl;

    return 0;
}
