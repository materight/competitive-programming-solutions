#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <set>
#include <utility>
#include <vector>

using namespace std;

auto rng = std::default_random_engine{};

struct photo {
    char v;
    set<string> t;
    bool took;
} typedef photo;

int punti(set<string> *t1, set<string> *t2) {
    int common = 0;
    int t1difft2 = 0;
    int t2difft1 = 0;

    bool t1_min = t1->size() < t2->size();
    set<string> *min_set = t1_min ? t1 : t2;
    set<string> *set2 = t1_min ? t2 : t1;

    for (string t : *min_set) {
        if (set2->find(t) != set2->end()) {
            common++;
        } else {
            t2difft1++;
        }
    }
    return min(common, min(t2difft1, static_cast<int>(t1->size()) - common));
}

void solve(string file, int *max) {
    ifstream in(file + ".txt");

    int N;
    in >> N;

    vector<photo> photos(N);

    for (int i = 0; i < N; i++) {
        int n_tag;
        photo x;
        x.took = false;
        in >> x.v >> n_tag;
        for (int j = 0; j < n_tag; j++) {
            string s;
            in >> s;
            x.t.insert(s);
        }
        photos[i] = x;
    }
    in.close();

    vector<pair<int, int>> result;

    vector<int> vertical;

    for (int i = 0; i < N; i++) {
        if (photos[i].v == 'H') {
            result.push_back(pair<int, int>(i, -1));
        } else {
            vertical.push_back(i);
        }
    }

    shuffle(begin(vertical), end(vertical), rng);

    int V_p = -1;
    for (int v : vertical) {
        if (V_p == -1) {
            V_p = v;
        } else {
            result.push_back(pair<int, int>(V_p, v));
            V_p = -1;
        }
    }

    shuffle(begin(result), end(result), rng);

    int tot = 0;
    for (int i = 1; i < result.size(); i++) {
        set<string> temp1;
        set<string> temp2;
        if (result[i].second != -1) {
            int p1 = result[i].first;
            int p2 = result[i].second;
            set_union(std::begin(photos[p1].t), std::end(photos[p1].t),
                      std::begin(photos[p2].t), std::end(photos[p2].t),
                      std::inserter(temp1, std::begin(temp1)));

        } else {
            temp1 = photos[result[i].first].t;
        }
        if (result[i - 1].second != -1) {
            int p1 = result[i - 1].first;
            int p2 = result[i - 1].second;
            set_union(std::begin(photos[p1].t), std::end(photos[p1].t),
                      std::begin(photos[p2].t), std::end(photos[p2].t),
                      std::inserter(temp2, std::begin(temp2)));
        } else {
            temp2 = photos[result[i - 1].first].t;
        }
        tot += punti(&temp1, &temp2);
    }

    if (tot > *max) {
        ofstream out("out" + file + ".txt");

        cout << file << ": new max = " << tot << endl;
        out << result.size() << endl;
        for (auto r : result) {
            if (r.second == -1) {
                out << r.first << endl;
            } else {
                out << r.first << " " << r.second << endl;
            }
        }
        *max = tot;
        out.close();
    } else {
        //cout  <<  file << ": min = " << tot << endl;
    }
}

int main(int argc, char **argv) {
    int max_a = 0;
    int max_b = 0;
    int max_c = 0;
    int max_d = 0;
    int max_e = 0;

    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    rng.seed((unsigned long)seed);

    while (true) {
        cout << "new loop" << endl;
        solve("a", &max_a);
        solve("b", &max_b);
        solve("c", &max_c);
        solve("d", &max_d);
        solve("e", &max_e);
    }

    return 0;
}