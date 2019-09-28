#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int T;
    scanf("%d\n", &T);
    for (int tc = 1; tc <= T; tc++) {
        int D;
        string P;
        cin >> D >> P;

        vector<int> shoots;
        int dmg = 0, charge = 1;
        for (char c : P) {
            if (c == 'S') {
                shoots.push_back(charge);
                dmg += charge;
            } else if (c == 'C') {
                charge *= 2;
            }
        }

        int swaps = 0;
        int idx = shoots.size() - 1;
        while (dmg > D) {
            if (idx < 0 && charge == 1) break;
            while (idx < 0 || shoots[idx] < charge) {
                charge = charge / 2;
                idx = shoots.size() - 1;
            }
            shoots[idx] = shoots[idx] / 2;
            idx--;
            dmg -= charge / 2;
            swaps++;
        }
        if (dmg > D)
            printf("Case #%d: IMPOSSIBLE\n", tc);
        else
            printf("Case #%d: %d\n", tc, swaps);
    }
    return 0;
}