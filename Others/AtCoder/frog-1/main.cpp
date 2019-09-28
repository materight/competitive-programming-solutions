#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char** argv) {
    int N;
    cin >> N;

    vector<int> cost(N);

    for (int i = 0; i < N; i++) {
        cin >> cost[i];
    }

    vector<int> DP(N);
    DP[0] = 0;
    DP[1] = abs(cost[0] - cost[1]);
    int i = 2;
    while (i < N) {
        DP[i] = min(
            DP[i - 1] + abs(cost[i - 1] - cost[i]),
            DP[i - 2] + abs(cost[i - 2] - cost[i]));
        i++;
    }
    cout << DP[N - 1] << endl;
    return 0;
}