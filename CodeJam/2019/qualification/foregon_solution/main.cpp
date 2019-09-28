#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    int T;
    cin >> T;

    for (int t = 0; t < T; t++) {
        string N;
        cin >> N;

        int A = 0, B = 0;
        for (char c : N) {
            int n = c - 48;
            A *= 10;
            B *= 10;
            if (c == '4') {
                A += n - 1;
                B += 1;
            } else {
                A += n;
            }
        }
        cout << "Case #" << t + 1 << ": " << A << " " << B << endl;
    }
    return 0;
}