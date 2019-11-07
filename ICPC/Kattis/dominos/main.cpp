#include <iostream>
#include <stack>
#include <vector>

using namespace std;

#define MAXN 100000

int N, M;  //  N = num nodi, M = num archi

typedef vector<vector<int>> graph;

graph G(MAXN);
vector<int> dfs_num(MAXN);
vector<int> dfs_low(MAXN);
vector<bool> in_stack(MAXN);
vector<int> SCC(MAXN);
stack<int> S;

void dfs_tarjan(int u, int& t, int& current_scc) {
    dfs_num[u] = dfs_low[u] = t;
    t++;
    S.push(u);
    in_stack[u] = true;
    for (int v : G[u]) {
        if (dfs_num[v] == -1) {
            dfs_tarjan(v, t, current_scc);
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
        } else if (in_stack[v]) {
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
        }
    }
    if (dfs_num[u] == dfs_low[u]) {
        int v;
        do {
            v = S.top();
            S.pop();
            in_stack[v] = false;
            SCC[v] = current_scc;

        } while (v != u);
        current_scc++;
    }
}

int main(int argc, char** argv) {
    int N_CASE;
    cin >> N_CASE;

    for (int t = 0; t < N_CASE; t++) {
        cin >> N >> M;

        //  Resetto valori
        fill(G.begin(), G.end(), vector<int>(0));
        fill(dfs_num.begin(), dfs_num.end(), -1);
        //fill(dfs_low.begin(), dfs_low.end(), 0); NON SERVE REINIZIALIZZARLO
        fill(in_stack.begin(), in_stack.end(), false);
        //fill(SCC.begin(), SCC.end(), 0);  NON SERVE REINIZIALIZZARLO
        while (!S.empty()) S.pop();

        int src, dest;
        for (int i = 0; i < M; i++) {
            cin >> src >> dest;
            G[src - 1].push_back(dest - 1);
        }

        //	Trovo tutte le SCC
        int time = 0;
        int current_scc = 0;
        for (int u = 0; u < N; u++) {
            if (dfs_num[u] == -1) {
                dfs_tarjan(u, time, current_scc);
            }
        }

        vector<int> arc_in(current_scc, 0);

        for (int u = 0; u < N; u++) {
            for (int v : G[u]) {
                if (SCC[u] != SCC[v]) {
                    //  Per ogni SCC conto i nodi entranti
                    arc_in[SCC[v]]++;
                }
            }
        }

        int tot = 0;
        for (int u = 0; u < current_scc; u++) {
            //	Ogni scc senza nodi entranti deve essere "colpita" direttamente, tutte le altre sono raggiungibili e quindi verranno abbattute di conseguenza
            if (arc_in[u] == 0) {
                tot++;
            }
        }

        cout << tot << endl;
    }
    return 0;
}