#include <bits/stdc++.h>
using namespace std;


void solve() {
    int n, k;
    cin >> n >> k;
    vector<array<int,3>> groups(n);
    for (auto &[a, b, c]: groups) cin >> a >> b >> c;   // already sorted by A
    vector<int64_t> ans(n);

    using E = pair<int64_t,int>; // time, group id
    set<E> s;
    int cur = 0;
    int64_t last_time = 0;

    int occ = 0;
    while (cur < n) {
        while (cur < n && occ + groups[cur][2] <= k) {
            auto &[a, b, c] = groups[cur];
            int64_t enter_tm = max<int64_t>(a, last_time);
            ans[cur] = enter_tm;
            s.emplace(enter_tm + b, cur);  // schedule leaving
            occ += c;
            cur++;
        }
        auto [tm, gid] = *s.begin();
        s.erase(s.begin());
        auto &[a, b, c] = groups[gid];
        occ -= c;
        last_time = tm;
    }
    for (int64_t v: ans) cout << v << '\n';
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
