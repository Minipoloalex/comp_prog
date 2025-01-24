#include <bits/stdc++.h>
using namespace std;

int64_t n, k;
int64_t get_cnt(int64_t p) {
    return n / p;
}
const int64_t MAX = int64_t(1e18);

void solve() {
    cin >> n >> k;
    vector<int64_t> a(k);
    for (auto &x: a) cin >> x;

    int64_t ans = 0;
    for (int i = 1; i < (1 << k); i++) {
        int64_t p = 1;
        int cnt = 0;
        for (int j = 0; j < k; j++) {   // which primes are in the subset
            if (i & (1 << j)) {
                cnt++;
                if (p > n / a[j]) {
                    p = n + 1;
                }
                else p *= a[j]; // no need to divide by gcd(p, a[j]) because they are distinct prime numbers
            }
        }
        if (cnt % 2 == 0) {
            ans -= get_cnt(p);
        }
        else {
            ans += get_cnt(p);
        }
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
