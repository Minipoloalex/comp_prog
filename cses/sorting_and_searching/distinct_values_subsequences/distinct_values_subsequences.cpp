#include <bits/stdc++.h>
using namespace std;

const int64_t MOD = int64_t(1e9) + 7;

void solve() {
    int n;
    cin >> n;
    map<int,int> mp;
    for (int i = 0; i < n; i++) {
        int xi;
        cin >> xi;
        mp[xi]++;
    }
    int64_t ans = 1;
    for (auto &[v, cnt]: mp) {
        ans = ans * (cnt + 1) % MOD;    // choose to take one or not
    }
    cout << ans - 1 << '\n';
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
