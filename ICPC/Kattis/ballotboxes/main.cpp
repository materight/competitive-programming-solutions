#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int>> matrix;

int solve2(int N, int B, vector<int>& c, matrix& DP) {
    for (int b = 0; b <= B; b++) DP[0][b] = (int)ceil(c[0] / (float)b);
    DP[0][0] = DP[1][0] = INT32_MAX;
    for (int n = 1; n < N; n++) {
        for (int b = 1; b <= B; b++) {
            int minDP = INT32_MAX;
            for (int i = 1; i <= b; i++) {
                minDP = min(minDP, max(DP[(n - 1) % 2][b - i], (int)ceil(c[n] / (float)i)));
            }
            DP[n % 2][b] = minDP;
        }
    }
    return DP[(N - 1) % 2][B];
}

int main(int argc, char** argv) {
    int N, B;
    cin >> N >> B;

    while (N != -1 && B != -1) {
        vector<int> c(N);

        int sum = 0;
        for (int i = 0; i < N; i++) {
            cin >> c[i];
            sum += c[i];
        }

        matrix DP(2, vector<int>(B + 1, -1));

        cout << solve2(N, B, c, DP) << endl;

        cin >> N >> B;
    }

    return 0;
}