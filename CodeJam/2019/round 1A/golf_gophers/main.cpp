#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    int T, N, M;
    cin >> T >> N >> M;

    for (int t = 0; t < T; t++) {
        int G;

        //  Per il teorema cinese del resto
        int a = -1, n = -1, b = -1, m = -1;

        for (int i = 0; i < N; i++) {
            //  OUTPUT
            for (int b = 0; b < 18; b++) {
                cout << 18 << " ";
            }
            cout << endl;

            //  INPUT
            int sum = 0;
            for (int b = 0; b < 18; b++) {
                int res;
                cin >> res;
                sum += res;
            }
            if (sum == G) {
                break;  //    Usciamo dal for e stampiamo la risposta
            } else {
                G = sum;
            }
        }
        cout << G << endl;
        int response;
        cin >> response;
        if (response == -1) {
            cout << "Wrong answer" << endl;
            return 0;
        }
    }
    return 0;
}