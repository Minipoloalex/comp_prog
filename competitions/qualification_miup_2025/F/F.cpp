#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, h, l;
    cin >> n >> h >> l;
    vector<int> x(h);
    for (auto &xi: x) cin >> xi;
    vector<vector<int>> g(n);
    while (l--) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    vector<int> ans(n, INT_MAX);
    queue<int> q;
    for (int i = 0; i < h; i++) {
        ans[x[i]] = 0;
        q.push(x[i]);
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v: g[u]) {
            if (ans[v] == INT_MAX) {
                ans[v] = ans[u] + 1;
                q.push(v);
            }
        }
    }
    // for (int i = 0; i < n; i++) cout << ans[i] << " ";
    // cout << endl;
    int id = int(max_element(ans.begin(), ans.end()) - ans.begin());
    cout << id << '\n';
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    int t = 1;
    // cin >> t;
    while (t--) { 
        solve();
    }
    return 0;
}
