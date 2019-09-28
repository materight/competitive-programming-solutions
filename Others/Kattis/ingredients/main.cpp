#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

typedef struct recipe {
    string name, parent;
    int cost, prest;
    recipe() {
        cost = 0;
        prest = 0;
    }
} recipe;

int main(int argc, char** argv) {
    int B, N;
    cin >> B >> N;

    unordered_map<string, recipe> recipes;

    for (int i = 0; i < N; i++) {
        recipe r;
        string name, ingredient;
        cin >> name >> r.parent >> ingredient >> r.cost >> r.prest;
    }

    return 0;
}