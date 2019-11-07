#include <bits/stdc++.h>
#include "grader.cpp"

using namespace std;

typedef long long int ll;

ll percorri(int N, ll L, ll D[], ll P[]) {
    ll C = 0;
    ll left = L;
    ll Ds = 0, Ps = 0;  // Valori D e P dell'ultima spiaggia presa
    stack<int> took;
    for (int i = 0; i < N; i++) {
        ll m1 = (D[i] - Ds) + P[i] + Ps;  // Prima metà
        ll m2 = (L - D[i]) + P[i];        // Seconda metà
        if (m1 < left && m2 < left) {
            left = m2;
            C = max(m1, C);
            Ds = D[i];
            Ps = P[i];
            took.push(i);
            if (i == N - 1) C = max(m2, C);
        } else if (i == N - 1) {
            C = max(left, C);
        }
    }

    return C;
}
