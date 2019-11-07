#include <bits/stdc++.h>
#include "grader.cpp"
#define MAXN 100000

using namespace std;

vector<int> G[MAXN];
int groups[MAXN];

void nuovo_gruppo();

void aggiungi(int bambino);

int dfs(int u) {
    int n_groups = 2;
    for (int v : G[u]) {
        if (groups[v] == -1) {
            groups[v] = (groups[u] == 0) ? 1 : 0;
            n_groups = max(n_groups, dfs(v));
        } else if (groups[u] == groups[v]) {
            n_groups = 3;
            groups[v] = 2;
        }
    }
    return n_groups;
}

void smista(int N, int nemico[]) {
    for (int i = 0; i < N; i++) {
        groups[i] = -1;
        G[i].push_back(nemico[i]);
        G[nemico[i]].push_back(i);
    }

    int n_groups = 2;
    for (int i = 0; i < N; i++) {
        if (groups[i] == -1) {
            n_groups = max(n_groups, dfs(i));
        }
    }

    for (int g = 0; g < n_groups; g++) {
        nuovo_gruppo();
        for (int i = 0; i < N; i++) {
            if (groups[i] == g) {
                aggiungi(i);
            }
        }
    }
}
