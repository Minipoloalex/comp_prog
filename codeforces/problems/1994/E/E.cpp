#include <bits/stdc++.h>
using namespace std;

// don't need dfs (could just use N instead XD)
int dfs(int u, vector<vector<int>> &g, vector<int> &st) {
    st[u] = 1;
    for (int v: g[u]) {
        st[u] += dfs(v, g, st);
    }
    return st[u];
}

void solve() {
    int k; cin >> k;
    vector<int> trees(k);
    for (auto &sz: trees) {
        int n;
        cin >> n;
        vector<int> st(n);
        vector<vector<int>> g(n);
        for (int i = 1; i < n; i++) {
            int pi; cin >> pi;
            pi--;
            g[pi].push_back(i);
        }
        dfs(0,g,st);
        sz = st[0]; // this is just N but ok...
    }
    int ans = 0;
    for (int b = 20; b >= 0; b--) {
        int cnt = 0;
        for (int j = 0; j < int(trees.size()); j++) {
            int sz = trees[j];
            if (sz & (1 << b)) {
                cnt++;
            }
        }
        if (cnt) {
            ans |= 1 << b;
            if (cnt > 1) {
                ans |= (1 << b) - 1;
                break;
            }
        }
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
