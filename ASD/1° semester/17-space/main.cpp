#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

int main(int argc, char** argv) {
	ifstream in ("input.txt");
	ofstream out ("output.txt");

	int N, M, min = 0;
	in >> N >> M;

	vector<vector<int>> G(N);
	
	for(int i=0;i< M;i++){
		int u,v;
		in >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	
	vector<int> stampa;
	for(int i=0;i< N;i++){
		if(G[i].size() == 1){
			stampa.push_back(i);
			min++;
		}
	}
	
	
	
	out << min << endl;	
	for(int i=0;i< stampa.size();i++){
		out  << stampa[i] << " ";
	}
	
	return 0;
}
