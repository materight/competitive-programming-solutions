#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
typedef struct library {
    int id, n, t, b;
    bool taken;
    library() : id(-1), t(-1), n(-1), b(-1), taken(false) {}
} library;

struct cmp {
    bool operator()(int const& lhs, int const& rhs) const {
        return lhs > rhs;
    }
};

void solve(string file) {
    ifstream in(file + ".in");
    ofstream out(file + ".out");

    int B, L, D;
    vector<int> books;
    vector<library> libs;
    vector<set<int, cmp>> LB;  // Libraries with books
    vector<set<int, cmp>> BL;  // Books with libraries
    vector<int> rewSum;
    vector<vector<int>> partialSum;

    in >> B >> L >> D;
    books.resize(B);
    libs.resize(L);
    LB.resize(L);
    BL.resize(B);
    rewSum.resize(L, 0);
    partialSum.resize(L);

    for (int i = 0; i < B; i++) {
        in >> books[i];
    }
    for (int i = 0; i < L; i++) {
        libs[i].id = i;
        in >> libs[i].n >> libs[i].t >> libs[i].b;
        for (int j = 0; j < libs[i].n; j++) {
            int book;
            in >> book;
            LB[i].insert(book);
            BL[book].insert(i);
            rewSum[i] += books[book];
            if (partialSum[i].empty())
                partialSum[i].push_back(books[book]);
            else
                partialSum[i].push_back(partialSum[i][partialSum[i].size() - 1] + books[book]);
        }
    }

    vector<int> Ltak;

    long long coeffMin, coeffRew, coeff;
    while (D > 0) {
        priority_queue<pii> Q;
        for (int i = 0; i < L; i++) {
            if (!libs[i].taken && libs[i].n > 0) {
                coeffMin = min(max((D - libs[i].t), 0) * libs[i].b, libs[i].n);  // Indica quanti libri posso prendere
                coeffRew = rewSum[i] + (double)min(1.0, ((double)((D - libs[i].t) * libs[i].b) / ((double)libs[i].n)));
                coeff = coeffMin + coeffRew;

                if (coeffMin >= 1) {
                    coeff = partialSum[i][coeffMin - 1];  // Somma libri prendibili
                } else {
                    coeff = 0;
                }

                Q.push({coeff, i});
            }
        }
        if (Q.empty()) break;

        library l = libs[Q.top().second];
        libs[Q.top().second].taken = true;
        Ltak.push_back(l.id);

        /*for (int i = 0; i < Ltak.size(); i++) {
            for (int j = 0; j < l.t; j++) {
                int ltak = Ltak[i];
                libs[ltak].n--;
                int Btak = *LB[ltak].begin();
                for (int lib : BL[Btak]) {
                    LB[lib].erase(Btak);
                }
            }
        }*/
        D -= l.t;
    }

    vector<bool> book_tak(B);
    vector<vector<int>> lbtak(L);

    int Lcount = 0;
    for (int l : Ltak) {
        int count = 0;
        for (int b : LB[l]) {
            if (!book_tak[b]) {
                count++;
                lbtak[l].push_back(b);
                book_tak[b] = true;
            }
        }
        if (count > 0) {
            Lcount++;
        }
    }

    fill(book_tak.begin(), book_tak.end(), false);

    out << Lcount << endl;
    for (int l : Ltak) {
        int count = 0;
        queue<int> Q;
        for (int b : LB[l]) {
            if (!book_tak[b]) {
                count++;
                Q.push(b);
                book_tak[b] = true;
            }
        }
        if (count > 0) {
            out << l << " " << count << endl;
            while (!Q.empty()) {
                out << Q.front() << " ";
                Q.pop();
            }
            out << endl;
        }
    }
    out << endl;
}

int main(int argc, char** argv) {
    string files[] = {"a", "b", "c", "d", "e", "f"};
    for (string f : files) {
        cout << f << " solving... ";
        solve(f);
        cout << "done" << endl;
    }
    return 0;
}