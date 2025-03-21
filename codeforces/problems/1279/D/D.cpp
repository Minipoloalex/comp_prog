#include <bits/stdc++.h>
using namespace std;

/*
for each kid a, for each other kid b, add up |intersection(a, b)| / |a|
*/
const int MAX_P = int(1e6);
const int MOD = 998244353;

int64_t mod_exp(int64_t a, int64_t b, int64_t m) {
    if (b == 0) return 1;
    if (b & 1) return (a * mod_exp(a, b - 1, m)) % m;
    int64_t aux = mod_exp(a, b / 2, m);
    return (aux * aux) % m;
}

int64_t inv(int64_t x, int64_t m) {
    return mod_exp(x, m - 2, m);
}

void solve() {
    int n;
    cin >> n;
    // for each item, how many kids have this item in their list? easy to get
    // for each kid: we know its size of wanted presents. then we just need to know how many out of the others have it and calc it
    vector<int> cnt(MAX_P + 1, 0);
    vector<vector<int>> kids(n);
    for (auto &v: kids) {
        int ki;
        cin >> ki;
        v.resize(ki);
        for (auto &x: v) {
            cin >> x;
            cnt[x]++;
        }
    }
    int64_t inv_n2 = inv((int64_t(n) * n) % MOD, MOD);
    int64_t ans = 0;
    for (int i = 0; i < n; i++) {
        int ks = (int) kids[i].size();
        int64_t inv_ks = inv(ks, MOD);
        int64_t inv_den = (inv_ks * inv_n2) % MOD;

        int64_t num = 0;
        // for each kid and each present: prob = (1 / ks) * (havep / n)
        for (int ki = 0; ki < ks; ki++) {
            int p = kids[i][ki];
            int havep = cnt[p];
            num += havep;
        }
        (ans += (num * inv_den) % MOD) %= MOD;
    }
    cout << ans << '\n';
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
