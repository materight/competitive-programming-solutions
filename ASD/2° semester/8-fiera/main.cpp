#include <climits>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int N;  //  Numero di paesi
int K;  //  Numero di castelli

typedef struct sentiero {
    int n;  //  nodo
    int t;  //  costo
    sentiero(int _n, int _t) {
        n = _n;
        t = _t;
    }
} sentiero;

typedef vector<vector<sentiero>> Graph;

vector<int> B;  //  Numero barili rihiesti dall'i-esimo paese
Graph G;        //  Sentieri, 0 = castello

/**
 * p = paese 
 * t = tempo fino al paese p
 * k = castelli rimanenti 
 **/
int solve_rec(int p, int t, int k) {
    if (p >= N) return 0;

    cout << p << " " << t << " " << k << endl;
    int tot_no_castello = t * B[p];
    int tot_castello = k > 0 ? 0 : INT_MAX;
    for (int i = 0; i < G[p].size(); i++) {
        tot_no_castello += solve_rec(G[p][i].n, t + G[p][i].t, k);
        if (k > 0) {
            tot_castello += solve_rec(G[p][i].n, G[p][i].t, k - 1);
        }
    }
    cout << p << ": tot_no_castello = " << tot_no_castello << ", tot_castello = " << tot_castello << endl;
    return min(tot_no_castello, tot_castello);
}

int solve() {
    return solve_rec(0, 0, K);
}

int main(int argc, char** argv) {
    ifstream in("dataset/input/input0.txt");
    ofstream out("output.txt");

    in >> N >> K;

    B.resize(N);
    G.resize(N);

    for (int i = 0; i < N; i++) {
        in >> B[i];
    }

    int S, D, T;
    for (int i = 0; i < N - 1; i++) {
        in >> S >> D >> T;
        G[S].push_back(sentiero(D, T));
    }

    int soluz = solve();
    out << soluz << endl;
    cout << soluz << endl;

    return 0;
}