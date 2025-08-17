#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    int64_t w;
    cin >> n >> w;
    // there's a much better solution: see editorial code
    vector<int> par(n);
    for (int i = 1; i < n; i++) {
        cin >> par[i];
        par[i]--;
    }
    par[0] = -1;
    int64_t total = w * n;

    vector<int64_t> vals(n, -1);
    vector<int64_t> smaffected(n, 0);
    vector<int> mx_subtree(n, -1);
    vector<vector<int>> g(n);
    for (int i = 1; i < n; i++) {
        g[par[i]].push_back(i);
    }
    function<void(int)> dfs = [&](int u) {
        mx_subtree[u] = u;
        for (int v: g[u]) {
            dfs(v);
            mx_subtree[u] = max(mx_subtree[u], mx_subtree[v]);
        }
    };
    vector<int> cntedges(n);
    for (int i = 0; i < n; i++) {
        int target = (i + 1) % n;
        int u = i;
        int edgecnt = 0;
        while (par[target] != u && u != target) {
            u = par[u];
            edgecnt++;
        }
        if (u != target) edgecnt++;
        cntedges[i] = edgecnt;
    }
    dfs(0);

    int cntyes = n;
    int64_t cursum = 0;
    auto recompute = [&](int x) {
        int64_t old_value = w - cursum + smaffected[x];
        int target = (x + 1) % n;
        int u = x;
        int64_t nw_value = 0;
        while (par[target] != u && u != target) {
            nw_value += vals[u];
            u = par[u];
        }
        if (u != target) nw_value += vals[target];
        total += nw_value - old_value;
    };

    for (int i = 0; i < n - 1; i++) {
        int x;
        int64_t y;
        cin >> x >> y;
        x--;
        vals[x] = y;

        int cntaffected = 0;
        if (--cntedges[x - 1] == 0) {
            cntyes--;
            recompute(x - 1);
        }
        else {
            cntaffected++;
            smaffected[x - 1] += y;
        }

        if (--cntedges[mx_subtree[x]] == 0) {
            cntyes--;
            recompute(mx_subtree[x]);
        }
        else {
            cntaffected++;
            smaffected[mx_subtree[x]] += y;
        }
        total -= (cntyes - cntaffected) * y;
        cursum += y;
        cout << total << " \n"[i == n - 2];
    }
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
