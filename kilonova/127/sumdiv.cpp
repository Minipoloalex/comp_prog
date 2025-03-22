#include <bits/stdc++.h>
using namespace std;

const int MOD = int(1e9) + 7;

int64_t mod_exp(int64_t a, int64_t b, int64_t m) {
    if (b == 0) return 1;
    if (b & 1) return (a * mod_exp(a, b - 1, m)) % m;
    int64_t aux = mod_exp(a, b / 2, m);
    return (aux * aux) % m;
}

vector<pair<int,int>> get_factors(int64_t a) {
    vector<pair<int,int>> factors;
    factors.reserve((int)sqrt(a));
    for (int i = 2; i * i <= a; i++) {
        int cnt = 0;
        while (a % i == 0) {
            a /= i;
            cnt++;
        }
        if (cnt > 0) {
            factors.emplace_back(i, cnt);
        }
    }
    if (a > 1) {
        factors.emplace_back(a, 1);
    }
    return factors;
}

int64_t mod_inv(int64_t value, int64_t m) {
    return mod_exp(value, m - 2, m);
}

void solve() {
    int64_t a, b;
    cin >> a >> b;
    if (b == 0) {
        cout << "1\n";
        return;
    }
    vector<pair<int,int>> factors = get_factors(a);
    int64_t ans = 1;
    for (auto &[p, cnt]: factors) {
        int64_t value;
        if (p - 1 % MOD == 0) {
            // (p - 1) = k * MOD
            value = (1 + cnt * (b % MOD)) % MOD;
        }
        else {
            if (p % MOD == 0) {
                value = 0;
            }
            else {
                int64_t auxb = b % (MOD - 1);
                int64_t exponent = (cnt * auxb + 1) % (MOD - 1);
                value = mod_exp(p % MOD, exponent, MOD);
            }
            (value += MOD - 1) %= MOD;
            int64_t inv_p_minus_1 = mod_inv(p - 1, MOD);
            (value *= inv_p_minus_1) %= MOD;
        }
        (ans *= value) %= MOD;
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    freopen("sumdiv.in", "r", stdin);
    freopen("sumdiv.out", "w", stdout);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
