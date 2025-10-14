#include <bits/stdc++.h>
using namespace std;

const int MAX = 31622779;

void solve() {
    int m, n, k;
    cin >> m >> n >> k;
    vector<int64_t> c(n);
    for (auto &ci: c) cin >> ci;
    vector<vector<pair<int,int>>> g(m);
    while (k--) {
        int j, i, d;
        cin >> j >> i >> d;
        j--;i--;
        g[j].emplace_back(i, d);
    }
    int cur = 0;
    vector<int64_t> ans(m);
    for (int64_t x = 2; x <= MAX && cur < m; x++) {
        int fst = g[cur].front().first;
        if (c[fst] % x == 0) {
            ans[cur] = x;
            for (auto &[i, d]: g[cur]) {
                for (int tm = 0; tm < d; tm++) {
                    c[i] /= x;
                }
            }
            cur++;
        }
    }
    vector<int64_t> lef;
    for (int i = 0; i < n; i++) {
        if (c[i] != 1) {
            lef.push_back(c[i]);
        }
    }
    sort(lef.begin(), lef.end());
    lef.erase(unique(lef.begin(), lef.end()), lef.end());
    assert(lef.size() == m - cur);
    for (int i = cur; i < m; i++) {
        ans[i] = lef[i - cur];
    }
    for (int i = 0; i < m; i++) {
        cout << ans[i] << " \n"[i == m - 1];
    }
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
