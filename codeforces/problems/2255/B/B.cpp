#include <bits/stdc++.h>
using namespace std;

int64_t MOD = 998244353;
const int MAX = int(1e6);

int64_t fact[MAX + 1];
int64_t invfact[MAX + 1];

int64_t powmod(int64_t a, int64_t b, int64_t p) {   // a^b % p
    if (b == 0) return 1;
    if (b % 2 == 1) return (a * powmod(a, b - 1, p)) % p;
    int64_t aux = powmod(a, b / 2, p);
    return (aux * aux) % p;
}

// Assumes p is prime
int64_t invmod(int64_t v, int64_t p) { // v^(-1) % p
    return powmod(v, p - 2, p);
}

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
    int n;
    cin >> n;
    string s;
    cin >> s;
    int c0 = int(count(s.begin(), s.end(), '0'));
    int c1 = n - c0;
    int loc[2] = {s[0] == '0', s[0] == '1'};
    for (int i = 1; i < n; i++) {
        if (s[i] != s[i-1]) {
            loc[s[i]-'0']++;
        }
    }
    int64_t ans = 1;
    if (c0 > 0) ans *= comb(c0-1, loc[0]-1);
    if (c1 > 0) ans *= comb(c1-1, loc[1]-1);
    ans %= MOD;
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    precompute_facts();
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
