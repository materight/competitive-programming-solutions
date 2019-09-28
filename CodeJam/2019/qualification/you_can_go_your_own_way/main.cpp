#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    int T;
    cin >> T;

    for (int t = 0; t < T; t++) {
        int N;
        scanf("%d ", &N);
        int M = 2 * N - 2;  //  Lunghezza percorso

        char l;
        cout << "Case #" << t + 1 << ": ";
        for (int i = 0; i < M; i++) {
            l = getchar_unlocked();
            cout << (l == 'E' ? 'S' : 'E');
        }
        cout << endl;
    }

    return 0;
}