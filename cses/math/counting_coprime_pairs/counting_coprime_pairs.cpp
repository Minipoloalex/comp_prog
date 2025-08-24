#include <bits/stdc++.h>
using namespace std;

const int MAX = int(1e6);
int divcnt[MAX + 1];

void divisors(int n) {
    for (int i = 1; 1LL * i * i <= n; i++) {
        if (n % i == 0) {
            divcnt[i]++;
            if (n / i != i) {
                divcnt[n / i]++;
            }
        }
    }
}
vector<int> distinct_primes(int n) {
    vector<int> ans;
    for (int i = 2; 1LL * i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0) {
                n /= i;
            }
            ans.push_back(i);
        }
    }
    if (n != 1) ans.push_back(n);
    return ans;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);

    // because my primes approach doesn't actually remove them, so I need to do it manually
    int ones_cnt = 0;

    for (auto &ai: a) {
        cin >> ai;
        if (ai == 1) ones_cnt++;
    }
    for (int i = 0; i < n; i++) divisors(a[i]);

    int64_t ans = 0;
    for (int i = 0; i < n; i++) {
        vector<int> primes = distinct_primes(a[i]);
        int SZ = int(primes.size());
        int64_t cur = 0;
        for (int m = 0; m < (1 << SZ); m++) {
            int cnt = 0;
            int mult = 1;
            for (int j = 0; j < SZ; j++) {
                if (m & (1 << j)) {
                    cnt++;
                    mult *= primes[j];
                }
            }
            // p1 and p2 and ... and pk
            if (cnt % 2 == 1) {
                cur -= divcnt[mult];
            }
            else {
                cur += divcnt[mult];
            }
        }
        ans += cur;
    }
    ans -= ones_cnt;    // now we only have the pairs
    ans /= 2;
    cout << ans << '\n';
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
