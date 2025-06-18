#include <bits/stdc++.h>
using namespace std;

const int64_t MOD = int(1e9) + 7;
const int MAX = 500;

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
    assert(n >= i && n >= 0 && i >= 0);
    return (((fact[n] * invfact[n - i]) % MOD) * invfact[i]) % MOD;
}

void solve() {
    string s;
    cin >> s;
    int n = int(s.size());
    vector<vector<int64_t>> dp(n, vector<int64_t>(n, -1));
    function<int64_t(int,int)> go = [&](int i, int j) -> int64_t {
        if (i > j) return 1;
        // if (i == j) return 0;    // no need, because we start with idx = i + 1

        int64_t &ans = dp[i][j];
        if (ans != -1) return ans;

        int64_t cur = 0;
        for (int idx = i + 1; idx <= j; idx++) {
            if (s[i] == s[idx]) {
                // handle middle and after
                int64_t after = go(idx + 1, j);
                int64_t mid = go(i + 1, idx - 1);
                int rp = (j - idx) / 2;
                int lp = (idx - i + 1) / 2;
                // for each way of organizing the left and right indepedently (after * mid ways). we fix the way to organize the left and the right (and the order as well)
                // for each of these ways, we have a number of combinations depending on left pairs and right pairs (based on stars and bars)
                // Since we fixed a way, we have a specific ordering set for the left and for the right values, so:
                // Now, we just need to select the positions for the left (or the right) pairs
                int64_t v = comb(rp + lp, rp) * after % MOD * mid % MOD;
                cur = (cur + v) % MOD;
            }
        }
        return ans = cur;
    };
    int64_t ans = go(0, n - 1);
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    // cin >> t;
    precompute_facts();
    while (t--) {
        solve();
    }
    return 0;
}
