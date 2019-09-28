#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main(int argc, char** argv) {
    int T;
    cin >> T;

    for (int t = 0; t < T; t++) {
        int N, B, F;
        cin >> N >> B >> F;

        int Ndiv = 2;

        vector<vector<int>> broken(N, vector<int>(N, 0));
        broken[0][N - 1] = B;

        for (Ndiv = 1; (N / Ndiv) > 1; Ndiv *= 2) {
            int range = (N / Ndiv);
            cerr << "Numero sottoproblemi: " << Ndiv << ", range: " << range << endl;

            //  Output
            for (int s = 0, e = range - 1; e < N; s += range, e += range) {  //  Per ogni sottoproblema di dimensione "range", tra [s, e)
                int m = (s + e) / 2;
                for (int i = s; i <= e; i++) {
                    cout << (i <= m ? 0 : 1);
                }
            }
            cout << endl;

            //  Lettura risposta
            queue<int> resp;
            char c;
            for (int i = 0; i < N - B; i++) {
                cin >> c;
                resp.push(c == '0' ? 0 : 1);
            }

            int last_resp = 0;
            for (int s = 0, e = range - 1; e < N; s += range, e += range) {
                cerr << "Analizzo sottoproblema [" << s << "," << e << "]: " << endl;
                int Wl = 0, Wr = 0;  //  Numero lavoratori funzionanti a sx e dx
                cerr << "\tCi sono " << (e - broken[s][e] + 1 - s) << " elementi non broken: ";
                for (int i = s; i < e - broken[s][e] + 1; i++) {
                    if (resp.front() == 0)
                        Wl++;
                    else
                        Wr++;
                    cerr << resp.front() << " ";
                    resp.pop();
                }
                cerr << endl;
                int m = (s + e) / 2;
                broken[s][m] = (m - s + 1) - Wl;
                broken[m + 1][e] = (e - (m + 1) + 1) - Wr;
                cerr << "\tBroken DX [" << s << "," << m << "] = " << broken[s][m] << endl;
                cerr << "\tBroken SX [" << m + 1 << "," << e << "] = " << broken[m + 1][e] << endl;
            }
        }
        for (int i = 0; i < N; i++) {
            if (broken[i][i] > 0) {
                cout << i << " ";
            }
        }
        cout << endl;
    }
    return 0;
}