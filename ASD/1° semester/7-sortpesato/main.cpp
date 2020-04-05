#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//#define PRINT

#ifdef PRINT
void print(vector<int> v){
	for(int i=0; i < v.size(); i++){
		cout << v[i] << " ";
	}
}
#endif

void swap(int* a, int* b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

int calcP(vector<int> v, int lv, int *S){
	int minP = -1;

	#ifdef PRINT
	for(int i=0; i<lv; i++) cout << "\t";
	cout << "LV" << lv << " ";
	print(v); cout <<endl;
	#endif

	if(lv > *S) *S = lv;

	for(int i=0; i < v.size(); i++){
		if(v[i] != i) {

			#ifdef PRINT
			for(int i=0; i<lv; i++) cout << "\t";
			cout << "LV" << lv << " found to swap: " << v[i] << " " << v[v[i]] << " | ";
			print(v); cout <<endl;
			#endif

			int pos = v[i];
			
			swap(&v[i], &v[pos]);
			int lP = calcP(v, lv + 1, S) + v[i] + v[pos] + 2;
			swap(&v[i], &v[pos]);

			if(lP < minP || minP == -1) minP = lP;
		}
	}

	#ifdef PRINT
	for(int i=0; i<lv; i++) cout << "\t";
	cout << "LV" << lv << " P: " << minP << endl;
	#endif

	if(minP == -1) minP = 0;
	return minP;
}



int main(int argc, char** argv) {
	ifstream in("input.txt");
	ofstream out("output.txt");

	int N;
	in >> N;

	vector<int> v(N);

	for(int i=0; i<N; i++){
		in >> v[i];
		v[i]--;	//	Per comodità faccio andare i numeri da 0 a N-1
	}

	int S = 0;
	int P = calcP(v, 0, &S);
	int i=0;

	cout << "S: " << S << ", P: " << P << endl;
	out << S << " " << P;
	return 0;
}