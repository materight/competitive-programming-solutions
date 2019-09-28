#include <iostream>
#include <fstream>
#include <climits>
#include <vector>

using namespace std;

int main(int argc, char** argv) {
	ifstream in("input.txt");

	vector<int> c = vector<int>('12');

	int N,M;
	in >> N >> M;
	
	int somme[N][M];
	int max = INT_MIN;
	
	for(int i=0; i < N; i++){
		for(int j=0; j < M; j++){
			int a;
			in >> a;
			if(i == 0 && j == 0){
				max = a;	//	Inizializzo il max
				somme[i][j] = a;
			} else if(i == 0){
				somme[i][j] = a + somme[i][j-1];
			} else if(j == 0) {
				somme[i][j] = a + somme[i - 1][j];
			} else{
				somme[i][j] = a + somme[i][j-1] + somme[i-1][j] - somme[i-1][j-1];
			}
			if(somme[i][j] > max){
				max = somme[i][j];
			}
		}
	}
	
	/*cout << "Somme: "<< endl; 
	
	for(int i=0; i < N; i++){
		for(int j=0; j < M; j++){
			cout << somme[i][j] << " ";
		}
		cout << endl;
	}*/

	//	Sposto l'angolo di partenza della matrice
	for(int i1=0; i1 < N; i1++){
		for(int j1=0; j1 < M; j1++){
				if(i1 != 0 && j1 != 0){
					for(int i2=i1; i2 < N; i2++){
						for(int j2=j1; j2 < M; j2++){
							
							int last = somme[i2][j2];	//	Coordinata elemento in basso a destra
							int togliRiga = i1 != 0 ? somme[i1-1][j2] : 0;	//	Somma righe da togliere
							int togliColonna = j1 != 0 ? somme[i2][j1-1] : 0;	//	Somma colonne da togliere
							int aggiungiDiagonale = i1 != 0 && j1 != 0 ? somme[i1-1][j1-1] : 0;	//	Somma elemento diagonale da aggiungere perch� eliminato 2 volte con togliRiga e togliColonna
							
							int somma = last - togliRiga - togliColonna + aggiungiDiagonale;	//	Calcolo somma sottomatrice
							
							if(somma > max){
								max = somma;
							}
						}
					}
				}
		}
	}
	
	cout << "Max trovato: "<< max <<endl;

	ofstream out("output.txt");
	out << max << endl;
	
	return 0;
}
