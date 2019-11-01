#include <iostream>
#include <vector>

using namespace std;

typedef struct point {
    int x, y;
    point() : point(-1, -1) {}
    point(int _x, int _y) : x(_x), y(_y) {}
} point;

int main(int argc, char** argv) {
    int N, PROB;
    cin >> N >> PROB;

    // Numero minimo di punti in una linea
    int M = (N * PROB / 100);

    vector<point> p(N);
    for (int i = 0; i < N; i++) {
        cin >> p[i].x >> p[i].y;
    }

    
    return 0;
}