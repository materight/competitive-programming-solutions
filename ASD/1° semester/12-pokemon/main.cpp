#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

typedef vector<vector<int>> graph;

int cycle_size(graph *_G){
	vector<int> dist(N, INT_MAX);
	dist[0] = 0;
	return cycle_size_dfs(_G, 0, &dist):
}

int cycle_size_dfs(graph *_G, int u, vector<int> *_dist){
	graph& G = *_G;
	vector<int>& dist = *_dist;

	for(int i=0; i<G[u].size(); i++){
		if(dist[v] == INT_MAX){
			dist[v] = dist[u];
		}
	}

	return 0;
}

int main(int argc, char** argv) {
	ifstream in("input.txt");
	ofstream out("output.txt");

	int N, M;
	in >> N >> M;

	graph G(N);
	for(int i=0; i<M; i++){
		int n1, n2;
		in >> n1 >> n2;
		G[n1].push_back(n2);
		G[n2].push_back(n1);
	}

	int c_size = cycle_size(&G);
	cout << c_size;
	out << c_size;

	return 0;
}