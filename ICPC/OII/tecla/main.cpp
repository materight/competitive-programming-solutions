#include <bits/stdc++.h>
#include <fstream>

#define NO -1
#define BLEAH 0
#define SLURP 1
#define TUTTO 2

using namespace std;

typedef vector<vector<int>> graph;

int N, M;
graph G;
vector<int> visited;  // -1 = non visitato, 0 = visitato con BLEAH, 1 = visitato con SLURP, 2 = visitato con entrambi

bool solve(int u, int stato, stack<int>& path) {
    if (visited[u] == TUTTO || visited[u] == stato) return false;  // Nodo giò visitato con questo stato
    if (visited[u] == NO) visited[u] = stato;                      // Nodo mai visitato
    if (visited[u] != stato) visited[u] = TUTTO;                   // Nodo non visitato con questo stato

    if (u == 0 && stato == SLURP) {
        return true;  // Soluzione trovata
    }

    for (int v : G[u]) {
        path.push(v);
        if (solve(v, 1 - stato, path))  // Visito il nodo con l'altro stato
            return true;
        path.pop();
    }
    return false;
}

int main(int argc, char** argv) {
    ifstream in("input.txt");
    ofstream out("output.txt");

    in >> N >> M;
    G.resize(N);
    visited.resize(N, NO);

    for (int i = 0; i < M; i++) {
        int a, b;
        in >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    stack<int> path;
    solve(0, BLEAH, path);

    // Soluzione trovata
    out << path.size() << endl;
    while (!path.empty()) {
        out << path.top() << " ";
        path.pop();
    }
    out << 0 << endl;

    return 0;
}