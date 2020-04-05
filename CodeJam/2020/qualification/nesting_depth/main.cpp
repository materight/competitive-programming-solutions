#include <bits/stdc++.h>

using namespace std;

int main(int argc, char** argv) {
    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        string line;
        cin >> line;
        int prev = 0;
        for (int i = 0; i < line.size(); i++) {
            int next = line.at(i) - '0';
            int diff = next - prev;
            char p = diff > 0 ? '(' : ')';
            for (int i = 0; i < abs(diff); i++) cout << p;
            cout << next;
            prev = next;
        }
        for (int i = 0; i < prev; i++) cout << ')';
        cout << endl;
    }
    return 0;
}