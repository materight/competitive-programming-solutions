#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

typedef long long int ll;

int main(int argc, char** argv) {
    int N, M;
    cin >> N >> M;

    vector<ll> S(N), E(M);

    for (int i = 0; i < N; i++) cin >> S[i];
    for (int i = 0; i < M; i++) cin >> E[i];

    unordered_map<ll, ll> res;

    ll min_interval = 0, max_occurences = -1;

    for (int s = 0; s < N; s++) {
        for (int e = 0; e < M; e++) {
            if (E[e] >= S[s]) {
                ll interval = E[e] - S[s];
                res[interval]++;
                ll occurences = res[E[e] - S[s]];
                if (occurences == max_occurences && interval < min_interval) {
                    min_interval = interval;
                } else if (occurences > max_occurences) {
                    min_interval = interval;
                    max_occurences = occurences;
                }
            }
        }
    }
    cout << min_interval << endl;
    return 0;
}