#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char** argv) {
    int T;
    cin >> T;

    for (int t = 0; t < T; t++) {
        int A;
        cin >> A;

        vector<string> C(A);

        int max_length = 0;
        for (int i = 0; i < A; i++) {
            cin >> C[i];
            max_length = max(max_length, (int)C[i].length());
        }

        string result = "";

        for (int i = 0; i < max_length; i++) {
            bool R = false, P = false, S = false;
            for (int c = 0; c < A; c++) {
                int pos = i % C[c].length;
            }
        }
    }
    return 0;
}