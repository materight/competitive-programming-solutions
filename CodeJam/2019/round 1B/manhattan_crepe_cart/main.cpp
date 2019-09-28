#include <iostream>
#include <vector>

using namespace std;

typedef struct point {
    int x, y;
    char d;
} point_t;

pair<int, int> get_s_e_X(point_t p, int Q) {
    switch (p.d) {
        case 'S':
        case 'N':
            return {p.x, p.x};
        case 'E':
            return {p.x + 1, Q};
        case 'W':
            return {0, p.x - 1};
    }
}

pair<int, int> get_s_e_Y(point_t p, int Q) {
    switch (p.d) {
        case 'S':
            return {p.y + 1, Q};
        case 'N':
            return {0, p.y - 1};
        case 'E':
        case 'W':
            return {p.y, p.y};
    }
}

int move_x(point_t p) {
    switch (p.d) {
        case 'S':
        case 'N':
            return 0;
        case 'E':
        case 'W':
            return 1;
    }
}

int main(int argc, char** argv) {
    int T;
    cin >> T;

    for (int t = 0; t < T; t++) {
        int P, Q;
        cin >> P >> Q;
        vector<point_t> p(P);

        for (int i = 0; i < P; i++) {
            cin >> p[i].x >> p[i].y >> p[i].d;
        }

        vector<vector<int>> map(Q + 1, vector<int>(Q + 1, 0));

        for (point_t person : p) {
            pair<int, int> pair_x = get_s_e_X(person, Q);
            pair<int, int> pair_y = get_s_e_Y(person, Q);
            int sx = pair_x.first;
            int ex = pair_x.second;
            int sy = pair_y.first;
            int ey = pair_y.second;
            int c_x = move_x(person);
            int c_y = 1 - c_x;
            for (int y = sx, x = sy; y <= ex && x <= ey; x += c_y, y += c_x) {
                map[y][x]++;
            }
        }

        int max_x = 0, max_y = 0;
        for (int x = 0; x <= Q; x++) {
            for (int y = 0; y <= Q; y++) {
                cout << map[x][y] << " ";
                if (map[x][y] > map[max_x][max_y]) {
                    max_x = x;
                    max_y = y;
                } else if (map[x][y] == map[max_x][max_y]) {
                    if ((x < max_x) || (x == max_x && y > max_y)) {
                        max_x = x;
                        max_y = y;
                    }
                }
            }
            cout << endl;
        }

        cout << "Case #" << (t + 1) << ": " << max_x << " " << max_y << endl;
    }
    return 0;
}