#include <bits/stdc++.h>
#include "grader.cpp"

#define MAXN 500000

using namespace std;

typedef struct scala {
    int v, s;  // Nodo e scala
    scala(int _v, int _s) : v(_v), s(_s){};
} scala;

vector<scala> G[MAXN];
int d[MAXN];

void bfs(int start, int inizio[], int fine[]) {
    d[start] = 0;
    queue<int> q;
    q.push(start);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (scala s : G[u]) {
            int new_d = d[u] + max(0, inizio[s.s] - d[u]) + 1;  // Se non posso ancora andare nella scala, provo ad aspettare
            if ((d[s.v] == -1 || new_d < d[s.v]) && d[u] < fine[s.s]) {
                d[s.v] = new_d;
                q.push(s.v);
            }
        }
    }
}

int raggiungi(int N, int M, int A[], int B[], int inizio[], int fine[]) {
    for (int i = 0; i < N; i++) d[i] = -1;
    for (int i = 0; i < M; i++) {
        G[A[i]].push_back(scala(B[i], i));
        G[B[i]].push_back(scala(A[i], i));
    }

    bfs(0, inizio, fine);

    return d[N - 1];
}
