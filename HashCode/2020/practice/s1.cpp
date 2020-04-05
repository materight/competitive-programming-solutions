#include <bits/stdc++.h>
#include <fstream>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;

int M, N;
vector<pll> P;

void solve(string file) {
    cout << "Solving " << file << endl;
    ifstream in(file + ".in");
    ofstream out(file + ".out");

    in >> M >> N;

    P.resize(N);

    for (int i = 0; i < N; i++) {
        P[i].first = i;
        in >> P[i].second;
    }
    sort(P.begin(), P.end());

    ll sum = 0;
    queue<ll> q;
    for (int i = 0; i < N; i++) {
        if (sum + P[i].second >= M) break;
        sum += P[i].second;
        q.push(P[i].first);
    }

    out << q.size() << endl;
    while (!q.empty()) {
        out << q.front() << " ";
        q.pop();
    }
}

int main(int argc, char** argv) {
    solve("a");
    solve("b");
    solve("c");
    solve("d");
    solve("e");
    return 0;
}
