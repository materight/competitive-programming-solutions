#include <bits/stdc++.h>

using namespace std;

typedef vector<vector<int>> graph;

vector<bool> visited_in;
vector<bool> farlocco;
vector<bool> self;
graph prato;

int dfs(int u, bool in_visit) {
    int res = 0;
    if (in_visit) {
        visited_in[u] = true;
        res++;
    } else {
        farlocco[u] = true;
    }

    for (int v : prato[u]) {
        if ((!in_visit && !visited_in[v]) || (in_visit && !farlocco[v])) {
            res += dfs(v, !in_visit);
        }
    }
    return res;
}

int main(int argc, char** argv) {
    int N, M;
    cin >> N >> M;

    prato.resize(N);
    visited_in.resize(N, false);
    farlocco.resize(N, false);
    self.resize(N, false);

    int v0 = 0;
    int u, v;
    while (cin >> u >> v) {
        prato[u].push_back(v);
        if (u == v) self[u] = true;
    }

    cout << dfs(v0, true) << endl;

    return 0;
}