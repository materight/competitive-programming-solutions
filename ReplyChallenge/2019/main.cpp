#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef struct point {
    int x, y, p;
    point() {
        point(-1, -1, -1);
    }
    point(int _x, int _y, int _p) {
        x = _x;
        y = _y;
        p = _p;
    }
    bool operator<(const point& a) const {
        return p < a.p;
    }
    bool operator>(const point& a) const {
        return p > a.p;
    }
} point;

typedef struct cell {
    int v;
    int c;
    cell() {
        cell(-1, 0);
    }
    cell(int _v, int _c) {
        v = _v;
        c = _c;
    }
} cell;

int cost(char c) {
    switch (c) {
        case '~':
            return 800;
        case '*':
            return 200;
        case '+':
            return 150;
        case 'X':
            return 120;
        case '_':
            return 100;
        case 'H':
            return 70;
        case 'T':
            return 50;
        default:  //  case '#':
            return INT_MAX;
    }
}

char cost_char(int v) {
    switch (v) {
        case 800:
            return '~';
        case 200:
            return '*';
        case 150:
            return '+';
        case 120:
            return 'X';
        case 100:
            return '_';
        case 70:
            return 'H';
        case 50:
            return 'T';
        default:  //  case INT_MAX:
            return '#';
    }
}

pair<point, char> min_adj(vector<vector<cell>>& map, int N, int M, int x, int y) {
    point min = point(-1, -1, INT_MAX - 1);
    char c = 'X';

    /* 
    cout << x - 1 << " " << y << " U " << map[x - 1][y] << endl;
    cout << x << " " << y - 1 << " L " << map[x][y - 1] << endl;
    cout << x + 1 << " " << y << " D " << map[x + 1][y] << endl;
    cout << x << " " << y + 1 << " R " << map[x][y + 1] << endl;
    */

    if (x - 1 >= 0 && map[x - 1][y].v < min.p && map[x - 1][y].c == 0) {
        min = point(x - 1, y, map[x - 1][y].v);
        c = 'U';
    }
    if (y - 1 >= 0 && map[x][y - 1].v < min.p && map[x][y - 1].c == 0) {
        min = point(x, y - 1, map[x][y - 1].v);
        c = 'R';
    }
    if (x + 1 < N && map[x + 1][y].v < min.p && map[x + 1][y].c == 0) {
        min = point(x + 1, y, map[x + 1][y].v);
        c = 'D';
    }
    if (y + 1 < M && map[x][y + 1].v < min.p && map[x][y + 1].c == 0) {
        min = point(x, y + 1, map[x][y + 1].v);
        c = 'L';
    }
    return {min, c};
}

void solve(string file, bool print = false) {
    cout << " -----  SOLVING " << file << " ----- " << endl;

    ifstream in(file);

    int M, N;  //   Dimensioni mappa
    int C;     //   Customer offices
    int O;     //   Office da impostare

    in >> M >> N >> C >> O;  //  N e M invertite apposta
    if (print) printf("%d %d %d %d\n", M, N, C, O);

    vector<vector<cell>> map(N, vector<cell>(M));
    vector<point> cust(C);

    int x, y, p;
    for (int i = 0; i < C; i++) {
        in >> y >> x >> p;
        cust[i] = point(x, y, p);
        map[x][y].c = 1;
    }

    char c;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            in >> c;
            map[i][j].v = cost(c);
        }
    }

    sort(cust.begin(), cust.end(), greater<point>());

    int i = 0;
    ofstream out("out_" + file);
    while (O > 0 && i < C) {
        pair<point, char> min_pair = min_adj(map, N, M, cust[i].x, cust[i].y);
        point min = min_pair.first;
        char path = min_pair.second;
        if (min.x != -1 && min.y != -1) {
            out << min.y << " " << min.x << " " << path << endl;
            map[min.x][min.y].c = 2;
            //cout << min.x << " " << min.y << " " << path << endl;
            O--;
        }
        i++;
    }

    cout << endl;
    if (print) {
        for (int i = -1; i < N; i++) {
            for (int j = -1; j < M; j++) {
                if (i == -1) {
                    printf("%3d", j);
                } else if (j == -1) {
                    printf("%3d", i);
                } else {
                    if (map[i][j].c == 0)
                        printf("%3c", cost_char(map[i][j].v));
                    else if (map[i][j].c == 1)
                        printf("\033[31m%3c\033[0m", cost_char(map[i][j].v));
                    else if (map[i][j].c == 2)
                        printf("\033[34m%3c\033[0m", cost_char(map[i][j].v));
                }
            }
            cout << endl;
        }
    }
}

int main(int argc, char** argv) {
    solve("0_test.txt");
    cout << "0 solved" << endl;
    solve("1_victoria_lake.txt", true);
    cout << "1 solved" << endl;
    solve("2_himalayas.txt");
    cout << "2 solved" << endl;
    solve("3_budapest.txt");
    cout << "3 solved" << endl;
    solve("4_manhattan.txt");
    cout << "4 solved" << endl;
    solve("5_oceania.txt");
    cout << "5 solved" << endl;
}