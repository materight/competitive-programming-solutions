#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

void swap(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}

void trouble_sort(vector<int>& L) {
    bool done = false;
    while (!done) {
        done = true;
        for (int i = 0; i < L.size() - 2; i++) {
            if (L[i] > L[i + 2]) {
                done = false;
                swap(L[i], L[i + 2]);
            }
        }
    }
}

int is_ordered(vector<int>& L_pari, vector<int>& L_disp, int N) {
    for (int i = 0; i < N - 1; i++) {
        if (i % 2 == 0) {
            if (L_pari[i / 2] > L_disp[i / 2]) {
                return i;
            }
        } else {
            if (L_disp[i / 2] > L_pari[(i / 2) + 1]) {
                return i;
            }
        }
    }
    return -1;
}

main(int argc, char** argv) {
    int T;
    cin >> T;
    for (int t = 0; t < T; t++) {
        int N, val;
        scanf("%d\n", &N);

        int Ndisp = N / 2;
        vector<int> L_disp(Ndisp), L_pari(N - Ndisp);

        for (int i = 0; i < N; i++) {
            scanf("%d ", &val);
            if (i % 2 == 0) {
                L_pari[i / 2] = val;
            } else {
                L_disp[i / 2] = val;
            }
        }
        sort(L_disp.begin(), L_disp.end());
        sort(L_pari.begin(), L_pari.end());

        //trouble_sort(L);
        // cout << "result: ";
        // for (int i = 0; i < N; i++) {
        //     if (i % 2 == 0) {
        //         cout << L_pari[i / 2] << " ";
        //     } else {
        //         cout << L_disp[i / 2] << " ";
        //     }
        // }
        //cout << endl;
        int res = is_ordered(L_pari, L_disp, N);
        if (res == -1) {
            printf("Case #%d: OK\n", t + 1);
        } else {
            printf("Case #%d: %d\n", t + 1, res);
        }
    }

    return 0;
}