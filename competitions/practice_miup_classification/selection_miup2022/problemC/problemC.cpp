#include <bits/stdc++.h>
using namespace std;

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

int smallest_multiple(int a, int b) {
    int x, y;
    return a * b / extEuclidean(a, b, x, y);
}

int main() {
    int k;
    cin >> k;
    int res = INT_MAX;
    for (int i = 0; i < k; i++) {
        int y;
        int c1;
        int c2;
        cin >> y >> c1 >> c2;
        int r = y + smallest_multiple(c1, c2);
        if (r < res) res = r;
    }
    cout << res << endl;
    return 0;
}
