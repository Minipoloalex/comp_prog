#include <bits/stdc++.h>
using namespace std;

const int MAX = 20;
int64_t c[MAX+1][MAX+1];

void precompute() {
    memset(c, 0, sizeof(c));
    for (int i = 0; i <= MAX; i++) {
        c[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            c[i][j] = c[i-1][j-1] + c[i-1][j];
        }
    }
}
int64_t comb(int n, int i) {
    return c[n][i];
}

void solve() {
    int n, m; int64_t y;
    cin >> n >> m >> y;
    vector<int64_t> a(n);
    for (auto &ai: a) cin >> ai;

    int64_t ans = 0;
    for (int mask = 1; mask < (1 << n); mask++) {
        int64_t cur = 1;    // lcm
        bool possible = true;
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                __int128_t v = (__int128_t)cur * a[i] / gcd(cur, a[i]);
                if (v > y) {
                    possible = false;
                    break;
                }
                cur = (int64_t) v;
                cnt++;
            }
        }
        if (!possible) continue;
        int64_t years = y / cur;
        if (cnt >= m) {
            if ((cnt - m) % 2 == 0) {
                ans += comb(cnt, m) * years;   
            }
            else {
                ans -= comb(cnt, m) * years;                
            }
        }
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    // cin >> t;
    precompute();
    while (t--) {
        solve();
    }
    return 0;
}
