#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<pair<int64_t,int64_t>> vals(n);
    for (auto &[b, a]: vals) cin >> a;
    for (auto &[b, a]: vals) cin >> b;
    int64_t total = 0;
    for (int i = 0; i < n; i++) {
        auto [bi, ai] = vals[i];
        vals[i].second = max(ai, bi);
        vals[i].first = min(ai, bi);
        total += abs(vals[i].second - vals[i].first);
    }
    sort(vals.begin(), vals.end());
    int64_t additional = INT64_MAX;
    int64_t prefmx = vals[0].second;
    for (int i = 1; i < n; i++) {
        auto [bi, ai] = vals[i];
        int64_t cur_mx = prefmx;
        if (cur_mx >= bi) {
            additional = 0;
            break;
        }
        else {
            additional = min(additional, 2 * bi - 2 * cur_mx);
        }
        prefmx = max(prefmx, ai);
    }
    int64_t ans = total + additional;

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
