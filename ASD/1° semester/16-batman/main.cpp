#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

typedef struct nodo{
	int parent;
	int val;
	int enemy;	//	-1 = da anlizzare, 0 = non c'è nessun nemico, 1 = c'è un nemico

	nodo(int _parent, int _val, int _enemy){
		parent = _parent; 
		val = _val;
		enemy = _enemy;
	}
} nodo;

bool contain_enemy(vector<vector<int>> *_G, int a, int b){
	return false;
}

int main(int argc, char** argv) {
	ifstream in("input.txt");
	ofstream out("output.txt");

	int N, M, S, D;
	in >> N >> M >> S >> D;

	vector<vector<nodo>> G(N);

	for(int i=0; i<M; i++){
		int t, s;
		in >> t >> s;
		G[t].push_back(nodo(t, s, -1));
	}

	queue<int> coda;
	coda.push(S);
	vector<bool> visited(N);
	visited[S] = true;

	while(!coda.empty()){
		int u = coda.front();
		coda.pop();

		for(int i=0; i<G[u].size(); i++){
			int v = G[u][i].val;
			if(!visited[v]){
				visited[v] = true;
				coda.push(v);
			}
		}
	}


	return 0;
}