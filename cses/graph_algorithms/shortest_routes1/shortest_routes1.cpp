#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int,int>>> g(n);
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a-1].emplace_back(b-1,c);
    }
    // simple dijkstra
    vector<int64_t> d(n, -1);
    set<pair<int64_t,int>> pq;
    d[0] = 0;
    pq.emplace(d[0], 0);
    while (!pq.empty()) {
        auto [dist, u] = *pq.begin();
        pq.erase(pq.begin());
        for (auto &[v, w]: g[u]) {
            if (d[v] == -1 || d[u] + w < d[v]) {    // d[u] same as dist
                pq.erase({d[v], v});
                d[v] = d[u] + w;
                pq.emplace(d[v], v);
            }
        }
    }
    // problem says we can assume we can get to every other city
    for (int i = 0; i < n; i++) {
        cout << d[i] << " \n"[i == n - 1];
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
