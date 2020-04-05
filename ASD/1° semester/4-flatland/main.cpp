#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <set>

using namespace std;

int N;
char *arr;
vector<bool> soluzione;
set<vector<int>> analizzati;

void solve(vector<int> v){
	if(v.size() == 1){
		soluzione[v[0]] = true;
		return;
	} else {
		for(int i = 1; i < v.size() - 1; i++){
			//	Elimino il triangolo selezionato e quello di fronte in un vettore copia per passarlo a solve
			vector<int> copia(v);

			int delete_pos = (arr[v[i]] == 's') ? i - 1 : i;
			copia.erase(copia.begin() + delete_pos);
			copia.erase(copia.begin() + delete_pos);

			if(analizzati.count(copia) == 0){
				//	Sottovettore non ancora analizzato
				analizzati.insert(copia);
				solve(copia);
			}
		}
	}
}

int main(int argc, char** argv) {
	ifstream in("input.txt");
	ofstream out("output.txt");

	in >> N;
	soluzione.resize(N);

	arr = new char[N];

	vector<int> v;

	//	Inizializzo vettore di elementi
	for(int i=0; i<N; i++){
		in >> arr[i];
		v.push_back(i);
	}


	solve(v);

	ostringstream oss;
	int total = 0;
	for(int i=0; i<N; i++){
		if(soluzione[i] == 1){
			oss << i << " ";
			total++;
		}
	}


	out << total << endl;
	out << oss.str();


	cout << total << endl;
	cout << oss.str();
	return 0;
}