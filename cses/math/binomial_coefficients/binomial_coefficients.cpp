#include <bits/stdc++.h>
using namespace std;

const int64_t MOD = int(1e9) + 7;
const int64_t MAX = int(1e6);

int64_t fact[MAX + 1];
int64_t invfact[MAX + 1];

int64_t powmod(int64_t a, int64_t b, int64_t m) {
    if (b == 0) return 1;
    if (b & 1) return a * powmod(a, b - 1, m) % m;
    int64_t aux = powmod(a, b / 2, m);
    return aux * aux % m;
}

void precompute() {
    fact[0] = 1;
    for (int i = 1; i <= MAX; i++) {
        fact[i] = fact[i - 1] * i % MOD;
    }
    invfact[MAX] = powmod(fact[MAX], MOD - 2, MOD);
    for (int i = MAX - 1; i >= 0; i--) {
        invfact[i] = invfact[i + 1] * (i + 1) % MOD;
    }
}

int64_t comb(int64_t n, int64_t i) {
    return fact[n] * invfact[i] % MOD * invfact[n - i] % MOD;
}

void solve() {
    int a, b;
    cin >> a >> b;
    cout << comb(a, b) << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    precompute();
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
