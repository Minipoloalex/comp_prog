#include <bits/stdc++.h>
using namespace std;

const int64_t MOD = 998244353;
const int MAX = int(1e6);

int64_t fact[MAX + 1];
int64_t invfact[MAX + 1];

int64_t powmod(int64_t a, int64_t b, int64_t p) {
    if (b == 0) return 1;
    if (b % 2 == 1) return (a * powmod(a, b - 1, p)) % p;
    int64_t aux = powmod(a, b / 2, p);
    return (aux * aux) % p;
}

int64_t invmod(int64_t v) {
    return powmod(v, MOD - 2, MOD);
}

void precompute_facts() {
    fact[0] = 1;
    for (int i = 1; i <= MAX; i++) {
        fact[i] = (i * fact[i - 1]) % MOD;
    }
    invfact[MAX] = invmod(fact[MAX]);
    for (int i = MAX - 1; i >= 0; i--) {
        invfact[i] = (invfact[i + 1] * (i + 1)) % MOD;
    }
}

int64_t comb(int64_t n, int64_t i) {
    // cout << n << " " << i << endl;
    assert(n >= i && n >= 0 && i >= 0);
    return (((fact[n] * invfact[n - i]) % MOD) * invfact[i]) % MOD;
}

void solve() {
    int64_t n, k, q, x;
    cin >> n >> k >> q >> x;
    precompute_facts();
    auto value = [&](int r, int c) -> int64_t {
        if (c == 0) return 0;
        return comb(r + c - 1, c - 1);
    };

    while (q--) {
        int i, l, r;
        cin >> i >> l >> r;
        int64_t ans = (value(i + 1, r) - value(i + 1, l - 1) + MOD) % MOD;
        cout << ans * x % MOD << '\n';
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
