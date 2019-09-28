#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <climits>
#include <queue>

using namespace std;

typedef struct node{
	int x, y;
	node(int _x, int _y){
		x = _x;
		y = _y;
	}
	int dist(node n){
		return abs(x - n.x) + abs(y - n.y);
	}
}node;

int main(int argc, char** argv) {

	/*-------------------------------------------------------------------------------------  LETTURA DATI ----------------------------------------------------------------------------------------*/
	ifstream in("input19.txt");
	ofstream out("output.txt");

	int Cn, Sn;
	in >> Cn >> Sn;

	vector<node> C;
	vector<node> S;

	for(int i=0; i<Cn; i++){
		int x, y;
		in >> x >> y;
		C.push_back(node(x, y));
	}	

	for(int i=0; i<Sn; i++){
		int x, y;
		in >> x >> y;
		S.push_back(node(x, y));
	}	

	int x, y;
	in >> x >> y;
	node target = node(x, y); 


	

	/*--------------------------------------------------------------------------------------  ALGORITMO ----------------------------------------------------------------------------------------*/
	vector<int> costo(Cn, INT_MAX);
	vector<int> prende(Sn, -1);
	vector<int> preso(Cn, -1);

	//	Per avere almeno un soldato arrivato al terget da mettere nell'output per i componenti presi dal target
	int last_soldato = -1;

	//	Nel caso tutte le componenti costino meno dal target, devo avere almeno un soldato che va al target, ossia quello che mi costa meno
	int costo_min_assoluto = INT_MAX;
	int soldato_costo_min = -1;
	int componente_costo_min = -1;

	queue<int> coda;
	for(int i=0; i<Cn; i++){
		coda.push(i);
	}

	while(!coda.empty()){
		int i = coda.front();
		coda.pop();

		int from_target = 2 * C[i].dist(target);
		int costo_min = from_target;
		int preso_da = -1;

		cout << "Componente " << i << ", costo dal target: " << from_target << endl;

		for(int j=0; j<Sn; j++){
			
			int from_sold = (from_target / 2) + C[i].dist(S[j]);

			cout << "\tCosto dal soldato " << j << ": " << from_sold << endl;

			if(from_sold < costo_min_assoluto){
				costo_min_assoluto = from_sold;
				soldato_costo_min = j;
				componente_costo_min = i;
			}
			
			if(from_sold < costo_min){
				int guadagno = from_target - from_sold;
				if(prende[j] == -1  || guadagno > C[prende[j]].dist(target) - C[prende[j]].dist(S[j])){
					preso_da = j;
					last_soldato = j;
					costo_min = from_sold;
				}
			}
		}

		costo[i] = costo_min;
		if(preso_da != -1){			
			if(prende[preso_da] != -1){
				//	Se il componente analizzato adesso porta ad un guadagno migliore, devo rianalizzare l'altro componente
				coda.push(prende[preso_da]);
				preso[prende[preso_da]] = -1;
			}
			preso[i] = preso_da;
			prende[preso_da] = i;
		}
		cout << "Costo percorso scelto: " << costo_min << " usando soldato: " << preso[i] << endl << endl;
	}






	/*----------------------------------------------------------------------------------  RISULTATO ------------------------------------------------------------------------------------------*/

	//	Se tutte le componenti hanno costo minore se prese dal centro, uso il soldato che ne prende 1 al costo minore
	if(last_soldato == -1) {
		last_soldato = soldato_costo_min;
		costo[componente_costo_min] = costo_min_assoluto;
		preso[componente_costo_min] = soldato_costo_min;
	}

	int T = 0;
	for(int c : costo){
		T += c;
	}
	cout << T << endl << endl;
	out << T << endl;


	for(int i=0; i<preso.size(); i++){
		if(preso[i] == -1){
			out << last_soldato << endl;
		} else {
			cout << "Prendo " << i << " con soldato " << preso[i] << endl;
			out << preso[i] << endl;
		}
	}
	return 0;
}