#include <bits/stdc++.h>
using namespace std;

const uint64_t MOD = uint64_t(1e9) + 7;
const int MAX = int(1e5);

uint64_t fact[MAX+1];

void precompute_facts() {
    fact[0] = 1;
    for (int i = 1; i <= MAX; i++) {
        fact[i] = fact[i-1] * i % MOD;
    }
}

uint64_t powmod(uint64_t a, uint64_t b, uint64_t p) {   // a^b % p
    if (b == 0) return 1;
    if (b % 2 == 1) return (a * powmod(a, b - 1, p)) % p;
    uint64_t aux = powmod(a, b / 2, p);
    return (aux * aux) % p;
}

// Assumes p is prime
uint64_t invmod(uint64_t v, uint64_t p) { // v^(-1) % p
    return powmod(v, p - 2, p);
}


uint64_t comb(uint64_t n, uint64_t i) {
    assert(n >= i && n >= 0 && i >= 0);
    uint64_t o = n - i;
    if (o < i) swap(o, i);
    uint64_t ans = 1;
    for (uint64_t v = n; v > o; v--) {
        ans = ans * v % MOD; // 10^10 * 10^9 fits within uint64_t
    }
    return (ans * invmod(fact[i], MOD)) % MOD;
}

void solve() {
    int a, b, k;
    cin >> a >> b >> k;
    uint64_t n = uint64_t(a-1)*k + 1;
    uint64_t P = comb(n, a);
    uint64_t m = (P * k % MOD * (b-1) + 1) % MOD;
    cout << n % MOD << " " << m << '\n';
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
