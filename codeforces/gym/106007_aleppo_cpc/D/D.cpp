#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<vector<int>> g(n);

    string s;
    for (int i = 0; i < n; i++) {
        cin >> s;
        for (int j = 0; j < n; j++) {
            if (s[j] != '0') g[i].push_back(j);
        }
    }

    vector<bool> vis(n, false);

    vector<pair<int,int>> ans;
    function<void(int)> dfs = [&] (int u) {
        vis[u] = true;

        for (int c : g[u]) {
            if (!vis[c]) {
                ans.emplace_back(u, c);
                dfs(c);
            }
        }
    };

    dfs(0);

    bool can = true;
    for (int i = 0; i < n; i++) can &= vis[i];

    if (can) {
        cout << "Yes\n";
        // for (int i = 0; i < n; i++) {
        //     for (int c : tree[i]) cout << i + 1 << ' ' << c + 1 << '\n';
        // }
        reverse(ans.begin(), ans.end());
        for (auto &[a, b]: ans) {
            cout << a + 1 << " " << b + 1 << '\n';
        }
    } else {
        cout << "No\n";
    }
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
