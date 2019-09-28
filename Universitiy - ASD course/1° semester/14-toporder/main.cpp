#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void ts_dfs(vector<vector<int>> *_G, int u, vector<bool> *_visited, vector<int> *S){
	vector<vector<int>>& G = *_G;
	vector<bool>& visited = *_visited;
	
	visited[u] = true;
	for(int i = 0; i<G[u].size(); i++){
		int v = G[u][i];
		if(!visited[v]){
			ts_dfs(&G, v, &visited, S);
		}
	}
	S->push_back(u);
}

vector<int> top_sort(vector<vector<int>> *G){
	vector<int> S;
	vector<bool> visited(G->size());
	for(int u = 0; u<G->size(); u++){
		if(!visited[u]){
			ts_dfs(G, u, &visited, &S);
		}
	}
	return S;
}


int main(int argc, char** argv) {
	ifstream in("input.txt");
	ofstream out("output.txt");

	int N, M;
	in >> N >> M;

	vector<vector<int>> G(N);

	for(int i=0; i<M; i++){
		int n1, n2;
		in >> n1 >> n2;
		G[n1].push_back(n2);
	}

	vector<int> res = top_sort(&G);
	for(int i = res.size() - 1; i >= 0; i--){
		out << res[i] << " ";
	}
	return 0;
}