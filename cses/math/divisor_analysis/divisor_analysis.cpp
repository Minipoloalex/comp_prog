#include <bits/stdc++.h>
using namespace std;

const int64_t MOD = int(1e9) + 7;

int64_t powmod(int64_t a, int64_t b, int64_t p) {   // a^b % p

    if (b == 0) return 1;
    if (b % 2 == 1) return (a * powmod(a, b - 1, p)) % p;
    int64_t aux = powmod(a, b / 2, p);
    return (aux * aux) % p;
}

int64_t invmod(int64_t v, int64_t p) { // v^(-1) % p
    return powmod(v, p - 2, p);
}

void solve() {
    int n;
    cin >> n;
    // MOD never divides our value (because prime factors <= 1e6)
    vector<pair<int64_t,int64_t>> factors(n);
    bool perfect = true;
    for (auto &[x, k]: factors) {
        cin >> x >> k;
        if (k % 2 == 1) {
            perfect = false;
        }
    }
    int64_t num_divisors = 1, sum_divisors = 1;
    int64_t MOD_PHI = MOD - 1;

    int64_t val_n_mod = 1;  // only used if non-perfect square
    int64_t sqrt_n_mod = 1; // only used if perfect square
    int64_t exp_prod = 1;
    bool divided_by_2 = false;  // only used if non-perfect square

    for (auto &[x, k]: factors) {
        num_divisors = num_divisors * (k + 1) % MOD;
        int64_t sum_term = (((powmod(x, k + 1, MOD) - 1) * invmod(x - 1, MOD)) + MOD) % MOD;
        sum_divisors = sum_divisors * sum_term % MOD;
        if (perfect) {
            sqrt_n_mod = sqrt_n_mod * powmod(x, k / 2, MOD) % MOD;
            exp_prod = exp_prod * (k + 1) % MOD_PHI;
        }
        else {
            val_n_mod = val_n_mod * powmod(x, k, MOD) % MOD;
            if (!divided_by_2 && (k + 1) % 2 == 0) {
                exp_prod = exp_prod * ((k + 1) / 2) % MOD_PHI;
                divided_by_2 = true;
            }
            else exp_prod = exp_prod * (k + 1) % MOD_PHI;
        }
    }
    // using if with (divnr % 2 == 1) doesn't work because divnr has been % MOD
    int64_t prod_divisors;
    if (perfect) {
        // odd number of divisors: perfect square
        // Note that: (sqrt(N % MOD)) % MOD != sqrt(N) % MOD
        prod_divisors = powmod(sqrt_n_mod, exp_prod, MOD) % MOD;
    }
    else {
        prod_divisors = powmod(val_n_mod, exp_prod, MOD);
    }
    cout << num_divisors << " " << sum_divisors << " " << prod_divisors << '\n';
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
