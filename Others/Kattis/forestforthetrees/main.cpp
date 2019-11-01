#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

int main(int argc, char** argv) {
    ll xb, yb;
    ll xq1, xq2, yq1, yq2;

    cin >> xb >> yb;
    cin >> xq1 >> yq1 >> xq2 >> yq2;

    ll k = gcd(xb, yb);
    ll x1 = xb / k, y1 = yb / k;

    if (x1 == xb && y1 == yb) {
        cout << "Yes" << endl;
    } else if (x1 >= xq1 && y1 >= yq1 && x1 <= xq2 && y1 <= yq2) {
        ll i = min(ceil((ld)xq2 / (ld)x1), ceil((ld)yq2 / (ld)y1));
        ll xf = x1 * i, yf = y1 * i;
        if (xf < xb && yf < yb) {
            cout << "No" << endl
                 << xf << " " << yf << endl;
        } else {
            cout << "Yes" << endl;
        }
    } else {
        cout << "No" << endl
             << x1 << " " << y1 << endl;
    }

    return 0;
}