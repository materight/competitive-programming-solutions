#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

typedef vector<vector<int>> graph;

void solve(graph& G, vector<string>& itos) {
    int N = G.size();

    vector<int> color(N, -1);
    vector<int> walter, jesse;
    queue<int> q;

    for (int i = 0; i < N; i++) {
        if (color[i] == -1) {
            color[i] = 0;
            walter.push_back(i);
            q.push(i);
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                int c = color[u];
                for (int v : G[u]) {
                    if (color[v] == -1) {
                        color[v] = 1 - c;
                        if (color[v] == 0)
                            walter.push_back(v);
                        else
                            jesse.push_back(v);
                        q.push(v);
                    } else if (color[v] == c) {
                        cout << "impossible" << endl;
                        exit(0);
                    }
                }
            }
        }
    }
    for (int v : walter) {
        cout << itos[v] << " ";
    }
    cout << endl;
    for (int v : jesse) {
        cout << itos[v] << " ";
    }
    cout << endl;
}

int main(int argc, char** argv) {
    int N, M;
    cin >> N;

    graph G(N);
    unordered_map<string, int> stoi;
    vector<string> itos(N);

    string s;
    for (int i = 0; i < N; i++) {
        cin >> s;
        stoi[s] = i;
        itos[i] = s;
    }

    cin >> M;
    string s1, s2;
    for (int i = 0; i < M; i++) {
        cin >> s1 >> s2;
        G[stoi[s1]].push_back(stoi[s2]);
        G[stoi[s2]].push_back(stoi[s1]);
    }

    solve(G, itos);

    return 0;
}