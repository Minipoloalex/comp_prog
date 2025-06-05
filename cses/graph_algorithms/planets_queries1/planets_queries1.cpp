#include <bits/stdc++.h>
using namespace std;

const int MAXN = int(2e5);
const int MAXK = 31;

int up[MAXN][MAXK]; // using a vector instead could TLE (by very little: got AC with 1.0s)

void solve() {
    int n, q;
    cin >> n >> q;

    for (int i = 0; i < n; i++) {
        cin >> up[i][0];
        up[i][0]--;
    }
    for (int p = 1; p < MAXK; p++) {
        for (int i = 0; i < n; i++) {
            up[i][p] = up[up[i][p - 1]][p - 1];
        }
    }
    while (q--) {
        int x, k;
        cin >> x >> k;
        x--;
        for (int p = 0; p < MAXK; p++) {
            if ((1 << p) & k) {
                x = up[x][p];
            }
        }
        cout << x + 1 << '\n';
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
