#include <climits>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char** argv) {
    int N;
    cin >> N;

    vector<vector<int>> cost(N, vector<int>(3));
    vector<vector<int>> DP(N, vector<int>(3));

    for (int i = 0; i < N; i++) {
        cin >> cost[i][0] >> cost[i][1] >> cost[i][2];
    }

    DP[0][0] = cost[0][0];
    DP[0][1] = cost[0][1];
    DP[0][2] = cost[0][2];

    for (int i = 1; i < N; i++) {
        for (int a_i = 0; a_i < 3; a_i++) {
            int max_c = INT_MIN;
            //  Per ogni precedente, trovo quello con guadagno massimo
            for (int a_j = 0; a_j < 3; a_j++) {
                if (a_i != a_j) {
                    max_c = max(max_c, DP[i - 1][a_j]);
                }
            }
            DP[i][a_i] = max_c + cost[i][a_i];
        }
    }

    int max_tot;
    for (int i = 0; i < 3; i++) {
        max_tot = max(max_tot, DP[N - 1][i]);
    }

    cout << max_tot << endl;

    return 0;
}