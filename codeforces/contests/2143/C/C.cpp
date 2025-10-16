#include <bits/stdc++.h>
using namespace std;

class top_order {
public:
    int n; vector<vector<int>> g;

    top_order(vector<vector<int>>& A) : n(int(A.size())), g(A) {}

    vector<int> sort() {
        vector<int> indeg(n, 0), res;
        for (auto& l : g) for (auto& x : l) indeg[x]++;
        queue<int> q;
        for (int i = 0; i < n; i++) if (indeg[i] == 0) q.push(i);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            res.push_back(u);
            for (auto& x : g[u]) {
                if (--indeg[x] == 0) q.push(x);
            }
        }
        return res; // make sure res.size() == n
    }
};

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v, x, y;
        cin >> u >> v >> x >> y;
        u--;v--;
        if (x > y) {
            g[v].push_back(u);
        }
        else {
            g[u].push_back(v);
        }
    }
    top_order tp(g);
    vector<int> order = tp.sort();
    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
        ans[order[i]] = i + 1;
    }
    for (auto &v: ans) cout << v << " ";
    cout << '\n';
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
