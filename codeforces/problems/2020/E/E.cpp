#include <bits/stdc++.h>
using namespace std;

const int64_t MOD = int64_t(1e9) + 7;

// Requires: 0 <= a < m and gcd(a, m) == 1
int64_t inv(int64_t a, int64_t m) { // a^(-1) % m
    return a <= 1 ? a : m - (m/a) * inv(m % a, m) % m;
}
const int64_t D = int64_t(1e4);
const int64_t inv1e4 = inv(D, MOD);

void solve() {
    int n;
    cin >> n;
    vector<int> a(n), p(n);
    for (auto &ai: a) cin >> ai;
    for (auto &pi: p) cin >> pi;
    vector<int64_t> dpprev(1<<10), dpnext(1<<10);
    dpprev[0] = 1;
    for (int i = 0; i < n; i++) {
        int64_t yes = (p[i] * inv1e4) % MOD;
        int64_t no = ((D-p[i]) * inv1e4) % MOD;
        for (int m = 0; m < (1 << 10); m++) {
            dpnext[m] = dpprev[m] * no;
            dpnext[m] += dpprev[m ^ a[i]] * yes;
            dpnext[m] %= MOD;
        }
        swap(dpnext, dpprev);
    }
    int64_t ans = 0;
    for (int m = 0; m < (1 << 10); m++) {
        ans += (dpprev[m] * ((m * m) % MOD)) % MOD;
    }
    ans %= MOD;
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
