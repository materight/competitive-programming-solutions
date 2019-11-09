#include <bits/stdc++.h>

#define MAXN 65600

using namespace std;

typedef pair<int, int> pi;

int N;
int A[MAXN], B[MAXN];

int main(int argc, char** argv) {
    cin >> N;
    priority_queue<pi, vector<pi>, less<pi>> q;
    for (int i = 0; i < N; i++) {
        cin >> A[i] >> B[i];
        q.push(pi(A[i], i));
    }

    int n = N;  // Numero di atleti ancora in pista
    queue<pi> tmp;
    while (n > 1) {
        // Aggiornamento distanza raggiunta dopo 1 min
        for (int i = 0; i < n; i++) {
            pi a = q.top();
            q.pop();
            tmp.push(make_pair(a.first + B[a.second], a.second));
        }

        while (!tmp.empty()) {
            q.push(tmp.front());
            tmp.pop();
        }
        n /= 2;
    }

    cout << q.top().second << endl;

    return 0;
}