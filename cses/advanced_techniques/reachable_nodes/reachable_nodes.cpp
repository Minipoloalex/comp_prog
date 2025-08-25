#include <bits/stdc++.h>
using namespace std;

#pragma GCC target("popcnt")    // not necessary here, but makes it slightly more efficient

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

const int MAX = int(5e4);

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;v--;
        g[u].push_back(v);
    }
    top_order top(g);
    vector<int> order = top.sort();
    vector<bitset<MAX>> reachable(n);
    for (int i = n - 1; i >= 0; i--) {
        int u = order[i];
        for (int v: g[u]) {
            reachable[u] |= reachable[v];
        }
        reachable[u].set(i);
    }
    for (int i = 0; i < n; i++) {
        cout << reachable[i].count() << " \n"[i == n - 1];
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
