#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    int T, A;
    cin >> T;

    for (int t = 0; t < T; t++) {
        cin >> A;
        int I = 300, J = 300;
        int sI = I, sJ = J;  //  Punto di inizio del rettangolo
        int eI, eJ;          //  Punto di fine del rettangolo
        int Ip, Jp;
        do {
            cout << I << " " << J << endl;
            cin >> Ip >> Jp;
        } while ((Ip != 0 && Jp != 0) || (Ip != -1 && Jp != -1));
        //TODO: error handling
    }

    return 0;
}