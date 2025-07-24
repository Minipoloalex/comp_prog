#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    map<int64_t,int,greater<int64_t>> mp;
    for (int i = 0; i < n; i++) {
        int ai;
        cin >> ai;
        mp[ai]++;
    }
    while (m--) {
        int bj, cj;
        cin >> bj >> cj;
        mp[cj] += bj;
    }
    int64_t ans = 0;
    int total_cnt = 0;
    for (auto &[val, cnt]: mp) {
        int prev_cnt = total_cnt;
        total_cnt = min(n, total_cnt + cnt);
        ans += (total_cnt - prev_cnt) * val;
        if (total_cnt == n) break;
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
