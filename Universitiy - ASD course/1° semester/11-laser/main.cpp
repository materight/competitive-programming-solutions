#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct arco{
	int partenza, arrivo, peso, primo_spegnimento, tempo_spegnimento, tempo_accensione;
	arco(int _s, int _t,int _w, int _f, int _y, int _n){
		partenza = _s;
		arrivo = _t;
		peso = _w;
		primo_spegnimento = _f;
		tempo_spegnimento = _y;
		tempo_accensione = _n;
	}
};

int tempo_attesa_speginmento(int tempo, arco v){
	if(v.tempo_spegnimento < v.peso){
		//	Non posso passare per quel nodo, il tempo di accensione e minore del tempo di attraversamento
		//cout << "INT_MAX, " << v.tempo_spegnimento << " < " << v.peso;
		return INT_MAX;
	}
	else if(tempo < v.primo_spegnimento){
		return v.primo_spegnimento - tempo;
	} else {
		int T = v.tempo_spegnimento + v.tempo_accensione;	//	Ciclo accensione-spegnimento
		int a = (tempo - v.primo_spegnimento) % T;	//	momento attuale nel ciclo
		if(a > v.tempo_spegnimento){
			//	Sono nel tempo di accensione, devo finire il ciclo
			return T - a;
		}
		else {
			//	Sono nel tempo di spegnimento, controllo se posso attraversare l'arco prima che il laser si riaccenda
			if(a + v.peso < v.tempo_spegnimento){
				return 0;
			} else {
				// Devo aspettare la fine del ciclo per poter ripassare
				return T - a;
			}
			
		}
	}
}

void erdos(vector<vector<arco>> G, vector<int> *_erdos, vector<int> *_parent){
	vector<int>& erdos = *_erdos;
	vector<int>& parent = *_parent;

	queue<int> coda;
	coda.push(0);

	erdos[0] = 0;
	parent[0] = -1;

	while(!coda.empty()){
		int u = coda.front();
		coda.pop();

		int tempo = erdos[u];
		for(int i=0; i<G[u].size(); i++){
			arco v = G[u][i];
			//cout << endl << "Calcolo attesa: ";
			int t_attesa = tempo_attesa_speginmento(erdos[u], v);
			//cout << "\nDa: " << u << "   a: " << v.arrivo << "   t: " << erdos[u] << "   attesa: " << t_attesa << endl;
			if(t_attesa != INT_MAX){
				if(erdos[v.arrivo] > erdos[u] + t_attesa  + v.peso){
					erdos[v.arrivo] = erdos[u] + t_attesa + v.peso;
					parent[v.arrivo] = u;
					coda.push(v.arrivo);
				}
			}
		}
	}
}

int main(int argc, char** argv) {
	ifstream in("input.txt");
	ofstream out("output.txt");

	//	LETTURA DATI
	int N, M;
	in >> N >> M;

	vector<vector<arco>> G(N);

	for(int i=0; i<M; i++){
		int s, t, w, f, y, n;
		in >> s >> t >> w >> f >> y >> n;
		G[s].push_back(arco(s, t, w, f, y, n));
		G[t].push_back(arco(t, s, w, f, y, n));
	}

	//	ALGORITMO 
	vector<int> verdos(G.size(), INT_MAX);
	vector<int> vparent(G.size(), -1);

	erdos(G, &verdos, &vparent);

	if(verdos[N - 1] == INT_MAX){
		cout << -1 << endl;
		out << -1 << endl;
	} else {
		cout << verdos[N - 1] << endl;
		out << verdos[N - 1] << endl;

		//	Genero il percorso fatto per arrivare a N-1 e lo stampo
		vector<int> path;
		path.push_back(N - 1);
		int p = vparent[N-1];
		while(p != -1){
			path.push_back(p);
			p = vparent[p];
		}
		for(int i = path.size() - 1; i >= 0; i--){
			cout << path[i] << endl;
			out << path[i] << endl; 
		}
	}

	return 0;
}