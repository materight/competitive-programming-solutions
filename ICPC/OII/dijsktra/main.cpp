#include <bits/stdc++.h>
#include <fstream>

using namespace std;

typedef long long int lli;
typedef struct arc {
    int node;
    lli p;
    arc(int _node, lli _p) : node(_node), p(_p){};
} arc;
typedef pair<lli, int> pi;
typedef vector<vector<arc>> graph;

int N, M, S, E;
graph G;
vector<lli> dist;

void dijkstra() {
    priority_queue<pi, vector<pi>, greater<pi>> Q;

    dist[S] = 0;
    Q.push({0, S});

    while (!Q.empty()) {
        int u = Q.top().second;
        Q.pop();
        for (arc v : G[u]) {
            if (dist[v.node] > dist[u] + v.p) {
                dist[v.node] = dist[u] + v.p;
                Q.push({dist[v.node], v.node});
            }
        }
    }
}

int main(int argc, char** argv) {
    ifstream in("input.txt");
    ofstream out("output.txt");

    in >> N >> M >> S >> E;

    G.resize(N + 1);
    dist.resize(N + 1, LONG_LONG_MAX);

    for (int i = 0; i < M; i++) {
        int a, b;
        lli p;
        in >> a >> b >> p;
        G[a].push_back(arc(b, p));
    }

    dijkstra();

    cout << dist[E] << endl;
    out << dist[E] << endl;

    return 0;
}