//#include "tsp.h"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int>> graph;

#define START 0

int minSolCost = INT32_MAX;
vector<int> minSol;

void print_soluz(ofstream &out) {
    for (int i = 0; i < minSol.size() - 1; i++) {
        out << minSol[i] << " ";
    }
    out << minSol[minSol.size() - 1] << "#" << endl;
}

void calc_greedy(graph &G) {
    int N = G.size();
    int s = START;
    vector<bool> visited(N, false);
    minSol[0] = START;
    minSolCost = 0;
    for (int i = 0; i < N; i++) {
        int min_pos = -1;
        // Trovo l'arco con costo minore tra quelli adiacenti
        for (int j = 0; j < N; j++) {
            if (!visited[j] && (min_pos == -1 || G[s][j] < G[s][min_pos])) {
                min_pos = j;
            }
        }
        minSolCost += G[s][min_pos];
        s = min_pos;
        minSol[i] = min_pos;
        visited[min_pos] = true;
    }
    minSolCost += G[s][START];
    minSol[N] = START;
}

void local_search(graph &G, ofstream &out) {
    int N = G.size();
    for (int i = 0; i < N - 1; i++) {
        for (int j = i + 2; j < N - 1; j++) {
            //Scambio (i, i+1) e (j, j+1) facendoli diventare (i, j+1) e (j, i+1)
            int cost = minSolCost;
            cost -= (G[minSol[i]][minSol[i + 1]] + G[minSol[j]][minSol[j + 1]]);  //  Tolgo vecchi costi
            cost += (G[minSol[i]][minSol[j]] + G[minSol[i + 1]][minSol[j + 1]]);  //  Aggiungo nuovi costi
            if (cost < minSolCost) {
                minSolCost = cost;
                vector<int> oldSol = minSol;
                //minSol[i + 1] = oldSol[j];
                int c = 0;
                while (c < j - i) {
                    minSol[i + 1 + c] = oldSol[j - c];
                    c++;
                }
                minSol[j] = oldSol[i + 1];
                print_soluz(out);
                // Riparto da 0
                int calc_cost = 0;
                for (int i = 0; i < N - 1; i++) {
                    calc_cost += G[minSol[i]][minSol[i + 1]];
                }
                calc_cost += G[minSol[N - 1]][minSol[0]];
                i = 0;
                j = i + 1;
            }
        }
    }
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    int N;
    in >> N;

    vector<vector<int>> G(N, vector<int>(N));
    minSol.resize(N + 1, -1);

    G[0][0] = 0;
    for (int i = 1; i < N; i++) {
        for (int j = 0; j < i; j++) {
            in >> G[i][j];
            G[j][i] = G[i][j];
        }
        G[i][i] = 0;
    }

    calc_greedy(G);
    print_soluz(out);
    local_search(G, out);

    return 0;
}