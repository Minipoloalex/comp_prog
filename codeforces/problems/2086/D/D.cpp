#include <bits/stdc++.h>
using namespace std;

const int MAX = int(5e5);
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
    vector<int> cnt(27), pref(27);
    for (int i = 1; i <= 26; i++) {
        cin >> cnt[i];
        pref[i] = pref[i - 1] + cnt[i];
    }
    int n = pref[26];

    vector<vector<int64_t>> dp(n + 1, vector<int64_t>(27, 0));
    for (int i = 0; i <= n; i++) {
        dp[i][0] = 1;
    }
    for (int c = 1; c <= 26; c++) {
        for (int e = 0; e <= (n + 1) / 2; e++) {
            if (cnt[c] == 0) {
                dp[e][c] = dp[e][c-1];
                continue;
            }
            int odds = pref[c] - e;
            dp[e][c] = 0;
            if (cnt[c] <= odds) {
                dp[e][c] = (dp[e][c-1] * comb(odds, cnt[c])) % MOD;
            }
            if (e >= cnt[c]) {
                dp[e][c] = (dp[e][c] + dp[e-cnt[c]][c-1] * comb(e,cnt[c])) % MOD;
            }
        }
    }
    int64_t ans = dp[(n + 1) / 2][26];
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    precompute_facts();
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
