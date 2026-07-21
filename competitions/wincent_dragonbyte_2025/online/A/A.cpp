#include <bits/stdc++.h>
using namespace std;

#define lc(i) (2*(i))
#define rc(i) (2*(i) + 1)

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> g(n + 1);
    for (int i = 1; i <= n; i++) {
        int leftC = lc(i);
        int rightC = rc(i);
        if (leftC <= n) {
            g[i].push_back(leftC);
        }
        if (rightC <= n) {
            g[i].push_back(rightC);
        }
    }
    vector<int> depth(n + 1, 0), st(n + 1, 0);
    function<void(int)> dfs = [&](int u) {
        st[u] = 1;
        for (int v: g[u]) {
            depth[v] = depth[u] + 1;
            dfs(v);
            st[u] += st[v];
        }
    };
    dfs(1);

    vector<int64_t> pref(n + 2, 0);
    for (int i = 1; i <= n; i++) {
        int mn = st[i];
        int mx = n - depth[i];
        pref[mn]++;
        pref[mx+1]--;
    }
    for (int i = 1; i <= n; i++) {
        pref[i] += pref[i-1];
    }
    int64_t ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += i * pref[i];
    }
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
