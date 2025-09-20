#include <bits/stdc++.h>
using namespace std;

const int MAX_VALUE = int(1e6); // max value of prime detected
bitset<MAX_VALUE + 1> bs;       // if bs[i] = 1: i is prime
int pref_primes[MAX_VALUE + 1]; // pref_primes[i]: how many primes are <= i

void sieve(int64_t upper) {  // can be shown complexity is O(N log(log N))
    // sieve includes [0, upper]
    int64_t sieve_size = upper + 1;
    bs.set();
    bs[0] = bs[1] = 0;
    for (int64_t i = 2; i < sieve_size; i++) {
        pref_primes[i] = pref_primes[i - 1];
        if (bs[i]) {
            pref_primes[i]++;   // i is prime
            for (int64_t j = i * i; j < sieve_size; j += i) bs[j] = 0;
        }
    }
}

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> p(k);
    for (auto &pi: p) cin >> pi;
    if (n == 0) {
        cout << "0\n";
        return;
    }
    int ans = 0;
    for (int mask = 0; mask < (1 << k); mask++) {
        int cur = 1;
        for (int i = 0; i < k && cur <= n; i++) {
            if (mask & (1 << i)) {
                cur *= p[i];
            }
        }
        int cnt = n / cur;
        if (__builtin_parity(mask) == 1) {
            ans -= cnt;
        }
        else {
            ans += cnt;
        }
    }
    int cnt_primes_before_n = 0;
    for (int i = 0; i < k; i++) {
        if (p[i] <= n) {
            cnt_primes_before_n++;
        }
    }
    cout << ans - (pref_primes[n] - cnt_primes_before_n) - 1 << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    cin >> t;
    sieve(MAX_VALUE);
    for (int i = 1; i <= t; i++) {
        cout << "Case " << i << ": ";
        solve();
    }
    return 0;
}
