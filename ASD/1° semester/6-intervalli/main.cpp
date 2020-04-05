#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

#define PRINT

struct intv {
	int s,e;
	bool operator<(const intv & other) const {
		return s < other.s ;
	}
	void print() const{
		cout << "(" << s << "," << e << ") ";
	}
} typedef intv;



#ifdef PRINT
void printV(vector<intv> v){
	cout << "v: ";
	for(int i=0; i<v.size(); i++){
		v[i].print();
	}
}
#endif


void insertOrder(vector<intv> *vect, intv val){
	vector<intv> &v = *vect; // Create a reference
	if(v.size() == 0){
		v.push_back(val);
		
		#ifdef PRINT
		val.print(); cout << "v vuoto, aggiungo, ";
		#endif

	} else {
		vector<intv>::iterator low = lower_bound(v.begin(), v.end(), val);
		int foundPos = low - v.begin();
		int prev = foundPos > 0 ? foundPos - 1 : -1;
		int next = foundPos < v.size() ? foundPos : -1;

		//	Elemento tra due intervalli già esistenti
		if(v[prev].e < val.s && val.e < v[next].s){
			//	Se non posso espandere altri intervalli, inserisco l'elemento
			v.insert(v.begin() + prev + 1, val);
		} else {
			// Se ho alcuni intervalli che si accavallano
			if(next != -1 && val.e >= v[next].e){
				v[next].e = val.e;
				v[next].s = val.s;
			} else if(next != -1 && val.e >= v[next].s && val.s < v[next].s){
				v[next].s = val.s;
			} else if(prev == -1){
				v.insert(v.begin(), val);
			}

			if(prev != -1 && val.s <= v[prev].e && val.e > v[prev].e){
				v[prev].e = val.e;
			} else if(next == -1){
				v.push_back(val);
			}
		}

		#ifdef PRINT
		val.print();
		cout << "Trovato prev: " << prev << ", next: " << next << ", ";
		#endif
	}

	#ifdef PRINT
	printV(v);
	cout << endl;
	#endif
}


int main(int argc, char** argv) {
	ifstream in("input.txt");
	ofstream out("output.txt");

	int N;
	in >> N;

	vector<intv> v = vector<intv>();

	//	Lettura dati
	for(int i=0; i<N; i++){
		int s, e;
		in >> s;
		in >> e;
		insertOrder(&v, {s, e});
	}

	#ifdef PRINT
	cout << endl; printV(v); cout << endl;
	#endif

	int rs = -1, re = -1;

	if(v.size() == 0){
		cout << 0;
	}

	for(int i = 0; i < v.size() - 1; i++){
		if(v[i+1].s > v[i].e) {
			int lsomma = v[i+1].s - v[i].e;
			if(lsomma > 1 && lsomma > re - rs){
				rs = v[i].e;
				re = v[i+1].s;
			}
		}
	}

	if(rs == -1 && re == -1){
		cout  << 0 << endl;
		out << 0;
	} else {
		cout  << rs << " " << re << endl;
		out << rs << " " << re;
	}
	

	return 0;
}