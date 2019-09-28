#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

vector<int> merge(vector<int> v1, vector<int> v2) {
    int i1 = 0, i2 = 0;
    vector<int> res = vector<int>();
    while (i1 < v1.size() || i2 < v2.size()) {
        if (i1 < v1.size() && i2 < v2.size()) {
            if (v1[i1] < v2[i2]) {
                res.push_back(v1[i1]);
                i1++;
            } else {
                res.push_back(v2[i2]);
                i2++;
            }
        } else if (i1 < v1.size()) {
            res.push_back(v1[i1]);
            i1++;
        } else if (i2 < v2.size()) {
            res.push_back(v2[i2]);
            i2++;
        }
    }
    return res;
}

vector<int> sort(vector<int> v) {
    if (v.size() == 1) {
        return v;
    } else if (v.size() == 2) {
        if (v[0] > v[1]) {
            int tmp = v[0];
            v[0] = v[1];
            v[1] = tmp;
        }
        return v;
    } else {
        int len1 = v.size() / 2;
        vector<int> v1 = vector<int>(v.begin(), v.begin() + len1);
        vector<int> v2 = vector<int>(v.begin() + len1, v.end());
        return merge(sort(v1), sort(v2));
    }
}

int main(int argc, char** argv) {
    ifstream in("input.txt");
    ofstream out("output.txt");

    int N;
    in >> N;

    vector<int> v = vector<int>(N);

    for (int i = 0; i < N; i++) {
        in >> v[i];
    }

    vector<int> result = sort(v);

    for (int i = 0; i < N; i++) {
        out << result[i] << " ";
    }

    return 0;
}