#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char** argv) {
    int N;
    cin >> N;

    vector<int> cans(N);
    vector<int> balloons(N);

    for (int i = 0; i < N; i++) {
        cin >> cans[i];
    }

    sort(cans.begin(), cans.end());

    bool impossible = false;
    float min_fill = 1;
    for (int i = 0; i < N; i++) {
        if (cans[i] > i + 1) {
            impossible = true;
            break;
        } else {
            min_fill = min(min_fill, (float)cans[i] / (i + 1));
        }
    }
    if (impossible) {
        cout << "impossible" << endl;
    } else {
        cout << min_fill << endl;
    }

    return 0;
}