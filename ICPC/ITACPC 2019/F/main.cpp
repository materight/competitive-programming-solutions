#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

typedef struct node_t {
    int v, w;
    node_t(int v, int w) : v(v), w(w){};
} node_t;

typedef struct type_t {
    int i, w;
    type_t() : i(0), w(0){};
    type_t(int i, int w) : i(i), w(w){};
} type_t;

typedef vector<vector<node_t>> graph;

int N, K, T;
graph* G;
vector<type_t> types;

void bfs(int s, int w, vector<int>& conn, int current_conn) {
    queue<int> q;
    q.push(s);
    conn[s] = current_conn;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (node_t n : G->at(u)) {
            if (w <= n.w && conn[n.v] == -1) {
                q.push(n.v);
                conn[n.v] = current_conn;
            }
        }
    }
}

int main(int argc, char** argv) {
    cin >> N >> K >> T;
    G = new graph(N);
    types.resize(T);

    for (int i = 0; i < K; i++) {
        int a, b, v;
        cin >> a >> b >> v;
        G->at(a - 1).push_back(node_t(b - 1, v));
        G->at(b - 1).push_back(node_t(a - 1, v));
    }

    for (int i = 0; i < T; i++) {
        int w;
        cin >> w;
        types[i] = type_t(i, w);
    }

    sort(types.rbegin(), types.rend(), [](type_t a, type_t b) {
        return a.w < b.w;
    });

    vector<int> result(T);

    for (int t = 0; t < T; t++) {
        vector<int> conn(G->size(), -1);  // Componenti connesse
        int count = 0;
        for (unsigned int i = 0; i < G->size(); i++) {
            if (conn[i] == -1) {
                //  Componente connessa
                bfs(i, types[t].w, conn, count);
                count++;
            }
        }
        result[types[t].i] = count;
        graph* newG = new graph(count);
        for (unsigned int i = 0; i < G->size(); i++) {
            for (node_t n : G->at(i)) {
                n.v = conn[n.v];
                newG->at(conn[i]).push_back(n);
            }
        }
        graph* tmp = G;
        G = newG;
        free(tmp);
    }
    for (int c : result) {
        printf("%d\n", c);
    }
    return 0;
}