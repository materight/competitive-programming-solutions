#include <bits/stdc++.h>

using namespace std;

int main(int argc, char** argv) {
    int W, N;
    cin >> W >> N;

    int area = 0, w, l;
    for (int i = 0; i < N; i++) {
        cin >> w >> l;
        area += (w * l);
    }

    cout << area / W << endl;

    return 0;
}