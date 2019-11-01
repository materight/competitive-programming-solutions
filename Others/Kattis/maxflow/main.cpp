#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef vector<vector<int>> graph;
typedef vector<vector<int>> matrix;

pair<matrix, bool> get_augmenting_path(graph &G, int s, int t, matrix &r) {
    int N = G.size();
    matrix g(N, vector<int>(N, 0));

    vector<int> parent(N, -1);
    queue<int> q;

    parent[s] = 0;
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : G[u]) {
            if (r[u][v] > 0 && parent[v] == -1) {
                parent[v] = u;
                q.push(v);
                if (v == t) {
                    //  Ho trovato il cammino aumentante, costruisco g:
                    //  Trovo il minimo cf sul cammino
                    int x = v;
                    int cf = INT32_MAX;
                    while (x != 0) {
                        cf = min(cf, r[parent[x]][x]);
                        x = parent[x];
                    }
                    x = v;
                    while (x != 0) {
                        g[parent[x]][x] = cf;
                        g[x][parent[x]] = -cf;
                        x = parent[x];
                    }
                    return {g, true};
                }
            }
        }
    }
    return {g, false};
}

matrix max_flow(graph &G, int s, int t, matrix &c) {
    int N = G.size();
    matrix f(N, vector<int>(N));  //  Flusso parziale
    matrix r(N, vector<int>(N));  //  Rete residua

    for (int u = 0; u < N; u++) {
        for (int v : G[u]) {
            f[u][v] = 0;
            r[u][v] = c[u][v];
        }
    }

    bool found;
    do {
        pair<matrix, int> res = get_augmenting_path(G, s, t, r);  //  Flusso da cammino aumentante
        matrix g = res.first;
        found = res.second;
        if (found) {
            for (int u = 0; u < N; u++) {
                for (int v : G[u]) {
                    f[u][v] = f[u][v] + g[u][v];
                    r[u][v] = c[u][v] - f[u][v];
                }
            }
        }
    } while (found);

    return f;
}

int main(int argc, char **argv) {
    int N, M, s, t;
    cin >> N >> M >> s >> t;

    graph G(N);
    matrix c(N, vector<int>(N));

    for (int i = 0; i < M; i++) {
        int u, v, cost;
        cin >> u >> v >> cost;
        G[u].push_back(v);
        G[v].push_back(u);
        c[u][v] = cost;
        c[v][u] = 0;
    }

    matrix flow = max_flow(G, s, t, c);

    int f = 0;
    for (int v : G[s]) {
        f += flow[s][v];
    }

    int m1 = 0;  //  Numero di archi usati
    for (int u = 0; u < N; u++) {
        for (int v : G[u]) {
            if (flow[u][v] > 0) m1++;
        }
    }

    cout << N << " " << f << " " << m1 << endl;
    for (int u = 0; u < N; u++) {
        for (int v : G[u]) {
            if (flow[u][v] > 0) cout << u << " " << v << " " << flow[u][v] << endl;
        }
    }

    return 0;
}