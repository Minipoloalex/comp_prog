#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    while (m--) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    vector<int> dist(n, -1), p(n, -1);
    auto bfs = [&](int s) {
        queue<int> q;
        q.push(s);
        dist[s] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v: g[u]) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    p[v] = u;
                    q.push(v);
                }
            }
        }
    };
    bfs(0);
    int d = n - 1;
    if (dist[d] == -1) {
        cout << "IMPOSSIBLE\n";
    }
    else {
        vector<int> path;
        while (d != -1) {
            path.push_back(d);
            d = p[d];
        }
        reverse(path.begin(), path.end());
        cout << path.size() << '\n';
        for (int pt: path) {
            cout << pt + 1 << " ";
        }
        cout << '\n';
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
