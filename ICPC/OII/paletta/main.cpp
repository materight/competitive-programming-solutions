#include <bits/stdc++.h>
#include "grader.cpp"

#define MAXN 1500000

using namespace std;

typedef long long ll;

int fenP[MAXN], fenD[MAXN];
int W[MAXN];

int lsb(int i) {
    return i & (-i);
}

int sum(int i, int fen[]) {
    int res = 0;
    while (i > 0) {
        res += fen[i];
        i -= lsb(i);
    }
    return res;
}

void add(int i, int fen[], int N) {
    while (i <= N) {
        fen[i]++;
        i += lsb(i);
    }
}

ll paletta_sort(int N, int V[]) {
    ll moves = 0;
    for (int i = 0; i < N; i++) W[V[i]] = i;
    for (int i = N - 1; i >= 0; i--) {
        if (V[i] % 2 != i % 2) {
            return -1;
        } else {
            int *fen = (i % 2 == 0) ? fenP : fenD;
            moves += (ll)sum(W[i] / 2 + 1, fen);
            add(W[i] / 2 + 1, fen, N);
        }
    }

    return moves;
}
