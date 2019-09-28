#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef struct arc {
    int a = -1, w = -1;
    arc() {}
    arc(int _a, int _w) {
        a = _a;
        w = _w;
    }
} arc;

typedef vector<vector<arc>> graph;

int N;  //  Numero città
int K;  //   Numero di valori di L

graph G;
vector<int> L;

vector<int> dist;

//  SI PUO' OTTIMIZZARE????
void calc_dist(vector<int>& max_dist) {
    vector<bool> visited(N);
    for (int i = 0; i < N; i++) {
        vector<int> dist(N, -1);
        queue<int> q;
        dist[i] = 0;
        q.push(i);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (arc c : G[u]) {
                if (dist[c.a] == -1) {
                    q.push(c.a);
                    dist[c.a] = dist[u] + c.w;
                    max_dist[i] = max(max_dist[i], dist[c.a]);
                }
            }
        }
    }
}

/**
 * Un nodo si può "prendere", ossia si può mettere un cavaliere su quel nodo, o no
 * 
 **/
int solve_rec(int n, int start, bool preso, int L) {
    int max_L = 0;
    for (int i; i < G[n].size(); i++) {
        int u = G[n][i].a;
        if (start == 0) {
            //  Se non ho ancora preso nessun nodo, posso partire da uno dei figli o prendere il nodo corrente
            max_L = max(max_L, solve_rec(u, dist[u], true, L));
        } else if (preso && abs(start - dist[u]) <= L) {
            //  Se ho preso il nodo corrente e ho già impostato il primo cavaliere, prendo i nodi possibili che rispettano L
            max_L += solve_rec()
        }
    }
}

int solve(int L) {
    return solve_rec(0, L);
}

int main(int argc, char** argv) {
    ifstream in("input.txt");
    ofstream out("output.txt");

    in >> N;
    G.resize(N);

    int p, a, w;
    for (int i = 0; i < N - 1; i++) {
        in >> p >> a >> w;
        G[p].push_back(arc(a, w));
        G[a].push_back(arc(p, w));
    }

    in >> K;
    L.resize(K);
    for (int i = 0; i < K; i++) {
        in >> L[i];
    }

    dist.resize(N);
    calc_dist(dist);

    for (int i = 0; i < N; i++) {
        //  cout << "Max dist foglia " << i << " = " << dist[i] << endl;
    }

    return 0;
}