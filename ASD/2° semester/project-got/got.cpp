#include "got.h"
#include <math.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>

using namespace std;

typedef vector<vector<short>> matrix;
typedef vector<vector<bool>> bmatrix;

typedef struct point {
    short i, j;
    point() : point(0, 0){};
    point(short _i, short _j) : i(_i), j(_j){};
} point;

typedef struct castle {
    short i, j, dim, quanti;
    castle(short _i, short _j, short _dim) : i(_i), j(_j), dim(_dim){};
} castle;

short N, M;
vector<castle> castles;
int best_sol = 0;

vector<point> adj(matrix &map, point &p) {
    vector<point> res;
    if (p.i > 0) res.push_back(point(p.i - 1, p.j));
    if (p.j > 0) res.push_back(point(p.i, p.j - 1));
    if (p.i < N - 1) res.push_back(point(p.i + 1, p.j));
    if (p.j < M - 1) res.push_back(point(p.i, p.j + 1));
    random_shuffle(res.begin(), res.end());
    return res;
}

int bfs(matrix &map, castle &c, bmatrix &visited, matrix &start_map) {
    int assigned_castle = 1;
    queue<point> q;
    queue<point> reached;
    map[c.i][c.j] = -c.dim;

    point start = point(c.i, c.j);
    q.push(start);
    reached.push(start);
    short count = 1;

    queue<point> q2;
    q2.push(start);
    while (!q2.empty()) {
        point u = q2.front();
        q2.pop();
        for (point v : adj(map, u)) {
            if (map[v.i][v.j] == c.dim && !visited[v.i][v.j]) {
                assigned_castle++;
                map[v.i][v.j] = -c.dim;
                q.push(v);
                q2.push(v);
                reached.push(v);
                count++;
                visited[v.i][v.j] = true;
            }
        }
    }

    queue<point> rollback_for_touchedCastles;// in caso di rollback, bisogna risettare visited = false per i castelli inglobati

    while (!q.empty() && count < c.dim) {
        point u = q.front();
        q.pop();
        for (point v : adj(map, u)) {
            if (count < c.dim && map[v.i][v.j] == 0 && start_map[v.i][v.j] == 0 && !visited[v.i][v.j]) {
                bool valid = true;
                queue<point> touchedCastles;
                queue<point> rollback_forTouching_Castles;// in caso di rollback, bisogna risettare visited = false per i castelli inglobati
                short touched = 0;
                for (point v2 : adj(map, v)) {
                    if (map[v2.i][v2.j] == c.dim && valid) {
                        if (start_map[v2.i][v2.j] == c.dim && !visited[v2.i][v2.j]){
                            // gestisco il fatto dei castelli che toccano i castelli che andrei a toccare
                            queue<point> otherTouching_castles;
                            otherTouching_castles.push(v2);
                            while (!otherTouching_castles.empty() && valid == true)
                            {
                                point touch = otherTouching_castles.front();
                                otherTouching_castles.pop();
                                for (point v3 : adj(map, touch)) {
                                    if (map[v3.i][v3.j] == c.dim) {
                                        if (start_map[v3.i][v3.j] == c.dim && !visited[v3.i][v3.j]){// per ogni castello adiacente lo aggiungo
                                            //touched++;
                                            //touchedCastles.push(v3);
                                            otherTouching_castles.push(v3);
                                            visited[v3.i][v3.j] = true;// setto visitato temporaneamente per evitare che se è trovata dalle caselle adiacenti non la riconti
                                            rollback_forTouching_Castles.push(v3);
                                        }
                                        else{// se tocco una casella di un altro castello, che non dovrebbe succedere, blocco tutto
                                            valid = false;
                                            break;
                                        }
                                    }
                                }
                            }

                            touched++;
                            if (count + touched + rollback_forTouching_Castles.size() < c.dim && valid){// se aggiungendo questa casella, e quindi anche il castello toccato, non vado oltre il mio k...
                                touchedCastles.push(v2);
                                visited[v2.i][v2.j] = true;// setto visitato temporaneamente per evitare che se è trovata dalle caselle adiacenti non la riconti
                                valid = true;
                                /*while (!rollback_forTouching_Castles.empty())
                                {
                                    point touching = rollback_forTouching_Castles.front();
                                    rollback_forTouching_Castles.pop();
                                    touchedCastles.push(touching);
                                }*/
                            }
                            else{
                                valid = false;
                                break;
                            }
                        }
                        else{
                            valid = false;
                            break;
                        }
                    }
                }
                while (!rollback_forTouching_Castles.empty())// 
                {
                    point touching = rollback_forTouching_Castles.front();
                    rollback_forTouching_Castles.pop();
                    touchedCastles.push(touching);
                }
                
                if (valid) {
                    map[v.i][v.j] = -c.dim;
                    q.push(v);
                    reached.push(v);
                    count++;
                    // aggiungo anche i castelli toccati
                    while (!touchedCastles.empty())
                    {
                        assigned_castle++;
                        point touch = touchedCastles.front();
                        touchedCastles.pop();
                        rollback_for_touchedCastles.push(touch);
                        map[touch.i][touch.j] = -c.dim;
                        q.push(touch);
                        reached.push(touch);
                        count++;
                    }
                }
                else{
                    // resetto il visited dei castelli toccati
                    while (!touchedCastles.empty())
                    {
                        point touch = touchedCastles.front();
                        touchedCastles.pop();
                        visited[touch.i][touch.j] = false;
                    }
                }
            } else if (count >= c.dim) {
                break;
            }
        }
    }

    while (!reached.empty()) {
        point p = reached.front();
        reached.pop();
        if (count < c.dim) {  // ROLLBACK: Se non ho raggiunto dim, rimuovo il castello e il territorio
            map[p.i][p.j] = 0;
        } else{
            if (count == c.dim)
                map[p.i][p.j] = -map[p.i][p.j];
            else{
                map[p.i][p.j] = 0;
            }
        }
    }
    if (count < c.dim) {
        // rollback dei castelli toccati in bfs
        while (!rollback_for_touchedCastles.empty())
        {
            point p = rollback_for_touchedCastles.front();
            rollback_for_touchedCastles.pop();
            visited[p.i][p.j] = false;
        }
        return 0;
    } else {
        if (count == c.dim)
            return assigned_castle;
        else
            return 0;
    }
}

