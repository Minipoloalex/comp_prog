#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<array<int,3>> ps(n);
    vector<int> vals;
    vals.reserve(2*n);
    for (auto &[b, a, p]: ps) {
        cin >> a >> b >> p;
        b++;    // [a, b), a < b
        vals.push_back(a);
        vals.push_back(b);
    }
    sort(ps.begin(), ps.end());

    sort(vals.begin(), vals.end());
    int sz = int(vals.size());
    auto idx = [&](int val) {
        return int(lower_bound(vals.begin(), vals.end(), val) - vals.begin());
    };

    vector<int64_t> dp(sz);
    dp[0] = 0;  // minimum value of a in the projects
    int pid = 0;
    for (int i = 1; i < sz; i++) {
        int pos = vals[i];
        int64_t best = dp[i-1]; // skip the job (if there's any) at "position" i (the job's b is in i)
        while (pid < n && ps[pid][0] == pos) {
            // try taking this job
            auto &[b, a, c] = ps[pid];
            best = max(best, c + dp[idx(a)]);
            pid++;
        }
        dp[i] = best;
    }
    cout << dp[sz - 1] << '\n';
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
