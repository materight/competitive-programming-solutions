#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

typedef vector<vector<int>> graph;

typedef struct _int {
    int v = -1;
} _int;

void erdos(graph &G, vector<int> &dist, int e) {
    queue<int> q;
    q.push(e);
    dist[e] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : G[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
}

int main(int argc, char **argv) {
    unordered_map<string, _int> authors;
    vector<pair<int, string>> nodi;  //  Per avere i nodi in ordine di lettura per la stampa
    graph G;

    string a;     //  Autore corrente
    string coll;  // Collaboratore
    int a_v, coll_v;
    while (cin >> a) {
        a_v = authors[a].v;
        //  Se non ho ancora inserito questo autore lo aggiungo al map
        if (a_v == -1) {
            authors[a].v = a_v = G.size();
            G.push_back(vector<int>());
        }

        nodi.push_back({a_v, a});
        while (cin.peek() != 13 && cin.peek() != 10) {  //  Fino al \n (con '\n' non funziona)
            cin >> coll;
            coll_v = authors[coll].v;
            //  Se non ho ancora inserito questo autore lo aggiungo al map
            if (coll_v == -1) {
                authors[coll].v = coll_v = G.size();
                G.push_back(vector<int>());
            }
            G[a_v].push_back(coll_v);
            G[coll_v].push_back(a_v);
        }
    }

    int N = G.size();
    vector<int> dist(N, -1);
    erdos(G, dist, authors["PAUL_ERDOS"].v);

    for (auto n : nodi) {
        if (dist[n.first] == -1) {
            cout << n.second << " no-connection" << endl;
        } else {
            cout << n.second << " " << dist[n.first] << endl;
        }
    }

    return 0;
}