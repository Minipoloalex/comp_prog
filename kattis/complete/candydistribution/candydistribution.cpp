#include <bits/stdc++.h>
using namespace std;

int mod(int a, int m) { // to assure it's positive
    return ((a % m) + m) % m;
}

int extEuclidean(int a, int b, int &x, int &y) {
    int xx = y = 0;
    int yy = x = 1;
    while (b) {
        int q = a/b;
        int t = b; b = a % b; a = t;    // a, b = b, a % b
        t = xx; xx = x - q*xx; x = t;
        t = yy; yy = y - q*yy; y = t;
    }
    return a;   // returns gcd(a, b)
}

int main() {
    int t;
    cin >> t;
    while (t--) {  // t < 100
        int k, c;   // k, c [1, 1e9]
        cin >> k >> c;
        // n_candy_bags <= 1e9
        if (k == 1 || c == 1) {
            if (c == 1) cout << k + 1 << endl;
            else cout << 1 << endl;
            continue;
        }
        int x, y;
        int _gcd = extEuclidean(c, k, x, y);
        if (_gcd != 1) {
            cout << "IMPOSSIBLE" << endl;
        }
        else {
            // cout << c << " * " << x << " + " << k << " * " << y << " = " << 1 << endl;
            cout << mod(x, k) << endl;
        }
    }
    return 0;
}
