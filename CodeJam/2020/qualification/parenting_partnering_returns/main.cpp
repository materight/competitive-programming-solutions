#include <bits/stdc++.h>

using namespace std;

typedef struct intv {
    int s, e, i;
} intv;

int main(int argc, char** argv) {
    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        int N;
        cin >> N;
        vector<intv> A(N);
        for (int i = 0; i < N; i++) {
            cin >> A[i].s >> A[i].e;
            A[i].i = i;
        }

        sort(A.begin(), A.end(), [](intv a, intv b) { return a.s < b.s; });

        vector<char> assign(N);
        int endC = 0;
        int endJ = 0;

        bool possible = true;
        for (int i = 0; i < N && possible; i++) {
            if (A[i].s >= endC) {
                assign[A[i].i] = 'C';
                endC = A[i].e;
            } else if (A[i].s >= endJ) {
                assign[A[i].i] = 'J';
                endJ = A[i].e;
            } else
                possible = false;
        }
        cout << "Case #" << t << ": ";
        if (!possible)
            cout << "IMPOSSIBLE";
        else
            for (char c : assign) cout << c;
        cout << endl;
    }
    return 0;
}