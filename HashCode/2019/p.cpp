#include <iostream>
#include <fstream>
#include <set>
#include <vector>

using namespace std;

struct photo{
	char v;
	set<string> t;
	bool took;
}typedef photo;

int punti(set<string> *t1, set<string> *t2){
	int common = 0;
	int t1difft2 = 0;
	int t2difft1 = 0;

	bool t1_min = t1->size() < t2->size();
	set<string> *min_set = t1_min ? t1 : t2;
	set<string> *set2 = t1_min ? t2 : t1;

	for(string t : *min_set){
		if(set2->find(t) != set2->end()){
			common++;
		} else {
			t2difft1++;
		}
	}
	return min(common, min(t2difft1, static_cast<int>(t1->size()) - common));
}

void solve(string file){
	ifstream in(file+ ".txt");
	ofstream out("out" + file + ".txt");

	int N;
	in >> N;

	vector<photo> photos(N);

	for(int i=0; i<N; i++){
		int n_tag;
		photo x;
		x.took = false;
		in >> x.v >> n_tag;
		for(int j=0; j<n_tag; j++){
			string s;
			in >> s;
			x.t.insert(s);
		}
		photos[i] = x;
	}

	int n = N-1;
	vector<int> result;

	int i=0;
	result.push_back(i);
	while(n > 0){
		n--;
		int max_pos = 0;
		int max_points = 0;
		if(photos[i].v == 'H'){
			for(int j=0; j<N; j++){
				if(i != j && photos[j].v == 'H' && photos[j].took == false){
					int points = punti(&photos[i].t, &photos[j].t);
					if(points > max_points){
						max_pos = j;
						max_points = points; 
					}
				}
			}
			photos[i].took = true;
			photos[max_pos].took = true;
			i = max_pos;
			result.push_back(i);
		}
	}

	out << result.size() <<endl;
	for(int p : result) {
		out << p << endl;
	}
}


int main(int argc, char** argv) {
	vector<string> files;
	files.push_back("a");
	files.push_back("c");
	files.push_back("d");
	files.push_back("b");
	files.push_back("e");

	for(auto f : files){
		solve(f);
		cout << "done " << f << endl;
	}


	return 0;
}