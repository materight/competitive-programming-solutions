#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <climits>

using namespace std;

int main(int argc, char** argv) {
	ifstream in("input.txt");
	ofstream out("output.txt");

	int N, M, S, T;
	in >> N >> M >> S >> T;

	vector<vector<int>> G(N);
	
	for(int i=0; i<M; i++){
		int n1,n2;
		in >> n1 >> n2;
		G[n1].push_back(n2);
	}

	//	ALGORITMO
	vector<int> erdos(G.size(), INT_MAX);
	vector<int> times(G.size());

	deque<int> coda;
	coda.push_back(S);

	erdos[S] = 0;
	times[S] = 1;

	while(!coda.empty()){
		int u = coda.front();
		coda.pop_front();

		for(int i=0; i<G[u].size(); i++){
			int v = G[u][i];
			if(erdos[v] == INT_MAX){
				erdos[v] = erdos[u] + 1;
				coda.push_back(v);
			}
			if(erdos[v] == erdos[u] + 1) {
				//	Ogni volta che ripasso sullo stesso nodo incremento times
				times[v]+= times[u];
			}
		}
	}

	cout << erdos[T] << " " << times[T];
	out << erdos[T] << " " << times[T];
	return 0;
}