#include <bits/stdc++.h>

using namespace std;

int N, M, K, R;
int l[250], s[249], c[249];
int DP[250][250];

int soluz(int i, int j) {
    if (i == 0) {
        if (j == 0)
            DP[i][j] = 0;
        else
            DP[i][j] = INT_MAX;
    } else if (DP[i][j] == 0) {
        DP[i][j] = INT_MAX;
        for (int h = 0; h < M; h++) {
            if (abs(j - h) * K <= l[i - 1]) {
                int sol = soluz(i - 1, h);
                if (sol != INT_MAX) {
                    DP[i][j] = min(DP[i][j], sol + abs(j - h) * R + l[i - 1] + s[i - 1] + c[i - 1] * (j + 1));
                }
            }
        }
    }
    return DP[i][j];
}

int main(int argc, char** argv) {
    cin >> N >> M >> K >> R;

    for (int i = 0; i < N; i++) {
        cin >> l[i];
    }

    for (int i = 0; i < N - 1; i++) {
        cin >> s[i] >> c[i];
    }

    int result = INT_MAX;
    for (int h = 0; h < M; h++) {
        if (abs(0 - h) * K <= l[N - 1]) {
            int sol = soluz(N - 1, h);
            if (sol != INT_MAX) {
                result = min(result, sol + abs(0 - h) * R + l[N - 1]);
            }
        }
    }
    cout << result << endl;

    /*for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cout << " " << DP[i][j];
        }
        cout << endl;
    }*/

    return 0;
}