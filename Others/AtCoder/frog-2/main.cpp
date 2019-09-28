#include <climits>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char** argv) {
    int N, K;
    cin >> N >> K;

    vector<int> cost(N);
    vector<int> DP(N);

    for (int i = 0; i < N; i++) {
        cin >> cost[i];
    }

    DP[0] = 0;
    for (int i = 1; i < N; i++) {
        int min_jump = INT_MAX;
        for (int j = max(0, i - K); j < i; j++) {
            min_jump = min(min_jump, DP[j] + abs(cost[j] - cost[i]));
        }
        DP[i] = min_jump;
    }
    cout << DP[N - 1] << endl;
    return 0;
}