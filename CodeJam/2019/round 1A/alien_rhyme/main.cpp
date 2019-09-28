#include <iostream>
#include <unordered_map>

using namespace std;

typedef struct trie {
    bool is_element;
    int children_count;
    unordered_map<char, struct trie*> children;

    trie() {
        is_element = false;
        children_count = 0;
    }

    void insert(string val) {
        if (val.length() == 0) {
            is_element = true;
        } else {
            if (children[val.back()] == NULL) children[val.back()] = new trie();
            children_count++;
            children[val.back()]->insert(val.substr(0, val.length() - 1));
        }
    }

    ~trie() {
        for (auto child : children) {
            delete child.second;
        }
    }
} trie;

pair<int, int> solve(trie* t, bool is_root) {
    //  Foglia, quindi prima lettera di una stringa
    if (t->children_count == 0) return {0, 1};
    //  Nodo
    int accoppiati = 0;
    int da_accoppiare = 0;
    for (auto child : t->children) {
        pair<int, int> result = solve(child.second, false);
        accoppiati += result.first;
        da_accoppiare += result.second;
    }
    if (t->is_element) {
        da_accoppiare++;
    }
    if (!is_root && da_accoppiare >= 2) {
        //  Accoppio 2 nodi, gli altri li tengo come da accoppiare
        da_accoppiare -= 2;
        accoppiati += 2;
    }
    //  Se il nodo è la prima lettera di una stringa, lo conto
    return {accoppiati, da_accoppiare};
}

int main(int argc, char** argv) {
    int T;
    cin >> T;

    for (int t = 0; t < T; t++) {
        int N;
        cin >> N;

        trie tr = trie();

        for (int i = 0; i < N; i++) {
            string w;
            cin >> w;
            tr.insert(w);
        }

        pair<int, int> soluz = solve(&tr, true);
        cout << "Case #" << (t + 1) << ": " << soluz.first << endl;
    }
    return 0;
}