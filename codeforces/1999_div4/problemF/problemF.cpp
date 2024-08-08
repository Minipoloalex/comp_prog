#include <bits/stdc++.h>
using namespace std;

const int64_t MOD = int64_t(1e9) + 7;
const int64_t MAX_N = int(2e5) + 10;
int64_t fact[MAX_N];


int64_t mod(int64_t a, int64_t m) { // to ensure it's positive
    return ((a % m) + m) % m;
}

void calculate_fact(int n) {
    fact[0] = 1;
    for (int i = 1; i < n; i++) {
        fact[i] = mod(i * fact[i - 1], MOD);
    }
}

int64_t extEuclidean(int64_t a, int64_t b, int64_t &x, int64_t &y) {
    int64_t xx = y = 0;
    int64_t yy = x = 1;
    while (b) {
        int64_t q = a/b;
        int64_t t = b; b = a % b; a = t;    // a, b = b, a % b
        t = xx; xx = x - q*xx; x = t;
        t = yy; yy = y - q*yy; y = t;
    }
    return a;   // returns gcd(a, b)
}

int64_t modInverse(int64_t b, int64_t m) {
    int64_t x, y;
    int64_t d = extEuclidean(b, m, x, y);
    if (d != 1) return -1;  // b * x + m * y = 1, apply (mod m) to get b * x = 1 (mod m)
    return mod(x, m);
}

int64_t comb(int n, int k) {
    if (k > n) return 0;
    return mod(fact[n] * mod(modInverse(mod(fact[k] * fact[n - k], MOD), MOD), MOD), MOD);
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cout.tie(0);

    calculate_fact(MAX_N);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;

        int count_1s = 0;       
        for (int i = 0; i < n; i++) {
            int ai;
            cin >> ai;
            count_1s += ai;
        }
        int count_0s = n - count_1s;

        int64_t ans = 0;
        for (int nr1s = (k + 1) / 2; nr1s <= min(count_1s, k); nr1s++) {
            int nr0s = k - nr1s;
            // cout << nr1s << "/" << count_1s << ", " << nr0s << "/" << count_0s << " " << comb(count_1s, nr1s) << " " << comb(count_0s, nr0s) << '\n';
            int64_t contribution = mod(comb(count_1s, nr1s) * comb(count_0s, nr0s), MOD);
            ans = mod(ans + contribution, MOD);
        }
        cout << ans << '\n';
    }
    return 0;
}
