#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

void erdos_dfs(vector<vector<int>> *G, int u, vector<int> *erdos, int *max){
	for(int i=0; i<(*G)[u].size(); i++){
		int v = (*G)[u][i];
		if((*erdos)[v] == INT_MAX || (*erdos)[v] < (*erdos)[u] + 1){
			(*erdos)[v] = (*erdos)[u] + 1;
			if((*erdos)[v] > *max){
				*max = (*erdos)[v];
			}
			erdos_dfs(G, v, erdos, max);
		}
	}
}

int main(int argc, char** argv) {
	ifstream in("input.txt");
	ofstream out("output.txt");

	int N, M;
	in >> N >> M;

	vector<vector<int>> G(N);

	for(int i=0; i<M; i++){
		int t, s;
		in >> t >> s;
		G[t].push_back(s);
	}

	int cammino_max = 0;

	//	BFS
	/*for(int start = 0; start < N; start++){
		queue<int> coda;
		coda.push(start);
		vector<int> erdos(N, INT_MAX);
		erdos[start] = 0;

		while(!coda.empty()){
			int u = coda.front();
			coda.pop();
			for(int j = 0; j<G[u].size(); j++){
				int v = G[u][j];
				if(erdos[v] == INT_MAX || erdos[v] < erdos[u] + 1){
					erdos[v] = erdos[u] + 1;
					if(erdos[v] > cammino_max){
						cammino_max = erdos[v];
					}
					coda.push(v);
				}
			}
		}
	}*/

	//	DFS
	for(int start = 0; start < N; start++){
		vector<int> erdos(N, INT_MAX);
		erdos[start] = 0;
		erdos_dfs(&G, start, &erdos, &cammino_max);
	}


	out << cammino_max;
	cout << cammino_max << endl;

	return 0;
}