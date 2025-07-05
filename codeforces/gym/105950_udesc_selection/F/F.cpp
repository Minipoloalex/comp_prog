#include <bits/stdc++.h>
using namespace std;

void solve() {
    int64_t n, f, s;
    cin >> n >> f >> s;

    vector<int64_t> p(n), q(n);
    for (auto& x : p) { cin >> x; x--; }
    for (auto& x : q) { cin >> x; x--; }

    map<int64_t, int> pos;
    for (int i = 0; i < n; i++) pos[q[i]] = i;

    vector<array<int, 2>> segp, segq;
    for (int i = 0; i < n; i++) {
        int j = pos[p[i]];
        int t = i;
        for (; t < n && j < n && p[t] == q[j]; t++, j++) {}
        segp.push_back({i, t - 1});
        segq.push_back({pos[p[i]], j - 1});
        i = t - 1;
    }

    int segs = int(segp.size());

    int64_t ans = int64_t(1e18);
    for (int i = 0; i < segs; i++) {
        auto [lp, rp] = segp[i];
        auto [lq, rq] = segq[i];

        int64_t left = (lp + lq) * f;
        int64_t right = ((n - rp - 1) + (n - rq - 1)) * s;
        ans = min(ans, max(left, right));
    }

    cout << ans << endl;
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
