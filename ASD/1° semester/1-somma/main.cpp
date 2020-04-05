#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv) {
	ifstream in("input.txt");
	int N, M;
	in >> N >> M;
	
	ofstream out("output.txt");
	out << N + M << endl;
	
	return 0;
}
