#include <bits/stdc++.h>
#include <fstream>

using namespace std;

typedef struct arc {
    int n, p;
    arc(int _n, int _p) : n(_n), p(_p){};
} arc;
typedef pair<int, int> pi;
typedef vector<vector<arc>> graph;

int N, M, C, K;
graph G;
vector<int> dist;
vector<int> aria;
vector<bool> is_aria;

void dijkstra(int s) {
    priority_queue<pi, vector<pi>, greater<pi>> Q;
    Q.push({0, s});
    dist[s] = 0;
    aria[0] = 0;

    while (!Q.empty()) {
        int u = Q.top().second;
        Q.pop();
        for (arc v : G[u]) {
            if (dist[v.n] > dist[u] + v.p && aria[u] + v.p < 20) {
                dist[v.n] = dist[u] + v.p;
                aria[v.n] = is_aria[v.n] ? 0 : aria[u] + v.p;
                Q.push({dist[v.n], v.n});
            }
        }
    }
}

int main(int argc, char** argv) {
    ifstream in("input.txt");
    ofstream out("output.txt");

    in >> N >> M >> C >> K;
    G.resize(N + 1);
    dist.resize(N + 1, INT_MAX);
    aria.resize(N + 1, 0);  // Aria usata
    is_aria.resize(N + 1, false);

    for (int i = 0; i < K; i++) {
        int n;
        in >> n;
        is_aria[n] = true;
    }

    for (int i = 0; i < M; i++) {
        int a, b, p;
        in >> a >> b >> p;
        G[a].push_back(arc(b, p));
        G[b].push_back(arc(a, p));
    }

    dijkstra(1);

    int res = dist[C];
    if (res == INT_MAX) res = -1;

    cout << res << endl;
    out << res << endl;

    return 0;
}