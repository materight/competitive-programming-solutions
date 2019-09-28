#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char** argv) {
    int T;
    cin >> T;

    for (int t = 0; t < T; t++) {
        int N, K;
        cin >> N >> K;

        vector<int> C(N);
        vector<int> D(N);

        for (int i = 0; i < N; i++) cin >> C[i];
        for (int i = 0; i < N; i++) cin >> D[i];

        int count = 0;

        for (int s = 0; s < N; s++) {
            int maxC = s;
            int maxD = s;
            for (int e = s; e < N; e++) {
                if (C[e] > C[maxC]) maxC = e;
                if (D[e] > D[maxD]) maxD = e;
                if (abs(C[maxC] - D[maxD]) <= K) {
                    count++;
                }
            }
        }

        cout << "Case #" << (t + 1) << ": " << count << endl;
    }
    return 0;
}