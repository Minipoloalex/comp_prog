#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> g(n + 1);
    vector<int> learned(n + 1);
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(i);
        g[b].push_back(i);
        if (a == 0 && b == 0) {
            learned[i] = 1;
            q.push(i);
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v: g[u]) {
            if (!learned[v]) {
                learned[v] = 1;
                q.push(v);
            }
        }
    }
    int ans = int(count(learned.begin(), learned.end(), 1));
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
