#include <bits/stdc++.h>
#include <fstream>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef struct _ll {
    ll v = -1;
} _ll;

int M, N;
vector<ll> P;
vector<unordered_map<ll, _ll>> DP;

ll calc(int i, int c) {
    if (c < 0) return LONG_LONG_MIN;
    if (i < 0 || c == 0) return 0;
    if (DP[i][c].v == -1) {
        DP[i][c].v = max(calc(i - 1, c),
                         calc(i - 1, c - P[i]) + P[i]);
    }
    return DP[i][c].v;
}

void solve(string file) {
    cout << "Solving " << file << "... ";
    ifstream in(file + ".in");
    ofstream out(file + ".out");

    in >> M >> N;

    P.resize(N);
    DP.resize(N);

    for (int i = 0; i < N; i++) {
        in >> P[i];
    }

    calc(N - 1, M);
    out << DP[N - 1][M].v << endl;
    cout << "Done" << endl;
}

int main(int argc, char** argv) {
    solve("a");
    solve("b");
    solve("c");
    solve("d");
    //solve("e");
    return 0;
}
