#include <climits>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

typedef long long int llint;

typedef struct _llint {
    llint v = -1;
} _lint;

llint solve(vector<unordered_map<llint, _llint>> &DP, vector<llint> &w, vector<llint> &v, int i, llint W) {
    if (W < 0) return LONG_LONG_MIN;
    if (W == 0 || i < 0) return 0;
    if (DP[i][W].v == -1) {
        DP[i][W].v = max(
            solve(DP, w, v, i - 1, W - w[i]) + v[i],  //  Prendo l'elemento i
            solve(DP, w, v, i - 1, W));               //  Non prendo l'elemento i
    }
    return DP[i][W].v;
}

int main(int argc, char **argv) {
    int N;
    llint W;
    cin >> N >> W;

    vector<llint> w(N);
    vector<llint> v(N);
    vector<unordered_map<llint, _llint>> DP(N);

    for (int i = 0; i < N; i++) {
        cin >> w[i] >> v[i];
    }

    llint res = solve(DP, w, v, N - 1, W);
    cout << res << endl;

    return 0;
}