#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

int N;
ll DP[5100];

int main() {
    cin >> N;

    DP[0] = 0;
    DP[1] = 4;

    for (int i = 2; i <= N; i++) {
        ll min_div = LONG_LONG_MAX - 1000000;
        ll min_non_div = LONG_LONG_MAX - 1000000;

        for (int j = 1; j <= i / 2; j++) {
            min_div = min(min_div, DP[j] + DP[i - j]);
        }

        for (int k = 1; k <= (int)sqrt(i); k++) {
            min_non_div = min(min_non_div, i % k == 0 ? ((i / k + k) * 2) : LONG_LONG_MAX);
        }
        DP[i] = min(min_div, min_non_div);
    }

    cout << DP[N] << endl;

    return 0;
}