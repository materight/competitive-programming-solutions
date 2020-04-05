#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;

typedef vector<vector<int>> graph;

void ts_dfs(graph *_G, int u, vector<bool> *_visited, stack<int> *S){
	graph& G = *_G;
	vector<bool>& visited = *_visited;
	
	visited[u] = true;
	for(int i = 0; i<G[u].size(); i++){
		int v = G[u][i];
		if(!visited[v]){
			ts_dfs(&G, v, &visited, S);
		}
	}
	S->push(u);
}

stack<int> top_sort(graph *G){
	stack<int> S;
	vector<bool> visited(G->size());
	for(int u = 0; u<G->size(); u++){
		if(!visited[u]){
			ts_dfs(G, u, &visited, &S);
		}
	}
	return S;
}

graph transpose(graph *G){
	graph GT(G->size());
	for(int u = 0; u<G->size(); u++){
		for(int i = 0; i<(*G)[u].size(); i++){
			int v = (*G)[u][i];
			GT[v].push_back(u);
		}
	}
	return GT;
}

void cc_dfs(graph *_G, int counter, int u, vector<int> *_id){
	graph& G = *_G;
	vector<int>& id = *_id;

	id[u] = counter;
	for(int i=0; i<G[u].size(); i++){
		int v = G[u][i];
		if(id[v] == 0){
			cc_dfs(_G, counter, v, _id);
		}
	}
}

vector<int> cc(graph *_G, stack<int> S){
	graph& G = *_G;
	vector<int> id(G.size(), 0);
	
	int counter = 0;
	while(!S.empty()){
		int u = S.top();
		S.pop();
		if(id[u] == 0){
			counter++;
			cc_dfs(_G, counter, u, &id);
		}
	} 
	return id;
}

vector<int> scc(graph *G){
	stack<int> S = top_sort(G);
	graph GT = transpose(G);
	return cc(&GT, S);
}

int main(int argc, char** argv) {
	ifstream in("input.txt");
	ofstream out("output.txt");

	int N, M;
	in >> N >> M;

	graph G(N);
	for(int i=0; i<M; i++){
		int s, t;
		in >> s >> t;
		G[s].push_back(t);
	}

	vector<int> cc = scc(&G);
	vector<int> dim(N, 0);
	int max = 0;

	for(int i=0; i<cc.size(); i++){
		dim[cc[i] - 1]++;
		if(dim[cc[i] - 1] > max){
			max = dim[cc[i] - 1];
		}
	}	

	out << max;
	cout << max << endl;


	return 0;
}