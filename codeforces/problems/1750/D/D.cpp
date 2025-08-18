#include <bits/stdc++.h>
using namespace std;

const int64_t MOD = 998244353;

vector<int> prime_factor(int64_t n) {
    vector<int> ans;
    for(int64_t i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            while (n % i == 0) {
                n /= i;
            }
            ans.push_back(int(i));
        }
    }
    if (n != 1) {
        ans.push_back(int(n));
    }
    return ans;
}

vector<int> get_primes(int64_t x, const vector<int> &orig) {
    vector<int> ans;
    for (int p: orig) {
        if (x % p == 0) {
            ans.push_back(p);
        }
    }
    return ans;
}
int64_t get_possible_pie(const vector<int> &primes, int limit) {
    // it's not 2^log2(1e9), but actually:
    // 2^9 since the first 10 primes already go above 1e9
    // so we don't even need the last one (we can just use the first 9)
    int N = int(primes.size());
    int64_t ans = 0;
    for (int mask = 0; mask < (1 << N); mask++) {
        int sz = 0;
        int nr = 1;
        for (int i = 0; i < N; i++) {
            if (mask & (1 << i)) {
                sz++;
                nr *= primes[i];
            }
        }
        int cnt = limit / nr;
        if (sz & 1) {
            // odd
            ans -= cnt;
        }
        else {
            ans += cnt;
        }
    }
    return ans;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    int64_t ans = 1;
    vector<int> primes = prime_factor(a.front());
    for (int i = 1; i < n; i++) {
        int64_t cur;
        if (a[i - 1] % a[i] != 0) {
            cur = 0;
        }
        else {
            int64_t x = a[i - 1] / a[i];
            vector<int> xprimes = get_primes(x, primes);
            cur = get_possible_pie(xprimes, m / a[i]);
        }
        ans = ans * cur % MOD;
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
