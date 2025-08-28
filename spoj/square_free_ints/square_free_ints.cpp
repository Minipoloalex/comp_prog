#include <bits/stdc++.h>
using namespace std;

const int64_t MOBIUS_MAX = int64_t(1e7);
int64_t mobius[MOBIUS_MAX + 1];

void sieve_mobius() {
    mobius[1] = -1;
    for (int i = 1; i <= MOBIUS_MAX; i++) {
        if (mobius[i]) {
            mobius[i] = -mobius[i];
            for (int j = 2 * i; j <= MOBIUS_MAX; j += i) {
                mobius[j] += mobius[i];
            }
        }
    }
}

void solve() {
    int64_t n;
    cin >> n;
    int64_t ans = 0;
    for (int64_t i = 1; i * i <= n; i++) {
        int64_t cnt = n / (i * i); 
        ans += mobius[i] * cnt;
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    cin >> t;
    sieve_mobius();
    while (t--) {
        solve();
    }
    return 0;
}
