#include <algorithm>
#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    ifstream in("input.txt");

    int N;
    in >> N;

    int arr[N];

    int somma = 0;

    for (int i = 0; i < N; i++) {
        int a;
        in >> a;
        arr[i] = a;
    }

    int maxS = 0, maxH = 0;

    for (int i = 0; i < N; i++) {
        maxH += arr[i];
        if (maxH < 0) {
            maxH = 0;
        } else if (maxH > maxS) {
            maxS = maxH;
        }
    }
    cout << "Max: " << maxS << endl;
    ofstream out("output.txt");
    out << maxS << endl;
    return 0;
}
