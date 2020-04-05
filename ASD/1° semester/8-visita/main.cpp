#include <deque>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char** argv)
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    int N, M, S;
    in >> N;
    in >> M;
    in >> S;

    vector<vector<int>> grafo(N);
    vector<bool> visited(N);

    for (int i = 0; i < M; i++) {
        int n1, n2;
        in >> n1;
        in >> n2;
        grafo[n1].push_back(n2);
    }

    int result = 0;
    deque<int> coda;
    coda.push_back(S);
    while (!coda.empty()) {
        int current = coda.front();
        coda.pop_front();
        if (!visited[current]) {
            result++;
            visited[current] = true;
            coda.insert(coda.end(), grafo[current].begin(), grafo[current].end());
        }
    }
    out << result;

    return 0;
}