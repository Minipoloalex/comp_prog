#include <bits/stdc++.h>
using namespace std;

const int64_t MOD = 998244353;

int64_t powmod(int64_t a, int64_t b, int64_t p) {   // a^b % p
    if (b == 0) return 1;
    if (b % 2 == 1) return (a * powmod(a, b - 1, p)) % p;
    int64_t aux = powmod(a, b / 2, p);
    return (aux * aux) % p;
}

int64_t invmod(int64_t v, int64_t p) { // v^(-1) % p
    return powmod(v, p - 2, p);
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<array<int64_t,6>> segs(n);
    vector<int64_t> dp(m + 2, 0);
    vector<vector<int>> loc(m + 1);
    vector<int64_t> prefnotactive(m + 1, 1);
    for (int i = 0; i < n; i++) {
        auto &[l,r,p,q,not_active,active] = segs[i];
        cin >> l >> r >> p >> q;
        int64_t invq = invmod(q, MOD);
        not_active = ((1 - p * invq % MOD) + MOD) % MOD;
        active = p * invq % MOD;
        loc[l].push_back(i);
    }
    for (int i = 1; i <= m; i++) {
        prefnotactive[i] = prefnotactive[i - 1];
        for (int segidx: loc[i]) {
            prefnotactive[i] = prefnotactive[i] * segs[segidx][4] % MOD;
        }
    }
    auto get_not_active_prob = [&](int64_t l, int64_t r) {
        return prefnotactive[r] * invmod(prefnotactive[l - 1], MOD) % MOD;
    };
    dp[m + 1] = 1;
    for (int i = m; i >= 1; i--) {
        dp[i] = 0;
        for (int segidx: loc[i]) {
            auto &[l, r, p, q, not_active, active] = segs[segidx];
            int64_t none_active = get_not_active_prob(l, r);
            int64_t cur_active = none_active * invmod(not_active, MOD) % MOD * active % MOD;
            int64_t nxtidx = r + 1;
            dp[i] = (dp[i] + (cur_active * dp[nxtidx] % MOD)) % MOD;
        }
    }
    cout << dp[1] << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    // cout << 5 * invmod(18, MOD) % MOD << endl;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
