#include <bits/stdc++.h>
using namespace std;

const int64_t MOD = 998244353;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    int64_t ans = 0;
    for (int b = 0; b < 31; b++) {
        int cur = 0;
        array<int64_t,2> cnt = {1, 0}, sm = {0, 0};
        for (int i = 1; i <= n; i++) {
            cur ^= (a[i] & (1 << b)) >> b;
            int opposite = cur ^ 1;
            int64_t contribution = ((i * cnt[opposite] - sm[opposite]) % MOD + MOD % MOD) << b;
            ans = (ans + contribution) % MOD;
            cnt[cur]++;
            sm[cur] += i;
        }
    }
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
