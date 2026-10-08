#include <bits/stdc++.h>
using namespace std;

string player;

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

// another mod inverse: b^(-1) % m
int modInverse(int b, int m) {
    int x, y;
    int d = extEuclidean(b, m, x, y);
    if (d != 1) return -1;  // b * x + m * y = 1, apply (mod m) to get b * x = 1 (mod m)
    return ((x % m) + m) % m;
}

void solve() {
    int64_t n;
    cin >> n;
    vector<string> g(n);
    for (auto &s: g) cin >> s;
    int64_t w = 0;
    char c = '#';
    for (string &s: g) w += count(s.begin(), s.end(), c);
    if (w > n * n - w) {
        w = n * n - w;
        c = '.';
    }
    int64_t R = 0, C = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (g[i][j] == c) {
                R += i;
                C += j;
            }
        }
    }
    R %= n; C %= n;

    if (player == "first") {
        int rx, cx;
        cin >> rx >> cx;
        rx--; cx--;

        // pull the "average" into where we want it: (rx, cx)
        int64_t dr = ((rx * w - R) % n + n) % n;
        int64_t dc = ((cx * w - C) % n + n) % n;
        if (dr == 0 && dc == 0) {
            cout << "1 1 1 1\n";
            goto res;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int ni = (i+dr) % n;
                int nj = (j+dc) % n;
                if (g[i][j] == c && g[ni][nj] != c) {
                    cout << i + 1 << " " << j + 1 << " " << ni + 1 << " " << nj + 1 << '\n';
                    goto res;
                }
            }
        }
        res:
    }
    else {
        assert(player == "second");
        int64_t invw = modInverse(w, n);
        R = R * invw % n;
        C = C * invw % n;
        cout << R % n + 1 << " " << C % n + 1 << '\n';
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> player;
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
