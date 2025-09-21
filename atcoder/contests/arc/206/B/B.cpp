#include <bits/stdc++.h>
using namespace std;

int find_lds(vector<int> &arr) {
    int n = int(arr.size());
    vector<int> ans(n, INT_MAX);
    int mx = 0;
    for (int i = 0; i < n; i++) {
        int idx = int(lower_bound(ans.begin(), ans.end(), arr[i]) - ans.begin());
        ans[idx] = arr[i];
        mx = max(mx, idx + 1);
    }
    return mx;
}

void solve() {
    int n;
    cin >> n;
    vector<int> p(n), c(n);
    for (auto &pi: p) cin >> pi;
    for (auto &ci: c) cin >> ci;
    // color to vector of slime sizes with that color (in order they appear in p)
    vector<vector<int>> slimes(n + 1);
    for (int i = 0; i < n; i++) {
        slimes[c[i]].push_back(p[i]);
    }

    int64_t ans = 0;
    for (int x = 1; x <= n; x++) {
        vector<int> &sls = slimes[x];
        if (!sls.empty()) {
            int lds_sz = find_lds(sls);
            ans += (int(sls.size()) - lds_sz) * 1LL * x;
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
