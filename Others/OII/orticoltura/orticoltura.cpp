#include <algorithm>
#include <vector>
#include "grader.cpp"

using namespace std;

void posiziona(int D, int T);

void budget(int B);

typedef struct seed {
    int i, x, p;
    seed() : seed(-1, -1, -1){};
    seed(int _i, int _x, int _p) : i(_i), x(_x), p(_p){};
    bool operator<(const seed& s) const {
        if (x == s.x) return p > s.p;
        return x < s.x;
    }
} seed;

typedef struct irr {
    int x, t;
    irr(int _x, int _t) : x(_x), t(_t){};
} irr;

void irriga(int C, int N, vector<int>& X, vector<int>& P) {
    vector<seed> seeds(N);
    for (int i = 0; i < N; i++) {
        seeds[i] = seed(i, X[i], P[i]);
    }

    sort(seeds.begin(), seeds.end());

    int tot = 0;
    irr last_irr = irr(-1, -1);

    for (seed s : seeds) {
        if (last_irr.x == -1) {
            // Primo irrigatore sopra il primo seme
            last_irr = irr(s.x, s.p);
            tot += C + s.p;
        } else if (last_irr.x == s.x) {
            // Ultimo irrigatore sopra il seme, aumento solo t SE serve.
            // Se t > p, il seme è già coperto dall'irrigatore, quindi non faccio niente
            if (last_irr.t < s.p) {
                tot += (s.p - last_irr.t);
                last_irr.t = s.p;
            }
        } else {
            int new_cost = C + s.p;  // Costo creazione nuovo irrigatore sopra seme

            int last_x_shift = (((last_irr.x - last_irr.t) + (s.x + s.p)) / 2) - last_irr.x;  // Spostamento ultimo irrigatore
            int last_cost = last_x_shift;                                                     // Costo spostamento ultimo irrigatore
            if (last_cost < new_cost) {
                // Sposto l'ultimo irrigatore per includere il seme
                last_irr.x += last_x_shift;
                last_irr.t += last_x_shift;
                tot += last_cost;
            } else {
                // Posiziono l'ultimo irrigatore creato
                posiziona(last_irr.x, last_irr.t);

                // Creo nuovo irrigatore sopra il seme
                last_irr = irr(s.x, s.p);
                tot += new_cost;
            }
        }
    }
    posiziona(last_irr.x, last_irr.t);
    budget(tot);
}
