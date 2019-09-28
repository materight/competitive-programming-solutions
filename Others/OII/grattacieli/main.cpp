#include <queue>
#include <vector>
#include "grader.cpp"

using namespace std;

typedef struct node {
    int adj;
    long long w;
    node(int _adj, long long _w) : adj(_adj), w(_w){};
} node;

typedef vector<vector<node>> graph;

void bfs(int start, graph& G, vector<long long>& max_H, vector<long long>& H) {
    H[start] = max_H[start];
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    q.push({0, start});
    while (!q.empty()) {
        int u = q.top().second;
        q.pop();
        for (node n : G[u]) {
            int v = n.adj;
            if (H[v] == -1 || H[u] + n.w < H[v]) {  // Nuovo conflitto da risolvere rianializzando il grafo e il nodo
                H[v] = min(H[u] + n.w, max_H[v]);
                q.push({H[v], v});
            }
        }
    }
}

long long costruisci(int N, int M, vector<long long>& max_H, vector<int>& A, vector<int>& B, vector<int>& C) {
    graph G(N);
    vector<long long> H(N, -1);
    for (int i = 0; i < M; i++) {
        G[A[i]].push_back(node(B[i], C[i]));
    }

    for (int i = 0; i < N; i++) {
        if (H[i] == -1) {
            bfs(i, G, max_H, H);
        }
    }

    long long sum = 0;
    for (long long h : H) {
        sum += h;
    }
    return sum;
}