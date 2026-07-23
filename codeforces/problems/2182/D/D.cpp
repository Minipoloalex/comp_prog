#include <bits/stdc++.h>
using namespace std;

const int64_t MOD = 998244353;

const int MAX = int(55);

int64_t fact[MAX + 1];
int64_t invfact[MAX + 1];

int64_t mod_pow(int64_t b, int64_t e, int64_t m) {
    int64_t res = 1;
    for (; e; e >>= 1) {
        if (e & 1) res = res * b % m;
        b = b * b % m;
    }
    return res;
}

int64_t mod_inv(int64_t n, int64_t m) {
    return mod_pow(n, m - 2, m);
}

void precompute_facts() {
    fact[0] = 1;
    for (int i = 1; i <= MAX; i++) {
        fact[i] = (i * fact[i - 1]) % MOD;
    }
    invfact[MAX] = mod_inv(fact[MAX], MOD);
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
    vector<int> a(n+1);
    for (auto &x: a) cin >> x;
    auto st = a.begin() + 1;
    int mx = *max_element(st, a.end());
    int sm = accumulate(st, a.end(), 0);
    // there is a better way to generalize this using this definition of F instead of A
    // need (cost to reach mx iterations with all): A, not mx cnt: B, mx cnt: C, have: D (a[0]), can a[0] at last iteration: F
    int D = a[0];
    int A = mx * n - sm;
    int C = int(count(st, a.end(), mx));
    int B = n - C;
    int E = (mx-1) * B - (sm - mx * C); // sum of not maxes to all reach (mx-1) iterations
    int F = D - E;
    int64_t ans;
    // if (D >= A) {
    if (F >= B) {
        ans = fact[n];
    }
    // else if (A - B > D) {
    else if (F < 0) {
        ans = 0;
    }
    else {
        // cout << comb(F+C, C) << " " << fact[C] << " " << fact[n-C] << endl;
        ans = (comb(F+C, C) * fact[C] % MOD) * fact[n-C] % MOD;
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    cin >> t;
    precompute_facts();
    while (t--) {
        solve();
    }
    return 0;
}
