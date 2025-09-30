#include <bits/stdc++.h>
using namespace std;

int64_t powmod(int64_t a, int64_t b, int64_t p) {   // a^b % p
    if (b == 0) return 1;
    if (b % 2 == 1) return (a * powmod(a, b - 1, p)) % p;
    int64_t aux = powmod(a, b / 2, p);
    return (aux * aux) % p;
}

int64_t invmod(int64_t v, int64_t p) { // v^(-1) % p
    return powmod(v, p - 2, p);
}

const int64_t MOD = int64_t(1e9) + 7;
int64_t inv2 = invmod(2, MOD);

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> x(q);
    for (auto &xi: x) cin >> xi;

    vector<int64_t> vals(q);
    int64_t cur = 1;
    for (int i = 0; i < q; i++) {
        cur *= inv2;
        cur %= MOD;
        vals[i] = cur * x[i];
        vals[i] %= MOD;
    }
    vector<int64_t> suf(q + 1);
    for (int i = q - 1; i >= 0; i--) { 
        suf[i] = (suf[i + 1] + vals[i]) % MOD;
    }
    vector<vector<int>> occ(n + 1);
    for (int i = 0; i < q; i++) {
        occ[x[i]].push_back(i);
    }
    vector<int64_t> ans(n+1);
    ans[1] += suf[0];
    for (int i = 1; i <= n; i++) {
        for (int pos: occ[i]) {
            ans[i] += suf[pos + 1] * powmod(2, pos, MOD);
            ans[i] %= MOD;
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << '\n';
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