void solve(matrix &map, matrix &copy_map, ofstream &out) {
    int point = 0;
    bmatrix visited(N, vector<bool>(M, false));
    for (castle c : castles) {
        if (!visited[c.i][c.j]) {
            visited[c.i][c.j] = true;
            point += bfs(copy_map, c, visited, map);
        }
    }

    unordered_map<short, short> aaa;
    int valid = 1;
    for (int k = 0; k < N; k++)
    {
        for (int j = 0; j < M; j++)
        {
            if (copy_map[k][j] != 0)
                aaa[copy_map[k][j]]++;
        }
    }
    for (std::unordered_map<short, short>::iterator it = aaa.begin(); it != aaa.end(); ++it)
    {
        //cout << it->first << ":" << it->second << endl;
        if (it->second % it->first != 0){
            valid = 0;
        }
    }

    if (valid){
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (point > best_sol)
                    out << copy_map[i][j] << " ";
                copy_map[i][j] = map[i][j];
            }
            if (point > best_sol)
                out << endl;
        }
        if (point > best_sol) {
            best_sol = point;
            out << "***" /*<< (valid ? "" : "ERR")*/ << endl;
            //cout << point << endl;
        }
    }
}

int main() {
    //ifstream in("input/input17.txt");
    ifstream in("input.txt");
    ofstream out("output.txt");

    /*********************** LETTURA DATI ****************************/
    in >> N >> M;

    matrix map(N, vector<short>(M, 0));
    matrix copy_map(N, vector<short>(M, 0));
    vector<short> conto(N * M, 0);  //mmm not very good, just for now :)
    int mass = 0;                   //to not iter on N*M later

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            in >> map[i][j];
            copy_map[i][j] = map[i][j];
            if (map[i][j] > 0) {
                castles.push_back(castle(i, j, map[i][j]));
                conto[map[i][j]]++;
                //mass = (mass > map[i][j]) ? mass : map[i][j];
            }
        }
    }

    /*********************** ALGORITMO ****************************/
    for (int i = 0; i < castles.size(); i++) {
        castles[i].quanti = conto[castles[i].dim];
    }

    for (int i = 0; i < 3; i++) {
        // Ordine di Steve
        sort(castles.begin(), castles.end(), [](castle a, castle b) {if (a.quanti == b.quanti) return a.dim > b.dim; else return a.quanti < b.quanti; });
        solve(map, copy_map, out);
        // Ordine di Steve inverso
        sort(castles.begin(), castles.end(), [](castle a, castle b) {if (a.quanti == b.quanti) return a.dim < b.dim; else return a.quanti > b.quanti; });
        solve(map, copy_map, out);
        // Ordine crescente
        sort(castles.begin(), castles.end(), [](castle a, castle b) { return a.dim < b.dim; });
        solve(map, copy_map, out);
        // Ordine decrescente
        sort(castles.begin(), castles.end(), [](castle a, castle b) { return a.dim > b.dim; });
        solve(map, copy_map, out);
    }
    // Casuale
    while (1) {
        random_shuffle(castles.begin(), castles.end());
        solve(map, copy_map, out);
    };
    //} while (next_permutation(castles.begin(), castles.end()));

    return 0;
}