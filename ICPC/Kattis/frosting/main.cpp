#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char** argv) {
    int N;
    cin >> N;

    vector<int> A(N), B(N);

    for (int i = 0; i < N; i++) cin >> A[i];
    for (int i = 0; i < N; i++) cin >> B[i];

    vector<long long int> C(3, 0);

    //  Collasso le B in un'unica riga per colore
    for (int i = 0; i < N; i++) {
        C[((i + 1) + (0 + 1)) % 3] += B[i];
    }

    vector<long long int> sum(3, 0);
    for (int c = 0; c < 3; c++) {
        for (int i = 0; i < N; i++) {
            sum[(c + i) % 3] += C[c] * A[i];
        }
    }
    cout << sum[0] << " " << sum[1] << " " << sum[2] << endl;
    return 0;
}