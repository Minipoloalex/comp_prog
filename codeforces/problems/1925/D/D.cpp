#include <bits/stdc++.h>
using namespace std;

const int64_t MOD = int64_t(1e9) + 7;

int64_t powmod(int64_t a, int64_t b, int64_t p = MOD) {   // a^b % p
    if (b == 0) return 1;
    if (b % 2 == 1) return (a * powmod(a, b - 1, p)) % p;
    int64_t aux = powmod(a, b / 2, p);
    return (aux * aux) % p;
}

int64_t invmod(int64_t v, int64_t p) { // v^(-1) % p
    return powmod(v, p - 2, p);
}

const int MAX = int(2e5);

int64_t fact[MAX + 1];
int64_t invfact[MAX + 1];

void precompute_facts() {   // requires setting MAX and MOD
    fact[0] = 1;
    for (int i = 1; i <= MAX; i++) {
        fact[i] = (i * fact[i - 1]) % MOD;
    }
    // inverse factorial computation (for calculating combinations)
    invfact[MAX] = invmod(fact[MAX], MOD);
    for (int i = MAX - 1; i >= 0; i--) {
        invfact[i] = (invfact[i + 1] * (i + 1)) % MOD;
    }
}

int64_t comb(int64_t n, int64_t i) {
    assert(n >= i && n >= 0 && i >= 0);
    return (((fact[n] * invfact[n - i]) % MOD) * invfact[i]) % MOD;
}

void solve() {
    int n, k;
    int64_t m;
    cin >> n >> m >> k;
    int64_t sm = 0;
    int64_t P = (int64_t(n) * (n - 1) / 2) % MOD;
    for (int i = 0; i < m; i++) {
        int a, b, f;
        cin >> a >> b >> f;
        sm += f;
    }
    sm %= MOD;
    sm = sm * k % MOD;

    int64_t invP = invmod(P, MOD);
    int64_t one_minus_invP = (1 - invP + MOD) % MOD;
    int64_t ans = sm * invP % MOD;
    int64_t additional = 0;
    for (int i = 2; i <= k; i++) {
        // out of k, choose i times to be this pair
        int64_t bonus = (int64_t(i) * (i - 1) / 2) % MOD;
        int64_t prob = comb(k, i) * powmod(invP, i) % MOD * powmod(one_minus_invP, k - i) % MOD;
        additional += bonus * prob % MOD;
        additional %= MOD;
    }
    ans += additional * m % MOD;
    ans %= MOD;
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    cin >> t;
    precompute_facts();
    while (t--) {
        solve();
    }
    return 0;
}
