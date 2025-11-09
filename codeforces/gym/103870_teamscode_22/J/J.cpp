#include <bits/stdc++.h>
using namespace std;

int64_t MOD = int64_t(1e9) + 7;

void solve() {
    int64_t a, l, r, n;
    cin >> a >> l >> r >> n;
    int64_t nsquare = n*n%MOD;
    int64_t ncube = nsquare*n%MOD;
    int64_t ans = 0;
    ans += ncube;               // *
    ans += ncube - nsquare;     // +
    ans += nsquare;             // =
    ans += nsquare;             // ;
    ans += ncube*l%MOD;         // left
    ans += ncube*r%MOD;         // right
    ans += ncube*8+4*nsquare;   // []
    ans += nsquare*a%MOD;       // result
    int64_t each_nr_freq = (4*nsquare+2*n) % MOD;
    int64_t before = 0;
    int64_t cur = 1;
    for (int d = 1; before < n; d++) {
        cur *= 10;
        int64_t cnt = min(cur, n) - before;
        before += cnt;
        ans += (cnt * d % MOD) * each_nr_freq % MOD;
    }
    cout << ((ans % MOD) + MOD) % MOD << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
}
