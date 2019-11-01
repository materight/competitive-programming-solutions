#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef vector<vector<int>> graph;

bool backtrack(graph &G, int u, int prec_a, vector<int> &assign) {
    if (assign[u] == prec_a) return false;  // Conflitto
    if (assign[u] != 0) return true;        // Animale già assegnato

    for (int a = 1; a <= 4; a++) {
        if (a != prec_a) {
            assign[u] = a;
            bool valid = true;
            for (int v : G[u]) {
                if (!backtrack(G, v, a, assign)) {
                    valid = false;
                    break;
                }
            }
            if (valid) return true;
        }
    }
    assign[u] = 0;
    return false;
}

int main(int argc, char **argv) {
    int N;
    cin >> N;

    graph G(N);

    char ignore;
    int v1, v2;

    while (!cin.eof()) {
        cin >> v1 >> ignore >> v2;
        G[v1 - 1].push_back(v2 - 1);
        G[v2 - 1].push_back(v1 - 1);
    }

    vector<int> assign(N, 0);

    for (int i = 0; i < N; i++) {
        if (assign[i] == 0) {
            backtrack(G, i, -1, assign);
        }
    }

    for (int i = 0; i < N; i++) {
        cout << i + 1 << " " << assign[i] << endl;
    }

    return 0;
}