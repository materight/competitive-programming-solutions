#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cmath>

using namespace std;

typedef vector<vector<int>> Cost;


typedef struct node{
    int x, y;
    node(int _x, int _y){
        x = _x;
        y = _y;
    }
    int dist(node n){
        return abs(x - n.x) + abs(y - n.y);
    }
}node;

int main(void)
{
    /*------------------------------------------------------------------------------------ LETTURA DATI ----------------------------------------------------------------------------------------*/

    ifstream in("input.txt");
    ofstream out("output.txt");

    int Cn, Sn;
    in >> Cn >> Sn;

    vector<node> C;
    vector<node> S;

    for(int i=0; i<Cn; i++){
        int x, y;
        in >> x >> y;
        C.push_back(node(x, y));
    } 

    for(int i=0; i<Sn; i++){
        int x, y;
        in >> x >> y;
        S.push_back(node(x, y));
    } 

    int x, y;
    in >> x >> y;
    node target = node(x, y);

    int N = Cn;
    int M = Cn + Sn - 1; 

    Cost cost(N, vector<int>(M));
    vector<int> u(N);
    vector<int> v(M);

    /*------------------------------------------------------------------------------------ ALGORITMO ----------------------------------------------------------------------------------------*/

    //  Preso da: https://github.com/t3nsor/codebook/blob/master/bipartite-mincost.cpp

    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            if(j >= Sn){
                cost[i][j] = 2 * C[i].dist(target); //  Costo dal target
            } else {
                cost[i][j] = C[i].dist(S[j]) + C[i].dist(target); //  Costo dal soldato
            }
            if(cost[i][j] < u[i]){
                u[i] = cost[i][j];  //  Costo minimo riga
            }
            if(cost[i][j] < v[j]){
                v[i] = cost[i][j];  // Costo minimo colonna
            }
        }
    }

    vector<int> L = vector<int>(N, -1);
    vector<int> R = vector<int>(M, -1);
    int matched = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (R[j] == -1 && cost[i][j] - u[i] - v[j] == 0) {
                L[i] = j;
                R[j] = i;
                matched++;
                break;
            }
        }
    }

    vector<int> dist(M);
    vector<int> parent(M);
    vector<bool> visited(M);

    // repeat until primal solution is feasible
    while (matched < M) {
        // find an unmatched left node
        int s = 0;
        while (L[s] != -1 && s < N) {
            s++;
        }
        //	Se ho già analizzato tutte le righe (componenti)
        if(s >= N) break;

        // initialize Dijkstra
        fill(parent.begin(), parent.end(), -1);
        fill(visited.begin(), visited.end(), false);
        for (int k = 0; k < M; k++) {
            dist[k] = cost[s][k] - u[s] - v[k];
        }

        int j = 0;
        while (true) {
            j = -1;
            for (int k = 0; k < M; k++) {
                if (!visited[k] && (j == -1 || dist[k] < dist[j])) {
                    j = k;
                }
            }
            visited[j] = true;

            // termination condition
            if (R[j] == -1) break;

            // relax neighbors
            int i = R[j];
            for (int k = 0; k < M; k++) {
                int new_dist = dist[j] + cost[i][k] - u[i] - v[k];
                if (!visited[k] && dist[k] > new_dist) {
                    dist[k] = new_dist;
                    parent[k] = j;
                }
            }
        }

        // update dual variables
        for (int k = 0; k < M; k++) {
            if (k != j && visited[k]) {
                int i = R[k];
                v[k] += dist[k] - dist[j];
                u[i] -= dist[k] - dist[j];
            }
        }
        u[s] += dist[j];

        // augment along path
        while (parent[j] >= 0) {
            int p = parent[j];
            R[j] = R[p];
            L[R[j]] = j;
            j = p;
        }
        R[j] = s;
        L[s] = j;
        matched++;
    }
    /*------------------------------------------------------------------------------------ SOLUZIONE ----------------------------------------------------------------------------------------*/

    int soldato_in_target = -1;
    int T = 0;
    for (int i = 0; i < Cn; i++){
        T += cost[i][L[i]];
        if(L[i] < Sn){
            soldato_in_target = L[i];
        }
    }

    out << T << endl;
    cout << T << endl;

    for (int i = 0; i < Cn; i++){
        int sold = L[i] < Sn ? L[i] : soldato_in_target;
        out << sold << endl;
    }

    return 0;
}