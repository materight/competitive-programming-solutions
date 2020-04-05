#include <bits/stdc++.h>

using namespace std;

int N, P;

typedef struct radar {
    int x, y, r;
} radar;

typedef struct point {
    int x, y;
    point(int _x, int _y) : x(_x), y(_y){};
    vector<point> adj() {
        vector<point> res;
        if (x < N - 1) res.push_back(point(x + 1, y));
        if (y < N - 1) res.push_back(point(x, y + 1));
        if (x > 0) res.push_back(point(x - 1, y));
        if (y > 0) res.push_back(point(x, y - 1));
        return res;
    }
    int dist(int _x, int _y) { return abs(x - _x) + abs(y - _y); }
} point;

int D[500][500];          // Distanze minime
vector<int> M[500][500];  // Radar raggiunti da una certa cella
vector<radar> R;          // Radars

int lcm(int a, int b) {
    return a * (b / __gcd(a, b));
}

//TODO: usare priority_queue
void bfs(int x, int y) {
    queue<point> Q;
    Q.push(point(x, y));
    D[x][y] = 0;

    while (!Q.empty()) {
        point u = Q.front();
        Q.pop();
        int t = D[u.x][u.y];  // Tempo impegato per arrivare a u
        for (point v : u.adj()) {
            int d = 1;
            bool found = false;
            // Calcolo days richiesti per andare nella cella nel caso sia raggiunta da qualche radar. Cella libera sse (t mod raggio_radar) < dist_radar
            if (!M[v.x][v.y].empty()) {
                int mcm = 1;  // Rappresenta ogni quanto si ripete il ciclo di finestre di passaggio libere
                for (int i : M[v.x][v.y]) {
                    mcm = lcm(mcm, R[i].r);
                }
                d = 1;
                while (!found) {
                    int turno = 0;
                    radar first = R[M[v.x][v.y][0]];
                    int durata = v.dist(first.x, first.y);
                    d = (first.r - (t % first.r)) * turno;  // Provo con le finestre dispobinibili per il radar fino a quando non ne trovo una che va bene
                    if (d < mcm) {
                        found = true;
                        for (int i : M[v.x][v.y]) {
                            if (i != M[v.x][v.y][0]) {
                                // Test se il turno preso non va bene
                                if ((t + d) % R[i].r >= v.dist(R[i].x, R[i].y)) {
                                    found = false;
                                    break;
                                }
                            }
                        }
                    } else {
                        break;
                    }
                    turno++;
                }
            } else {
                found = true;
            }

            if (t + d < D[v.x][v.y]) {
                if (found) {
                    D[v.x][v.y] = t + d;
                } else {
                    D[v.x][v.y] = INT_MAX;
                }
                Q.push(v);
            }
        }
    }
}

void initM(int x, int y, int r, int id) {
    // Per ogni cella M inserisco quando sarà coperta dal radar
    r--;  // Non considero il centro nel raggio
    for (int i = -r; i <= r; i++) {
        int d = (r - abs(i));  // Distanza della riga che sto analizzando dal centro
        for (int j = -d; j <= d; j++) {
            if (x + i >= 0 && x + i < N && y + j >= 0 && y + j < N) {
                M[x + i][y + j].push_back(id);
            }
        }
    }
}

int main(int argc, char** argv) {
    freopen("input.txt", "r", stdin);

    cin >> N >> P;

    R.resize(P);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            D[i][j] = INT_MAX;
        }
    }

    for (int i = 0; i < P; i++) {
        cin >> R[i].x >> R[i].y >> R[i].r;
        R[i].x--;
        R[i].y--;
        initM(R[i].x, R[i].y, R[i].r, i);
    }

    bfs(0, 0);

    cout << D[N - 1][N - 1] << endl;

    return 0;
}