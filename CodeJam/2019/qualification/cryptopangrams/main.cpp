#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

typedef unsigned long long int ulli;

//  Algoritmo di Euclide + rapido
ulli mcd(ulli a, ulli b) {
    if (a == 0) return b;
    if (b == 0) return a;

    int shift = __builtin_ctz(a | b);
    a >>= __builtin_ctz(a);
    do {
        b >>= __builtin_ctz(b);
        if (a > b) std::swap(a, b);
        b -= a;
    } while (b);
    return a << shift;
}

int main(int argc, char** argv) {
    int T;
    cin >> T;

    for (int t = 0; t < T; t++) {
        int L;
        string N;
        cin >> N >> L;

        vector<ulli> msg(L + 10);
        vector<ulli> msg_copy(L + 1);
        map<ulli, char> alphabet;

        cin >> msg[0] >> msg[2];  //  Leggo i primi 2 prodotti
        msg_copy[1] = msg[1] = mcd(msg[0], msg[2]);
        msg_copy[0] = msg[0] = msg[0] / msg[1];
        msg_copy[2] = msg[2] = msg[2] / msg[1];
        for (int i = 3; i <= L; i++) {
            cin >> msg[i];
            msg_copy[i] = msg[i] = msg[i] / msg[i - 1];
        }
        sort(msg_copy.begin(), msg_copy.end());
        alphabet[msg_copy[0]] = 'A';
        for (int i = 1; i <= L; i++) {
            if (msg_copy[i] != msg_copy[i - 1]) {
                alphabet[msg_copy[i]] = (char)(alphabet[msg_copy[i - 1]] + 1);
            }
        }

        cout << "Case #" << (t + 1) << ": ";
        for (ulli x : msg) {
            cout << alphabet[x];
        }
        cout << endl;
    }
    return 0;
}