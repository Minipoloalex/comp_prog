#include <bits/stdc++.h>
using namespace std;

void go(int u, int n, vector<vector<int>> &g, vector<int> &save, vector<vector<int>> &dp) {
    if (u == n-1) {
        dp[u][0] = 1;
        return;
    }
    if (save[u]) return;

    for (int v: g[u]) {
        go(v, n, g, save, dp);
        for (int i = 0; i < n; i++) {
            if (dp[v][i]) {
                dp[u][i + 1] = 1;
            }
        }
    }
    save[u] = 1;
}

void solve() {
    int n1, n2, m1, m2;
    cin >> n1 >> n2 >> m1 >> m2;
    vector<vector<int>> g1(n1), g2(n2);
    auto read = [](vector<vector<int>> &g, int m) {
        while (m--) {
            int a, b;
            cin >> a >> b;
            g[a - 1].push_back(b - 1);
        }
    };
    read(g1, m1);
    read(g2, m2);
    vector<vector<int>> dp1(n1, vector<int>(n1)), dp2(n2, vector<int>(n2));
    vector<int> save1(n1), save2(n2);
    go(0, n1, g1, save1, dp1);
    go(0, n2, g2, save2, dp2);
    vector<int> &v1 = dp1[0], &v2 = dp2[0];
    int q;
    cin >> q;
    while (q--) {
        int v;
        cin >> v;
        bool possible = false;
        // instead of answering online, could precalculate all of the answers
        for (int i = 0; i <= v; i++) {
            if (i >= int(v1.size()) || v - i >= int(v2.size())) continue;
            possible |= v1[i] && v2[v - i];
        }
        cout << (possible ? "YES" : "NO") << '\n';
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
