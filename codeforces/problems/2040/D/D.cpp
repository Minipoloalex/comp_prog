#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--;v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    if (n == 2) {
        cout << "1 2\n";
        return;
    }
    int root = -1;
    for (int i = 0; i < n; i++) {
        if (g[i].size() >= 2) {
            root = i;
        }
    }
    assert(root != -1);

    set<int> avail;
    for (int i = 4; i <= 2*n; i += 2) {
        avail.insert(i);
    }
    auto get_first = [&](int val) {
        for (int v: avail) {
            if (abs(val - v) > 2) {
                return v;
            }
        }
        exit(-1);
    };
    vector<int> a(n);
    function<void(int,int,int)> dfs = [&](int u, int p, int val) {
        a[u] = val;
        bool used_single_child = false;
        for (int v: g[u]) {
            if (v != p) {
                if (g[v].size() == 1 && !used_single_child) {
                    a[v] = val - 1;
                    used_single_child = true;
                }
                else {
                    int nxt_val = get_first(val);
                    avail.erase(nxt_val);
                    dfs(v, u, nxt_val);
                }
            }
        }
    };
    dfs(root, -1, 2);
    for (int val: a) cout << val << " ";
    cout << '\n';
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
