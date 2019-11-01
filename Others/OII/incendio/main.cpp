#include <math.h>
#include <queue>
#include <vector>
#include "grader.cpp"

#define _N 0
#define _S 1
#define _W 2
#define _E 3
#define _start 4
#define _end 5

using namespace std;

typedef struct node {
    int i, w;
    node(int _i, int _w) : i(_i), w(_w){};
} node;

typedef vector<vector<node>> graph;

int distman(int ax, int ay, int bx, int by) {
    return abs(ax - bx) + abs(ay - by);
}

int minpositive(int a, int b) {
    if (a < 0) return b;
    if (b < 0) return a;
    return min(a, b);
}

void minpath(graph &G, int s, vector<int> &dist) {
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (node n : G[u]) {
            int v = n.i;
            int newW = max(dist[u], n.w);
            if (dist[v] == -1 || newW < dist[v]) {
                dist[v] = newW;
                q.push(v);
            }
        }
    }
}

int alzati(int N, int M, int X[], int Y[]) {
    graph G(M + 4);  // Numero fuochi + numero muri

    // Grafo completo tra fuochi
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            if (i != j) {
                int dist = distman(X[i], Y[i], X[j], Y[j]) / 2 - 1;  // Diviso 2 perchè entrambi i nodi espandono il fuoco
                G[i].push_back(node(j, dist));
                G[j].push_back(node(i, dist));
            }
        }
    }

    // Distanze da muri
    for (int i = 0; i < M; i++) {
        // N/S
        int dN = distman(0, Y[i], 0, 0);
        int dS = distman(0, Y[i], 0, N - 1);
        if (dN < dS) {
            G[i].push_back(node(M + _N, dN));
            G[M + _N].push_back(node(i, dN));
        } else {
            G[i].push_back(node(M + _S, dS));
            G[M + _S].push_back(node(i, dS));
        }

        int dW = distman(X[i], 0, 0, 0);
        int dE = distman(X[i], 0, N - 1, 0);
        if (dW < dE) {
            G[i].push_back(node(M + _W, dW));
            G[M + _W].push_back(node(i, dW));
        } else {
            G[i].push_back(node(M + _E, dE));
            G[M + _E].push_back(node(i, dE));
        }
    }

    vector<int> distN(M + 4, -1);
    vector<int> distE(M + 4, -1);

    // Calcolo percorsi minimi da N
    minpath(G, M + _N, distN);
    // Calcolo percorsi minimi da E
    minpath(G, M + _E, distE);

    int minY = distN[M + _S] - 1;   // Minimo da N a S
    int minX = distE[M + _W] - 1;   // Minimo da E a W
    int minNW = distN[M + _W] - 1;  // Minimo da N a W
    int minES = distE[M + _S] - 1;  // Minimo da E a S

    printf("%d - %d - %d - %d\n", minY, minX, minNW, minES);

    return minpositive(minpositive(minY, minX), minpositive(minNW, minES));
}
