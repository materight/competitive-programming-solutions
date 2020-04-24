#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

ll dist(ll ax, ll ay, ll bx, ll by) {
    return abs(ax - bx) + abs(ay - by);
}

vector<pair<char, pair<ll, ll>>> jumps(ll jump_size) {
    vector<pair<char, pair<ll, ll>>> res;
    res.push_back({'E', {jump_size, 0}});
    res.push_back({'S', {0, jump_size}});
    res.push_back({'W', {-jump_size, 0}});
    res.push_back({'N', {0, -jump_size}});
    return res;
}

ll targetX;
ll targetY;
ll minSolLength;
string minSol;

void solve(ll x, ll y, ll i, vector<char>& S) {
    // Worse or impossible path
    ll jump_size = 1 << i;
    if (i >= minSolLength || (jump_size + jump_size * 2) > dist(x, y, targetX, targetY)) return;

    if (x == targetX && y == targetY) {
        // Solution found
        minSolLength = i;
        minSol = string(S.begin(), S.end());
        return;
    }

    cout << x << " " << y << endl;

    for (auto j : jumps(jump_size)) {
        S.push_back(j.first);
        solve(x + j.second.first, y + j.second.second, i + 1, S);
        S.pop_back();
    }
}

int main(int argc, char** argv) {
    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        cin >> targetX >> targetY;
        minSolLength = LONG_LONG_MAX;
        vector<char> S;
        solve(0, 0, 0, S);

        cout << "Case #" << t << ": ";
        if (minSolLength == LONG_LONG_MAX)
            cout << "IMPOSSIBLE";
        else
            cout << minSol;
        cout << endl;
    }
    return 0;
}