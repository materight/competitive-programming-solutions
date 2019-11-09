#include <bits/stdc++.h>

#define MAXN 50100

using namespace std;

typedef long long int ll;

int N;
vector<int> children[MAXN];
int w[MAXN];
ll sum[MAXN];
ll inc = 0;

void calc(int s) {
    ll maxw = 0;
    // Trovo il pillar con W massimo
    for (int v : children[s]) {
        calc(v);
        maxw = max(maxw, sum[v]);
    }

    // Incremento tutti i pillar per rispettare le condizioni
    for (int v : children[s]) {
        inc += maxw - sum[v];
        w[v] = maxw;
    }
    sum[s] = (maxw * children[s].size()) + w[s];
}

int main(int argc, char** argv) {
    cin >> N;
    for (int i = 1; i < N; i++) {
        int p;
        cin >> p >> w[i];
        children[p].push_back(i);
    }

    calc(0);

    cout << inc << endl;

    return 0;
}