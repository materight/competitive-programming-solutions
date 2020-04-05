#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <climits>

using namespace std;

int main(int argc, char** argv) {
	ifstream in("input.txt");
	ofstream out("output.txt");

	int N, M;
	in >> N;
	in >> M;

	vector<vector<int>> G(N);

	for(int i=0; i<M; i++){
		int n1, n2;
		in >> n1;
		in >> n2;
		G[n1].push_back(n2);
		G[n2].push_back(n1);
	}

	int max = 0;

	for(int start=0; start<N; start++){

		//cout << endl << endl << "Parto da " << start << endl;

		deque<int> coda;
		coda.push_back(start);

		vector<bool> visited(N);
		visited[start] = true;

		//Indica ad ogni livello quanti nodi ci sono. Quando diventa 0 ho raggiunto un altro livello
		int counter = 1;
		int level = 0;

		while(!coda.empty()){
			


			/*
			cout << "visited: ";
			for(bool b : visited) cout << b << " ";
			cout << endl << "coda: ";
			for(int n : coda) cout << n << " ";
			*/


			int current = coda.front();
			coda.pop_front();
				

			//cout << endl << "Analizzo " << current << " lvl: " << level << endl;



			for(int j=0; j<G[current].size(); j++){
				int child = G[current][j];
				if(!visited[child]){
					visited[child] = true;
					coda.push_back(child);
				}
			}

			counter--;
			
			if(counter == 0 && coda.size() != 0){
				//	Se counter == 0 ho finito di analizzare il livello e passo a quello successivo
				//	Se coda.size() == 0 ho analizzato tutto il grafo dal nodo start, ed ho finito
				counter = coda.size();
				level++;
			}
		}

		if(level > max){
			max = level;
		}
	}

	cout << max;
	out << max;

	return 0;
}