#include <bits/stdc++.h>
using namespace std;

uint64_t mod, alpha, be;
map<uint64_t, __uint128_t> dp; 

__uint128_t get(uint64_t e) {
    if (e == 0) return 2;
    if (e == 1) return alpha;
    if (dp.count(e)) return dp[e];

    if (e & 1) {
        uint64_t a = e / 2 + 1, b = e / 2;
        __uint128_t res = get(a) * get(b) % mod;
        res -= get(a - b);
        res = (res + mod) % mod;
        return dp[e] = res;
    } else {
        uint64_t a = e / 2;
        __uint128_t res = get(a);
        res *= res;
        res -= 2;
        res = (res + mod) % mod;
        return dp[e] = res;
    }
}

void solve() {
    cin >> alpha >> be >> mod;

    uint64_t ans = get(be);
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
